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
        List L = newList();
        getPath(L, G, 4);
        printList(stdout, L);
        printf("\n");
        printGraph(stdout, G);

        printf("\n");
        Graph A = newGraph(100);
        if(getSize(A) != 0){
                return 1;
        }
        addArc(A, 54, 1);
        addArc(A, 54, 2);
        addArc(A, 54, 3);
        addArc(A, 1, 54);
        addArc(A, 1, 55);
        if(getSize(A) != 5){
                return 2;
        }
        BFS(A, 67);
        if(getSize(A) != 5){
                return 3;
        }
        addArc(A, 55, 1);
        if(getSize(A) != 6){
                return 4;
        }
        printf("passed tests");
	freeList(&L);
	freeGraph(&A);
	freeGraph(&G);
	return 0;

}
