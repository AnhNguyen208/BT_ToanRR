#include "DFS.h"

void addEdge_weight(Graph graph, int v1, int v2, double weight);
double getEdgeValue_dijkstra(Graph graph, int v1, int v2);
int indegree(Graph graph, int v, int *output);
void swapArray(int arr[], int cnt);
double shortestPath(Graph graph, int start, int stop, int *path, int *numVertices);
void dijkstra(char *filename1, char *filename2);
