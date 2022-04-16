#include <stdio.h>
#include <stdlib.h>
#include "List.h"
#include "Graph.h"

//create GraphObj Struct
typedef struct GraphObj{
	List *listArr;
	int *color;
	int *parent;
	int *distance;
	int order;
	int size;
	int source;
}GraphObj;

Graph newGraph(int n){
	Graph G = malloc(sizeof(GraphObj));
	//allocate space for n 
	G->listArr = malloc(sizeof(List) * (n + 1));
	G->color = malloc(sizeof(int) * (n + 1));
	G->parent = malloc(sizeof(int) * (n + 1));
	G->distance = malloc(sizeof(int) * (n + 1));
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
		for(int i = 1; i < getOrder(*pG)+1; i += 1){
			freeList(&(*pG)->listArr[i]);
		}
		free((*pG)->listArr);
		free((*pG)->color);
		free((*pG)->parent);
		free((*pG)->distance);
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
		G->distance[i] = NIL;
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
	//append/prepend/insertBefore/insertAfter to have sorted listArr
	/*
	if(length(G->listArr[u]) == 0){
		append(G->listArr[u], v);
	}
	else{
		//if length of adj list of u is not empty
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
			//if index falls off and is not inserted in the middle somewhere
			if(index(G->listArr[u]) == -1){
				append(G->listArr[u], v);
			}
		}
	}
	
	if(length(G->listArr[v]) == 0){
		append(G->listArr[v], u);
	}
	else{
		//if length of adj list of v is not empty
		moveFront(G->listArr[v]);
		if(u <= front(G->listArr[v])){
			prepend(G->listArr[v], u);
		}
		else{
			while(index(G->listArr[v]) >= 0){
				if(u <= get(G->listArr[v])){
					insertBefore(G->listArr[v], u);
					break;
				}
				moveNext(G->listArr[v]);
		}
			if(index(G->listArr[v]) == -1){
				append(G->listArr[v], u);
			}
		}
	}
	//increment size variable after adding the edge to the graph
	G->size += 1;
	*/
}

void addArc(Graph G, int u, int v){
	if(G == NULL){
		printf("Graph Error: addArc() on a NULL Graph");
		exit(EXIT_FAILURE);
	}
	if(u < 1 || u > getOrder(G) || v < 1 || v > getOrder(G)){
		printf("Graph Error: addArd() on a NULL Graph");
		exit(EXIT_FAILURE);
	}
	if(length(G->listArr[u]) == 0){
		append(G->listArr[u], v);
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
	/*
	if(length(G->listArr[v]) == 0){
		append(G->listArr[v], u);
	}
	else{
		moveFront(G->listArr[v]);
		if(u <= front(G->listArr[v])){
			prepend(G->listArr[v], u);
		}
		else{
			while(index(G->listArr[v]) >= 0){
				if(u <= get(G->listArr[v])){
					insertBefore(G->listArr[v], u);
					break;
				}
				moveNext(G->listArr[v]);
			}
			if(index(G->listArr[v]) == -1){
				append(G->listArr[v], u);
			}
		}
	}
	*/
	G->size += 1;
}

//BFS(Graph G, int s) s = source, sets source, color, distance, and parent parameters of
//each vertex to corresponding values
//color: 0 = white, 1 = gray, 2 = black
void BFS(Graph G, int s){
	if(G == NULL){
		printf("Graph Error: BFS() on a NULL Graph");
		exit(EXIT_FAILURE);
	}
	if(s <= 0 || s > getOrder(G)){
		printf("Graph Error: BFS() on an invalid source");
		exit(EXIT_FAILURE);
	}
	for(int i = 1; i < getOrder(G) +1; i += 1){
		if(i == s){
			continue;
		}
		G->color[i] = 0;
		G->distance[i] = INF;
		G->parent[i] = NIL;
	}
	G->color[s] = 1;
	G->distance[s] = 0;
	G->parent[s] = NIL;
	G->source = s;
	List L = newList();
	append(L, s);
	while(length(L) != 0){
		//dequeue element = store front node in variable, deleteFront()
		int x = front(L);
		deleteFront(L);
		moveFront(G->listArr[x]);
		while(index(G->listArr[x]) >= 0){
			int y = get(G->listArr[x]);
			if(G->color[y] == 0){
				G->color[y] = 1;
				G->distance[y] = G->distance[x] + 1;
				G->parent[y] = x;
				append(L, y);
			}
			moveNext(G->listArr[x]);
		}
		G->color[x] = 2;
	}
	freeList(&L);
}

void printGraph(FILE *out, Graph G){
	for(int i = 1; i < getOrder(G) + 1; i +=1){
		fprintf(out, "%d: ", i);
		printList(out, G->listArr[i]);
		fprintf(out, "\n");
	}
}

int main(void){
	Graph G = newGraph(6);
	printf("getOrder() = %d\n", getOrder(G));
	addEdge(G, 1, 2);
	addEdge(G, 1, 6);
	addEdge(G, 2, 5);
	addEdge(G, 2, 3);
	addEdge(G, 6, 5);
	addEdge(G, 5, 4);
	addEdge(G, 4, 3);
	BFS(G, 1);
	printf("getDist 4 = %d\n", getDist(G, 4));
	printf("getSource = %d\n", getSource(G));
	printf("getParent 4 = %d\n", getParent(G, 4));
	printf("getSize() = %d\n", getSize(G));
	printGraph(stdout, G);
	freeGraph(&G);
}

