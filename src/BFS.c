#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "jrb.h"
#include "dllist.h"
#include "BFS.h"
#include "Tomau.h"

Graph1 createGraph_BFS()
{
   return make_jrb();
}

void addEdge_BFS(Graph1 graph, int v1, int v2)
{
    JRB node, tree;
    if (!adjacent_BFS(graph, v1, v2))
    {
        node = jrb_find_int(graph, v1);
        if (node==NULL)
        {
           tree = make_jrb();
           jrb_insert_int(graph, v1, new_jval_v(tree));
        }
        else
        {
           tree = (JRB) jval_v(node->val);   
        }
        jrb_insert_int(tree, v2, new_jval_i(1));
    }
    if (!adjacent_BFS(graph, v2, v1))
    {
        node = jrb_find_int(graph, v2);
        if (node==NULL)
        {
           tree = make_jrb();
           jrb_insert_int(graph, v2, new_jval_v(tree));
        }
        else
        {
           tree = (JRB) jval_v(node->val);   
        }
        jrb_insert_int(tree, v1, new_jval_i(1));   
    }
}

int adjacent_BFS(Graph1 graph, int v1, int v2)
{
    JRB node, tree;
    node = jrb_find_int(graph, v1);
    if (node==NULL)
       return 0;
    tree = (JRB) jval_v(node->val);
    if (jrb_find_int(tree, v2)==NULL)
       return 0;
    else
       return 1;       
}

int getAdjacentVertices (Graph1 graph, int v, int* output)
{
    JRB tree, node;
    int total;
    node = jrb_find_int(graph, v);
    if (node==NULL)
       return 0;
    tree = (JRB) jval_v(node->val);
    total = 0;   
    jrb_traverse(node, tree)
    {
       output[total] = jval_i(node->key);
       total++;                
    }
    return total;   
}

void dropGraph_BFS(Graph1 graph)
{
    JRB node, tree;
    jrb_traverse(node, graph)
    {
        tree = (JRB) jval_v(node->val);
        jrb_free_tree(tree);
    }
    jrb_free_tree(graph);
}

void BFS(Graph1 graph, int start, int stop, void (*func)(int))
{
   int visited[1000] = {};
   int n, output[100], i, u, v;
   Dllist node, queue;
   
   queue = new_dllist();
   dll_append(queue, new_jval_i(start));

   while ( !dll_empty(queue) )
   {
      node = dll_first(queue);
      u = jval_i(node->val);
      dll_delete_node(node);
      if (!visited[u]) 
      {
          func(u);
          visited[u] = 1;
          if ( u == stop ) return;           
          n = getAdjacentVertices(graph, u, output);
          for (i=0; i<n; i++)
          {
              v = output[i];
              if (!visited[v])
                 dll_append(queue, new_jval_i(v));
          }
      }
   }                            
}

void printVertex(int v)
{
   printf("%4d", v);
}

void Print_BFS(char *filename1)
{
   FILE *fp;
   int a, b;
   Graph1 g = createGraph_BFS();
   fp = fopen(filename1, "r");
   while (feof(fp) == 0)
   {
      fscanf(fp, "%d", &a);
      fgetc(fp);
      fscanf(fp, "%d", &b);
      addEdge_BFS(g, a, b);
   }
   cyan();
   printf("Nhap diem dau : ");
   scanf("%d", &a);
   printf("Nhap diem ket thuc : ");
   scanf("%d", &b);
   yellow();
   printf("\nBFS: bat dau tu  %d den  %d : \n", a, b);
   BFS(g, a, b, printVertex);
   printf("\n");
   dropGraph_BFS(g);
}
