#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "jrb.h"
#include "dllist.h"
#include "DFS.h"

Graph createGraph()
{
    Graph g;
    g.edges = make_jrb();
    g.vertices = make_jrb();
    return g;
}

void addVertex(Graph g, int id, char *name)
{
    JRB node = jrb_find_int(g.vertices, id);
    if (node == NULL)
        jrb_insert_int(g.vertices, id, new_jval_s(strdup(name)));
}

char *getVertex(Graph g, int id)
{
    JRB node = jrb_find_int(g.vertices, id);
    if (node == NULL)
        return NULL;
    else
        return jval_s(node->val);
}

int getEdgeValue(Graph graph, int v1, int v2)
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
        return jval_i(node->val);
}

void addEdge(Graph graph, int v1, int v2)
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
        jrb_insert_int(tree, v2, new_jval_i(1));
    }
}

int outdegree(Graph graph, int v, int *output)
{
    JRB tree, node;
    int total;
    node = jrb_find_int(graph.edges, v);
    if (node == NULL)
        return 0;
    tree = (JRB)jval_v(node->val);
    total = 0;
    jrb_traverse(node, tree)
    {
        output[total] = jval_i(node->key);
        total++;
    }
    return total;
}

void EmptyArray(int * output) {
    for (int i = 0; i < 100; i++) {
        output[i] = 0;
    }
}

void EmptyQueue(Dllist queue)
{
    while (!dll_empty(queue))
    {
        dll_delete_node(dll_first(queue));
    }
}

void dropGraph(Graph graph)
{
    JRB node, tree;
    jrb_traverse(node, graph.edges)
    {
        tree = (JRB)jval_v(node->val);
        jrb_free_tree(tree);
    }
    jrb_free_tree(graph.edges);
    jrb_free_tree(graph.vertices);
}

int Find(Dllist Stack, int id) {
    Dllist node;
    dll_traverse(node, Stack) {
        if (id == jval_i(node->val))
            return 1;
    }
    return 0;
} 

void DFS(Graph graph, int start, int stop, int *traval, Dllist Stack)
{
    int n, output[100], u, v;
    Dllist node, queue;
    JRB temp;
    queue = new_dllist();
    dll_append(queue, new_jval_i(start));

    while (!dll_empty(queue))
    {
        node = dll_last(queue);
        u = jval_i(node->val);
        dll_delete_node(node);
        if ((!traval[u]))
        {
            traval[u] = 1;
            temp = jrb_find_int(graph.vertices, u);
            printf("%s\t", jval_s(temp->val));
            dll_append(Stack, new_jval_i(u));
            if (u == stop)
            {
                return ;
            }

            n = outdegree(graph, u, output);
            for(int i = n - 1; i >= 0; i--)
            {
                v = output[i];
                if (!traval[v])
                    dll_append(queue, new_jval_i(v));
            }
        }
    }
}

int DFS_g1(Graph graph, int start, int stop, int index, int *traval, Dllist Stack)
{
    int n, output[100], u, v;
    Dllist node, stack;
    stack = new_dllist();
    dll_append(stack, new_jval_i(start));

    while (!dll_empty(stack))
    {
        node = dll_last(stack);
        u = jval_i(node->val);
        dll_delete_node(node);
        int p = Find(Stack, u);
        if ((!traval[u]) && (p == 1))
        {
            traval[u] = index;
            
            if (u == stop){
                index++;
                return index;
            }
                
            n = outdegree(graph, u, output);
            for(int i = n - 1; i >= 0; i--)
            {
                v = output[i];
                if (!traval[v])
                    dll_append(stack, new_jval_i(v));
            }
        }
    }
    index++;
    return index;
}

void DAG_DFS(char* filename1, char* filename2)
{
    Graph g = createGraph();
    Graph g1 = createGraph();
    Dllist Stack, Stack1;
    Stack = new_dllist();
    JRB node;
    FILE *fp;
    FILE *fp1;
    int index, index1, temp1, temp2;
    int traval[100], pre[100];
    EmptyArray(traval);
    EmptyArray(pre);
    fp = fopen(filename1, "r");
    fscanf(fp, "%d", &index);
    char *a, *b;
    a = malloc(5);
    b = malloc(5);
    index1 = 0;
    while (!feof(fp))
    {
        fscanf(fp, "%s", a);
        addVertex(g, index1 + 1, a);
        addVertex(g1, index1 + 1, a);
        fgetc(fp);
        index1++;
        if (index1 == index)
            break;
    }
    fclose(fp);

    fp1 = fopen(filename2, "r");
    fscanf(fp1, "%d", &index);
    index1 = 0;
    while (!feof(fp1))
    {
        fscanf(fp1, "%s", a);
        fscanf(fp1, "%s", b);
        fgetc(fp1);
        jrb_traverse(node, g.vertices)
        {
            if (strcmp(a, jval_s(node->val)) == 0)
                temp1 = jval_i(node->key);
            if (strcmp(b, jval_s(node->val)) == 0)
                temp2 = jval_i(node->key);
        }
        addEdge(g, temp1, temp2);
        addEdge(g1, temp2, temp1);
        index1++;
        if (index1 == index)
            break;
    }
    fclose(fp1);

    printf("DFS:\n");
    DFS(g, 1, -1, traval, Stack);
    EmptyArray(traval);

    index = 1;
    while (!dll_empty(Stack))
    {
        Stack1 = dll_first(Stack);
        int start = jval_i(Stack1->val);
        //printf("dll_first: %d\n", start);
        index = DFS_g1(g1, start, -1, index, traval, Stack);
        for (int i = 1; i < 100; i++) {
            if ((traval[i] != 0))
            {
                // printf("i = %d", i);
                Dllist temp_stack;
                temp_stack = new_dllist();
                dll_traverse(Stack1, Stack)
                {
                    if(jval_i(Stack1->val) == i)
                        temp_stack = dll_nil(Stack1);
                }
                if(temp_stack != NULL)
                    dll_delete_node(temp_stack);
                
            }
        }
    }
    for (int i = 1; i < index; i++)
    {
        printf("\nThành phần liên thông mạnh thứ %d: \n", i);
        for (int j = 1; j < 100; j++)
        {
            if(traval[j] == i)
            {
                node = jrb_find_int(g.vertices, j);
                printf("%s\n", jval_s(node->val));
            }
        }
       
    }
    printf("\n");
    dropGraph(g);
    dropGraph(g1);
}
