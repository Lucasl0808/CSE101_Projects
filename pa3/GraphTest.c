#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "List.h"
void Visits(int *s){
	*s += 1;
}
void test(int d[],int x, int *time){
	d[x] = *time;
	
}
int main(void){
	int time = 0;
	int distance[10];
	test(distance, 0, &time);
	Visits(&time);
	test(distance, 1, &time);
	printf("%d\n", time);
	printf("%d\n", distance[0]);
	printf("%d\n", distance[1]);
	Graph G = newGraph(8);
	List L = newList();
	for(int i = 1; i < getOrder(G) + 1; i += 1){
		append(L, i);
	}
	printList(stdout, L);
	addArc(G, 1, 2);
	addArc(G, 2, 3);
	addArc(G, 2, 5);
	addArc(G, 5, 1);
	addArc(G, 2, 6);
	addArc(G, 3, 7);
	addArc(G, 3, 4);
	addArc(G, 4, 3);
	addArc(G, 4, 8);
	addArc(G, 8, 8);
	addArc(G, 7, 8);
	addArc(G, 7, 6);
	addArc(G, 5, 6);
	addArc(G, 6, 7);
	printf("size g = %d\n", getSize(G));
	printGraph(stdout, G);
	DFS(G, L);
	printList(stdout, L);
	printf("\n");
	printf("discover time 1 = %d\n", getDiscover(G, 1));
	printf("discover time 8 = %d\n", getDiscover(G, 8));
	printf("finish time 8 = %d\n", getFinish(G, 8));
	printf("finish time 1 = %d\n", getFinish(G, 1));
	Graph T = transpose(G);
	printGraph(stdout, T);
	Graph C = copyGraph(G);
	printGraph(stdout, C);
	freeList(&L);
	freeGraph(&G);
	freeGraph(&T);
	freeGraph(&C);
}
