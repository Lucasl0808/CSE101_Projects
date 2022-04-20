#pragma once

#include <stdio.h>
#include <stdlib.h>
#include "List.h"

//INF should be a negative number, NIL should be a non-positive number
#define INF -1
#define NIL -2
#define UNDEF -3
//Initialize Graph

typedef struct GraphObj* Graph;

//Constructors

Graph newGraph(int n);
void freeGraph(Graph *pG);

//Access Functions

int getOrder(Graph G);
int getSize(Graph G);
int getSource(Graph G);
int getParent(Graph G, int u);
int getDist(Graph G, int u);
int getDiscover(Graph G, int u);
int getFinish(Graph G, int u);
void getPath(List L, Graph G, int u);

//Manipulation Procedures

void makeNull(Graph G);
void addEdge(Graph G, int u, int v);
void addArc(Graph G, int u, int v);
void BFS(Graph G, int s);
void DFS(Graph G, List S);
//Other operations
Graph transpose(Graph G);
Graph copyGraph(Graph G);
void printGraph(FILE *out, Graph G);
