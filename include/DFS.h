#include "jrb.h"
#include "dllist.h"

#define INFINITIVE_VALUE 10000000

typedef struct
{
    JRB edges;
    JRB vertices;
} Graph;

Graph createGraph();
void addVertex(Graph g, int id, char *name);
char *getVertex(Graph g, int id);
int getEdgeValue(Graph graph, int v1, int v2);
void addEdge(Graph graph, int v1, int v2);
int outdegree(Graph graph, int v, int *output);
void EmptyArray(int *output);
void dropGraph(Graph graph);
int Find(Dllist Stack, int id);
void DFS(Graph graph, int start, int stop, int *traval, Dllist Stack);
int DFS_g1(Graph graph, int start, int stop, int index, int *traval, Dllist Stack);
void DAG_DFS(char *filename1, char *filename2);