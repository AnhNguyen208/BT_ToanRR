#include "jrb.h"

typedef JRB Graph1;

Graph1 createGraph_BFS();
void addEdge_BFS(Graph1 graph, int v1, int v2);
int adjacent_BFS(Graph1 graph, int v1, int v2);
int getAdjacentVertices(Graph1 graph, int vertex, int *output);
void dropGraph_BFS(Graph1 graph);
void BFS(Graph1 graph, int start, int stop, void (*func)(int));
void printVertex(int v);
void Print_BFS(char *filename1);