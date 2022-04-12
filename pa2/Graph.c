#include <stdio.h>
#include <stdlib.h>
#include "List.h"
#include "Graph.h"

//create GraphObj Struct
typedef struct GraphObj{
	List **listArr;
	int color[];
	int parent[];
	int distance[];
	int order;
	int size;
	int source;
}GraphObj;

Graph newGraph(int n){
	Graph G = malloc(sizeof(GraphObj));
	//allocate space for n 
	G->listArr = malloc(sizeof(ListObj *) * n+1);
	G->color = malloc(sizeof(int) * n + 1);
	G->parent = malloc(sizeof(int) * n + 1);
	G->distance = malloc(sizeof(int) * n + 1);
	for(int i = 1; i < n+1; i += 1){
		G->listArr[i] = newList();
		G->color[i] = NIL;
		G->parent[i] = NIL;
		G->distance[i] = NIL;
	}
	G->order = n;
	G->size = 0;
	G->source = NIL;
	return G;
}

//change makeNull to clear all edges if function hasnt been created yet
void freeGraph(Graph *pG){
	if(pG != NULL && *pG != NULL){
		makeNull(*pG);
		free(*pG);
		*pG = NULL;
	}
}

//Access Functions

int getOrder(Graph G){
	if(G == NULL){
		printf("Graph Error: getOrder() on a NULL Graph");
		exit(EXIT_FAILURE);
	}
	return G->order;
}

int getSize(Graph G){
	if(G == NULL){
		printf("Graph Error: getSize() on a NULL Graph");
		exit(EXIT_FAILURE);
	}
	return G->size;
}

int getSource(Graph G){
	if(G == NULL){
		printf("Graph Error: getSource() on a NULL Graph");
		exit(EXIT_FAILURE);
	}
	return G->source; //source is initialized as NIL
}

//u is the vertex to get the parent for
//vertex u is parent[u]
//each vertex parent initialized as NIL
int getParent(Graph G, int u){
	if(G == NULL){
		printf("Graph Error: getParent() on a NULL Graph");
		exit(EXIT_FAILURE);
	}
	if(u < 1 || u > getOrder(G)){
		printf("Graph Error: getParent() u value is invalid");
		exit(EXIT_FAILURE);
	}
	return G->parent[u];
}

int getDist(Graph G, int u){
	if(G == NULL){
		printf("Graph Error: getDist() on a NULL Graph");
		exit(EXIT_FAILURE);
	}
	if(u < 1 || u > getOrder(G)){
		printf("Graph Error: getDist() u value is invalid");
		exit(EXIT_FAILURE);
	}
	if(getSource(G) == NIL){
		return INF;
	}
	return G->distance[u];
}
void getPath(List L, Graph G, int u){
	if(G == NULL){
		printf("Graph Error: getPath() on a NULL Graph");
		exit(EXIT_FAILURE);
	}
	if(u < 1 || u > getOrder(G)){
		printf("Graph Error: getPath() u value is invalid");
		exit(EXIT_FAILURE);
	}
	if(getSource(G) == NIL){
		printf("Graph Error: getPath() source is NIL");
		exit(EXIT_FAILURE);
	}
	if(getDist(G, u) == INF){
		append(L, INF);
		return;
	}
	int curr = u;
	while(curr != G->source){
		append(L, curr);
		curr = getParent(G, curr);
	}
	append(L, curr);
	return;
}

