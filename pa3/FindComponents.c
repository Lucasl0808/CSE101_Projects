#include <stdio.h>
#include <stdlib.h>
#include "List.h"
#include "Graph.h"

int main(int argc, char *argv[]){
	if(argc != 3){
		fprintf(stderr, "Usage: %s <input file> <output file>\n", argv[0]);
		exit(1);
	}
	FILE *in, *out;
	in = fopen(argv[1], "r");
	if(in == NULL){
		printf("Unable to open file %s for reading\n", argv[1]);
		exit(1);
	}
	out = fopen(argv[2], "w");
	if(out == NULL){
		printf("Unable to open file %s for writing\n", argv[2]);
		exit(1);
	}
	int vertices;
	fscanf(in, "%d", &vertices);
	Graph G = newGraph(vertices);
	int u = NIL;
	int v = NIL;
	fscanf(in, "%d %d", &u, &v);
	while(u != 0 && v != 0){
		addArc(G, u, v);
		fscanf(in, "%d %d", &u, &v);
	}
	fprintf(out, "Adjacency list representation of G:\n");
	printGraph(out, G);
	fprintf(out, "\n");

	List S = newList();
	for(int i = 1; i < getOrder(G) +1; i += 1){
		append(S, i);
	}
	DFS(G, S);
	Graph T = transpose(G);
	DFS(T, S);

	//pop off the stack backwards to find SCC of G
	int components = 0;
	moveFront(S);
	while(index(S) >= 0){
		int u = get(S);
		if(getParent(T, u) == NIL){
			components += 1;
		}
		moveNext(S);
	}
	printf("parent of 8 = %d\n", getParent(G, front(S)));
	fprintf(out, "G contains %d strongly connected components:\n", components);
	for(int i = 1; i < components + 1; i +=1){
		List L = newList();
		int B = back(S);
		while(getParent(T, B) != NIL){
			prepend(L, B);
			deleteBack(S);
			B = back(S);
		}
		prepend(L, B);
		deleteBack(S);
		fprintf(out, "Component %d: ", i);
		printList(out, L);
		fprintf(out, "\n");
		freeList(&L);
	}
	freeGraph(&T);
	freeGraph(&G);
	fclose(in);
	fclose(out);
}

