/* Lucas Lee
 * luclee
 * CSE101-02 Spring 2022
 * pa2
*/
#include <stdio.h>
#include <stdlib.h>

#include "List.h"
#include "Graph.h"

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
        int x = 4;
        while(x != NIL){
                printf("path = %d\n", x);
                x = getParent(G, x);
        }
        printf("\n");
        printGraph(stdout, G);

        printf("\n");

	List L = newList();
	getPath(L, G, 4);
	printList(stdout, L);
	freeList(&L);
	freeGraph(&G);
	return 0;

}
