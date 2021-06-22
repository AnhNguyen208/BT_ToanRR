#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "jrb.h"
#include "dllist.h"
#include "DFS.h"
#include "Tomau.h"

void swapArray(int arr[], int cnt)
{
    for (int i = 0; i < cnt / 2; i++)
    {
        int c = arr[i];
        arr[i] = arr[cnt - i - 1];
        arr[cnt - i - 1] = c;
    }
}

void addEdge_weight(Graph graph, int v1, int v2, double weight)
{
    JRB node, tree;
    if (getEdgeValue(graph, v1, v2) == INFINITIVE_VALUE)
    {
        node = jrb_find_int(graph.edges, v1);
        if (node == NULL)
        {
            tree = make_jrb();
            jrb_insert_int(graph.edges, v1, new_jval_v(tree));
        }
        else
        {
            tree = (JRB)jval_v(node->val);
        }
        jrb_insert_int(tree, v2, new_jval_d(weight));
    }
}

double getEdgeValue_dijkstra(Graph graph, int v1, int v2)
{
    JRB node, tree;
    node = jrb_find_int(graph.edges, v1);
    if (node == NULL)
        return INFINITIVE_VALUE;
    tree = (JRB)jval_v(node->val);
    node = jrb_find_int(tree, v2);
    if (node == NULL)
        return INFINITIVE_VALUE;
    else
        return jval_d(node->val);
}

int indegree(Graph graph, int v, int *output)
{
    JRB tree, node;
    int total = 0;
    jrb_traverse(node, graph.edges)
    {
        tree = (JRB)jval_v(node->val);
        if (jrb_find_int(tree, v))
        {
            output[total] = jval_i(node->key);
            total++;
        }
    }
    return total;
}

double shortestPath(Graph graph, int start, int stop, int *path, int *numVertices)
{
    double distance[1000];
    int previous[1000], u, visit[1000];

    for (int i = 0; i < 1000; i++)
    {
        distance[i] = INFINITIVE_VALUE;
        visit[i] = 0;
        previous[i] = 0;
    }
    distance[start] = 0;
    previous[start] = start;
    visit[start] = 1;

    Dllist ptr, queue, node;
    queue = new_dllist();
    dll_append(queue, new_jval_i(start));

    while (!dll_empty(queue))
    {
        double min = INFINITIVE_VALUE;
        dll_traverse(ptr, queue)
        {
            u = jval_i(ptr->val);
            if (min > distance[u])
            {
                min = distance[u];
                node = ptr;
            }
        }

        u = jval_i(node->val);
        visit[u] = 1;
        dll_delete_node(node);
        if (u == stop)
            break;

        int output[1000];
        int n = outdegree(graph, u, output);

        for (int i = 0; i < n; i++)
        {
            int v = output[i];
            double w = getEdgeValue_dijkstra(graph, u, v);
            if (distance[v] > distance[u] + w)
            {
                distance[v] = distance[u] + w;
                previous[v] = u;
            }
            if (visit[v] == 0)
            {
                dll_append(queue, new_jval_i(v));
            }
        }
    }

    double distance_s_t = distance[stop];
    int count = 0;
    if (distance[stop] != INFINITIVE_VALUE)
    {
        path[count++] = stop;
        while (stop != start)
        {
            stop = previous[stop];
            path[count++] = stop;
        }
        *numVertices = count;
    }
    swapArray(path, count);
    return distance_s_t;
}

void dijkstra(char* filename1, char* filename2)
{
    int i = 0, length, path[100], a, b;
    double w, weight;
    char s[3];
    Graph g = createGraph();
    FILE *p = fopen(filename1, "r");
    while (feof(p) == 0)
    {
        fscanf(p, "%d", &i);
        fgetc(p);
        fscanf(p, "%s", s);
        addVertex(g, i, s);
        i++;
    }
    fclose(p);
    FILE *fp = fopen(filename2, "r");
    while (feof(fp) == 0)
    {
        fscanf(fp, "%d", &a);
        fgetc(fp);
        fscanf(fp, "%d", &b);
        fgetc(fp);
        fscanf(fp, "%lf", &weight);
        addEdge_weight(g, a, b, weight);
    }
    fclose(fp);
    cyan();
    printf("Diem bat dau  : ");
    scanf("%d", &a);
    printf("Diem ket thuc : ");
    scanf("%d", &b);
    w = shortestPath(g, a, b, path, &length);
    if (w == INFINITIVE_VALUE)
    {
        yellow();
        printf("Khong co duong di tu dinh  %s den dinh  %s !!!!!!!\n", getVertex(g, a), getVertex(g, b));
    }
    else
    {
        yellow();
        printf("Duong di ngan nhat tu dinh %s den dinh %s la : %lf(m)\n", getVertex(g, a), getVertex(g, b), w);
        printf("Ban phai di qua lan luot cac dinh : \n");
        for (i = 0; i < length; i++)
            printf(" => %s", getVertex(g, path[i]));
        printf("\n");
    }

    dropGraph(g);
}