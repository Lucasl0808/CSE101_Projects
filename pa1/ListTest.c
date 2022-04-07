#include "List.h"

int main(void){
        List L = newList();
        append(L, 2);
        append(L, 3);
        prepend(L, 1);
        append(L, 4);
        append(L, 6);
        printList(stdout, L);
        moveFront(L);
        //printf("front element is %d\n", L->cursor->value);
        moveNext(L);
        //printf("cursor element is %d\n", L->cursor->value);
        moveBack(L);
        //printf("back element is %d\n", L->cursor->value);
        insertBefore(L, 5);
        printList(stdout, L);
        printf("\n");
        moveFront(L);
        insertBefore(L, 0);
        moveBack(L);
        insertAfter(L, 8);
        insertAfter(L, 7);
        printList(stdout, L);
        printf("\n");
        printf("length = %d\n", length(L));
        printf("index = %d\n", index(L));
        printf("front = %d\n", front(L));
        printf("back = %d\n", back(L));
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
        printList(stdout, G);
        printf("\n");
        printf("copy list = copied list = %d\n", equals(G, L));
        freeList(&G);
        freeList(&L);
	
	/*
        List A = newList();
        List B = newList();
	List C = copyList(A);
	printList(stdout, C);
        append(A, 4);
        append(B, 4);
        printf("A = B is %d\n", equals(A, B));
        printList(stdout, A);
        printf("\n");
        printList(stdout, B);
        deleteFront(A);
        deleteBack(B);
        printList(stdout, A);
        printf("\n");
        printList(stdout, B);
        printf("\n");
        freeList(&A);
        freeList(&B);
	*/
}
