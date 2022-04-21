/* Lucas Lee
 * luclee
 * CSE101-02 Spring 2022
 * pa2
*/
#include <stdio.h>
#include <stdlib.h>
#include "List.h"
#include "Graph.h"

//create GraphObj Struct
typedef struct GraphObj{
	List *listArr;
	int *color;
	int *parent;
	int order;
	int size;
	int *discover;
	int *finish;
}GraphObj;

Graph newGraph(int n){
	Graph G = malloc(sizeof(GraphObj));
	//allocate space for n 
	G->listArr = malloc(sizeof(List) * (n + 1));
	G->color = malloc(sizeof(int) * (n + 1));
	G->parent = malloc(sizeof(int) * (n + 1));
	G->discover = malloc(sizeof(int) * (n + 1));
	G->finish = malloc(sizeof(int) * (n + 1));
	for(int i = 1; i < n+1; i += 1){
		G->listArr[i] = newList();
		G->color[i] = NIL;
		G->parent[i] = NIL;
		G->discover[i] = UNDEF;
		G->finish[i] = UNDEF;
	}
	G->order = n;
	G->size = 0;
	return G;
}

//change makeNull to clear all edges if function hasnt been created yet
void freeGraph(Graph *pG){
	if(pG != NULL && *pG != NULL){
		makeNull(*pG);
		for(int i = 1; i < getOrder(*pG)+1; i += 1){
			freeList(&(*pG)->listArr[i]);
		}
		free((*pG)->listArr);
		free((*pG)->color);
		free((*pG)->discover);
		free((*pG)->finish);
		free((*pG)->parent);
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

//getDiscover(Graph G, int u) return the value for the discovery time of the vertex u
int getDiscover(Graph G, int u){
	if(G == NULL){
		printf("Graph Error: getDiscover() on a NULL Graph");
		exit(EXIT_FAILURE);
	}
	if(u < 1 || u > getOrder(G)){
		printf("Graph Error: getDiscover() on an invalid u value");
		exit(EXIT_FAILURE);
	}
	return G->discover[u];
}


int getFinish(Graph G, int u){
	if(G == NULL){
		printf("Graph Error: getFinish() on a NULL Graph");
		exit(EXIT_FAILURE);
	}
	if(u < 1 || u > getOrder(G)){
		printf("Graph Error: getFinish() on an invalid u value");
		exit(EXIT_FAILURE);
	}
	return G->finish[u];
}


//manipulation procedures

//makeNull deletes all edges in G, doesnt free arrays or list
void makeNull(Graph G){
	if(G == NULL){
		printf("Graph Error: makeNull() on a NULL Graph");
		exit(EXIT_FAILURE);
	}
	if(getSize(G) == 0){
		return;
	}
	for(int i = 1; i < getOrder(G) + 1; i += 1){
		clear(G->listArr[i]);
		G->parent[i] = NIL;
		//G->distance[i] = NIL;

	}
	G->size = NIL;
}

//addEdge adds int u to adjacency list of v, and v to the adjacency list of u
//pre: both ints have to be between 1 and getOrder
//increments Graph size
//COULD USE addArc() to cut down lines in program
//addArc(u, v)
//addArc(v, u)
//decrement size by 1
void addEdge(Graph G, int u, int v){
	if(G == NULL){
		printf("Graph Error: addEdge() on a NULL Graph");
		exit(EXIT_FAILURE);
	}
	if(u < 1 || u >getOrder(G) || v < 1 || v > getOrder(G)){
		printf("Graph Error: addEdge() u or v value is invalid");
		exit(EXIT_FAILURE);
	}
	addArc(G, u, v);
	addArc(G, v, u);
	G->size -= 1;
}

void addArc(Graph G, int u, int v){
	if(G == NULL){
		printf("Graph Error: addArc() on a NULL Graph");
		exit(EXIT_FAILURE);
	}
	if(u < 1 || u > getOrder(G) || v < 1 || v > getOrder(G)){
		printf("Graph Error: addArc() on a NULL Graph");
		exit(EXIT_FAILURE);
	}
	//if v is in the adj list of u, return nothing
	if(length(G->listArr[u]) == 0){
		append(G->listArr[u], v);
		G->size += 1;
		return;
	}
	moveFront(G->listArr[u]);
	while(index(G->listArr[u]) >= 0){
		int y = get(G->listArr[u]);
		if(v == y){
			return;
		}
		moveNext(G->listArr[u]);
	}
	if(length(G->listArr[u]) == 0){
		return;
	}
	else{
		moveFront(G->listArr[u]);
		if(v <= front(G->listArr[u])){
			prepend(G->listArr[u], v);
		}
		else{
			while(index(G->listArr[u]) >= 0){
				if(v <= get(G->listArr[u])){
					insertBefore(G->listArr[u], v);
					break;
				}
				moveNext(G->listArr[u]);
			}
			if(index(G->listArr[u]) == -1){
				append(G->listArr[u], v);
			}
		}
	}
	G->size += 1;
}

//void DFS(Graph G, List S) runs DFS algorithm on a graph
//pre: length(S) == getOrder(G)
//This function will need a Visit() function to perform recursion

void DFS(Graph G, List S){
	if(G == NULL){
		printf("Graph Error: DFS() on a NULL Graph");
		exit(EXIT_FAILURE);
	}
	if(length(S) != getOrder(G)){
		printf("Graph Error: DFS() length(S) != getOrder(G)");
		exit(EXIT_FAILURE);
	}
	//mark each vertex of G as white color and have a NIL parent
	for(int i = 1; i < getOrder(G) + 1; i += 1){
		G->color[i] = 0;
		G->parent[i] = NIL;
	}
	int time = 0;
	moveBack(S);
	for(int i = 1; i < getOrder(G) +1; i +=1){
		int y = front(S);
		if(G->color[y] == 0){
			Visit(G, y, &time, S);
		}
		deleteFront(S);
	}
}

void Visit(Graph G, int x, int *time, List S){
	//after finishing a vertex, append it to the stack
	*time += 1;
	G->discover[x] = *time;
	G->color[x] = 1;
	//for all y in adj[x]
	moveFront(G->listArr[x]);
	while(index(G->listArr[x]) >= 0){
		int y = get(G->listArr[x]);
		if(G->color[y] == 0){
			G->parent[y] = x;
			Visit(G, y, time, S);
		}
		moveNext(G->listArr[x]);
	}
	G->color[x] = 2;
	insertAfter(S, x);
	*time += 1;
	G->finish[x] = *time;
}

//transpose(Graph G) returns a graph with all arcs reversed in G

Graph transpose(Graph G){
	Graph T = newGraph(getOrder(G));
	for(int i = 1; i < getOrder(G) +1; i +=1){
		moveFront(G->listArr[i]);
		while(index(G->listArr[i]) >= 0){
			int y = get(G->listArr[i]);
			addArc(T, y, i);
			moveNext(G->listArr[i]);
		}
	}
	return T;
}

Graph copyGraph(Graph G){
	Graph C = newGraph(getOrder(G));
	for(int i = 1; i < getOrder(G) + 1; i += 1){
		moveFront(G->listArr[i]);
		while(index(G->listArr[i]) >= 0){
			int y = get(G->listArr[i]);
			addArc(C, i, y);
			moveNext(G->listArr[i]);
		}
	}
	return C;
}
void printGraph(FILE *out, Graph G){
	for(int i = 1; i < getOrder(G) + 1; i +=1){
		fprintf(out, "%d: ", i);
		printList(out, G->listArr[i]);
		fprintf(out, "\n");
	}
}
