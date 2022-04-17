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
	//first line in the file is read
	Graph G = newGraph(vertices);
	int u = NIL;
	int v = NIL;
	fscanf(in, "%d %d", &u, &v);
	while(u != 0 && v != 0){
		addEdge(G, u, v);
		fscanf(in, "%d %d", &u, &v);
	}
	//finished making graph
	printGraph(out, G);
	fprintf(out, "\n");
	int source = NIL;
	int dest = NIL;
	fscanf(in, "%d %d", &source, &dest);
	while(source != 0 && dest != 0){
		BFS(G, source);
		if(getDist(G, dest) == INF){
			fprintf(out, "The distance from %d to %d is infinity\n", source, dest);
			fprintf(out, "No %d-%d path exists\n", source, dest);
			fscanf(in, "%d %d", &source, &dest);
			continue;
		}
		fprintf(out, "The distance from %d to %d is %d\n", source, dest, getDist(G, dest));
		fprintf(out, "A shortest %d-%d path is: ", source, dest);
		List L = newList();
		getPath(L, G, dest);
		printList(out, L);
		fprintf(out, "\n");
		fprintf(out, "\n");
		freeList(&L);
		fscanf(in, "%d %d", &source, &dest);
	}
	fclose(out);
	fclose(in);
	freeGraph(&G);
}

