/* Lucas Lee
 * luclee
 * CSE101-02 Spring 2022
 * pa1
 */
#include "List.h"

int main(void){
        List L = newList();
	List P = newList();
        append(L, 2);
        append(L, 3);
        prepend(L, 1);
        append(L, 4);
        append(L, 6);
        printList(stdout, L);
        moveFront(L);
        moveNext(L);
        moveBack(L);
        insertBefore(L, 5);
	printf("\n");
        printList(stdout, L);
        printf("\n");
        moveFront(L);
        insertBefore(L, 0);
        moveBack(L);
        insertAfter(L, 8);
        insertAfter(L, 7);
        printList(stdout, L);
        printf("\n");
	moveFront(L);
	moveNext(L);
	moveNext(L);
        printf("length = %d\n", length(L));
        printf("index = %d\n", index(L));
        printf("front = %d\n", front(L));
        printf("back = %d\n", back(L));
	printf("get = %d\n", get(L));
        deleteFront(L);
        printList(stdout, L);
        printf("\n");
        deleteBack(L);
	deleteFront(L);
        printList(stdout, L);
        printf("\n");
        moveFront(L);
        moveNext(L);
        moveNext(L);
        moveNext(L);
        printf("index to delete = %d\n", index(L));
        delete(L);
        printList(stdout, L);
        List G = copyList(L);
        printf("\n");
        printf("list = copied list is %s\n", equals(G, L)?"true":"false");
        freeList(&G);
	freeList(&P);
        freeList(&L);
}

/*
Program Output:
1 2 3 4 6
1 2 3 4 5 6
0 1 2 3 4 5 6 7 8
length = 9
index = 2
front = 0
back = 8
get = 2
1 2 3 4 5 6 7 8
2 3 4 5 6 7
index to delete = 3
2 3 4 6 7
list = copied list is true
*/
