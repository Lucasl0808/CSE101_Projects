/* Lucas Lee
 * luclee
 * CSE101-02 Spring 2022
 * pa1
 */

#include "List.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//Private Nodes
typedef struct NodeObj* Node;

typedef struct NodeObj{
	int value;
	Node next;
	Node prev;
}NodeObj;

typedef struct ListObj{
	int length;
	int index;
	Node cursor;
	Node front;
	Node back;
}ListObj;

Node nodeCreate(int x){
	Node N = malloc(sizeof(NodeObj));
	N->value = x;
	N->next = NULL;
	N->prev = NULL;
	return N;
}

void freeNode(Node *pN){
	if(pN != NULL && *pN != NULL){
		free(*pN);
		*pN = NULL;
	}
}

List newList(void){
	List L = malloc(sizeof(ListObj));
	L->length = 0;
	L->index = -1;
	L->front = NULL;
	L->back = NULL;
	L->cursor = NULL;
	return L;
}

//when the list is empty, free the list and set its pointer to NULL

void freeList(List* pL){
	if(pL != NULL && *pL != NULL){
		clear(*pL);
		free(*pL);
		*pL = NULL;
	}
}

//Access Functions

//length(List L) returns total number of elements in L.
int length(List L){
	if(L == NULL){
		printf("List Error: length() on a NULL List");
		exit(EXIT_FAILURE);
	}
	return(L->length);
}

//index(List L) returns index of the cursor element if it is defined, otherwise it returns -1
//inside constructor, cursor element is initialized as -1
int index(List L){
	if(L == NULL){
		printf("List Error: index on a NULL List");
		exit(EXIT_FAILURE);
	}
	if(L->cursor == NULL){
		return -1;
	}
	else{
		return L->index;
	}
}

//front(List L) returns front element of the list
//pre: length() > 0

int front(List L){
	if(L == NULL){
		printf("List Error: front() on a NULL List");
		exit(EXIT_FAILURE);
	}
	if(length(L) <= 0){
		printf("List Error: front() on a List of length 0 or less");
		exit(EXIT_FAILURE);
	}
	return(L->front->value);
}

//back(List L) returns back element of the list
//pre: length() > 0

int back(List L){
	if(L == NULL){
		printf("List Error: back() on a NULL List");
		exit(EXIT_FAILURE);
	}
	if(length(L) <= 0){
		printf("List Error: back() on a List of length 0 or less");
		exit(EXIT_FAILURE);
	}
	return(L->back->value);
}

//get(List L) returns the cursor element of the list
//pre: length() > 0 and index() >= 0

int get(List L){
	if(L == NULL){
		printf("List Error: get() on a NULL List");
		exit(EXIT_FAILURE);
	}
	if(length(L) <= 0){
		printf("List Error: get() on a List of length 0 or less");
		exit(EXIT_FAILURE);
	}
	if(index(L) < 0){
		printf("List Error: get() on an index of less than 0");
		exit(EXIT_FAILURE);
	}
	return(L->cursor->value);
}

//equals(List A, List B) returns true if A = B, and false otherwise

bool equals(List A, List B){
	if(A == NULL){
		printf("List Error: equals() on NULL List A");
		exit(EXIT_FAILURE);
	}
	if(B == NULL){
		printf("List Error: equals() on NULL List B");
		exit(EXIT_FAILURE);
	}
	bool eq;
	Node AF, BF;
	eq = (A->length == B->length);
	AF = A->front;
	BF = B->front;
	while(eq && AF != NULL){
		eq = (AF->value == BF->value);
		AF = AF->next;
		BF = BF->next;
	}
	return eq;
}

//Manipulation procedures

//clear(List L) returns L to an empty state (no nodes)

void clear(List L){
	if(L == NULL){
		printf("List Error: clear() on a NULL List");
		exit(EXIT_FAILURE);
	}
	Node N = NULL;
	while(L->front != NULL){
		N = L->front;
		L->front = L->front->next;
		freeNode(&N);
	}
	L->length = 0;
	L->index = -1;
	L->cursor = NULL;
	L->back = NULL;
	//all nodes should be freed and values are reset
}

//set(List L, int x) overwrites cursor element with x
//pre: length() > 0 and index() >= 0
void set(List L, int x){
	if(L == NULL){
		printf("List Error: set() on a NULL List");
		exit(EXIT_FAILURE);
	}
	if(length(L) <= 0){
		printf("List Error: set() on a List of length 0 or less");
		exit(EXIT_FAILURE);
	}
	if(index(L) < 0){
		printf("List Error: set() on a List with cursor index < 0");
		exit(EXIT_FAILURE);
	}
	L->cursor->value = x;
}

//moveFront(List L) moves cursor to the front element, does nothing otherwise

void moveFront(List L){
	if(L == NULL){
		//printf("List Error: moveFront() on a NULL List");
		//exit(EXIT_FAILURE);
		return;
	}
	if(length(L) <= 0){
		//printf("List Error: moveFront() on a List of length 0");
		//exit(EXIT_FAILURE);
		return;
	}
	L->cursor = L->front;
	L->index = 0;
}	

//moveBack(List L) moves cursor to the back element, does nothing otherwise

void moveBack(List L){
	if(L == NULL){
		return;
	}
	if(length(L) <= 0){
		return;
	}
	L->cursor = L->back;
	L->index = length(L) -1;
}

//movePrev(List L) moves the cursor to the previous node if it is defined and not at the front

void movePrev(List L){
	if(L == NULL){
		return;
	}
	if(L->cursor == NULL){
		return;
	}
	if(L->cursor == L->front){
		L->cursor = NULL;
		L->index = -1;
		return;
	}
	L->cursor = L->cursor->prev;
	L->index -= 1;
}

//moveNext(List L) moves the cursor to the next node if it is defined and not at the back

void moveNext(List L){
	if(L == NULL){
		return;
	}
	if(L->cursor == NULL){
		return;
	}
	if(L->cursor == L->back){
		L->cursor = NULL;
		L->index = -1;
		return;
	}
	L->cursor = L->cursor->next;
	L->index += 1;
}

//prepend(List L, int x) inserts element before the front element in the list

void prepend(List L, int x){
	if(L == NULL){
		printf("List Error: prepend() on a NULL List");
		exit(EXIT_FAILURE);
	}
	Node N = nodeCreate(x);
	
	if(length(L) == 0){
		L->front = N;
		L->back = N;
		if(index(L) >=0){
			L->index += 1;
		}
	}
	else{
		L->front->prev = N;
		N->next = L->front;
		L->front = N;
		if(index(L) >= 0){
			L->index += 1;
		}	
	}
	L->length += 1;
}

//append(List L, int x) adds an element to the back of the list 

void append(List L, int x){
	if(L == NULL){
		printf("List Error: append() on a NULL List");
		exit(EXIT_FAILURE);
	}
	Node N = nodeCreate(x);

	if(length(L) == 0){
		L->front = N;
		L->back = N;
	}
	else{
		L->back->next = N;
		N->prev = L->back;
		L->back = N;
	}
	L->length += 1;
}

//insertBefore(List L, int x) inserts a new element before the cursor node
//pre: length(L) > 0 and index(L) >= 0

void insertBefore(List L, int x){
	if(L == NULL){
		printf("List Error: insertBefore() on a NULL List");
		exit(EXIT_FAILURE);
	}
	if(length(L) <= 0){
		printf("List Error: insertBefore() on a List of length 0");
		exit(EXIT_FAILURE);
	}
	if(index(L) < 0){
		printf("List Error: insertBefore() on a List with invalid cursor index");
		exit(EXIT_FAILURE);
	}
	Node N = nodeCreate(x);
	if(index(L) == 0){
		N->next = L->front;
		L->front->prev = N;
		L->front = N;
	}
	else{
		L->cursor->prev->next = N;
		N->prev = L->cursor->prev;
		N->next = L->cursor;
		L->cursor->prev = N;
	}
	L->length += 1;
	L->index += 1;
}

//insertAfter(List L, int x) inserts a new element after the cursor node
//pre: length(L) > 0 and index(L) >= 0

void insertAfter(List L, int x){
	if(L == NULL){
		printf("List Error: insertAfter() on a NULL List");
		exit(EXIT_FAILURE);
	}
	if(length(L) <= 0){
		printf("List Error: insertAfter() on a List of length 0");
		exit(EXIT_FAILURE);
	}
	if(index(L) < 0){
		printf("List ErrorL insertAfter() on a List with invalid cursor index");
		exit(EXIT_FAILURE);
	}
	Node N = nodeCreate(x);
	if(index(L) == length(L) -1){
		N->prev = L->back;
		L->back->next = N;
		L->back = N;
	}
	else{
		L->cursor->next->prev = N;
		N->next = L->cursor->next;
		N->prev = L->cursor;
		L->cursor->next = N;
	}
	L->length += 1;

}

//deleteFront(List L) deletes the node at the front of the List
//pre: length(L) > 0

void deleteFront(List L){
	if(L == NULL){
		printf("List Error: deleteFront() on a NULL List");
		exit(EXIT_FAILURE);
	}
	if(length(L) <= 0){
		printf("List Error: deleteFront() on a List of length 0");
		exit(EXIT_FAILURE);
	}
	Node N = L->front;
	if(length(L) == 1){
		L->front = NULL;
		L->back = NULL;
		L->cursor = NULL;
		L->index = -1;
	}
	else{
		if(L->front == L->cursor){
			L->index = -1;
			L->cursor = NULL;
			L->front = L->front->next;
		}
		else{
			L->front = L->front->next;
			L->index -= 1;
		}
		
	}
	L->length -= 1;
	freeNode(&N);
}

void deleteBack(List L){
	if(L == NULL){
		printf("List Error: deleteBack() on a NULL List");
		exit(EXIT_FAILURE);
	}
	if(length(L) <= 0){
		printf("List Error: deleteBack() on a List of length 0");
		exit(EXIT_FAILURE);
	}
	//Node N = L->back;
	if(length(L) == 1){
		Node N = L->back;
		L->front = NULL;
		L->back = NULL;
		L->cursor = NULL;
		L->index = -1;
		freeNode(&N);
	}
	else{
		if(L->index == length(L) -1){
			L->index = -1;
			L->cursor = NULL;
			L->back = L->back->prev;
		}
		else{
			L->back = L->back->prev;
		}
	}
	L->length -= 1;
	//freeNode(&N);
}

//delete(List L) deletes the cursor node in L
//pre: length(L) > 0 and index(L) >= 0

void delete(List L){
	if(L == NULL){
		printf("List Error: delete() on a NULL List");
		exit(EXIT_FAILURE);
	}
	if(length(L) <= 0 || index(L) < 0){
		printf("List Error: delete() on a List with invalid length or index");
		exit(EXIT_FAILURE);
	}
	if(L->cursor == L->front){
		deleteFront(L);
	}
	else if(L->cursor == L->back){
		deleteBack(L);
	}
	else{
		Node N = L->cursor;
		L->cursor->prev->next = L->cursor->next;
		L->cursor->next->prev = L->cursor->prev;
		freeNode(&N);
		L->cursor = NULL;
		L->index = -1;		
	}
	L->length -= 1;
}

//copyList(List L) returns new list representing the same sequence as L. Cursor is undefined in the new list
List copyList(List L){
	List A = newList();
	moveFront(L);
	int x;
	while(index(L) >= 0){
		x = get(L);
		append(A, x);
		moveNext(L);
	}
	A->cursor = NULL;
	A->index = -1;
	return A;
}

void printList(FILE* out, List L){
	moveFront(L);
	int x;
	while(index(L) >= 0){
		x = get(L);
		fprintf(out, "%d ", x);
		moveNext(L);
	}
}



int main(void){
	List L = newList();
	append(L, 2);
	append(L, 3);
	prepend(L, 1);
	append(L, 4);
	append(L, 6);
	printList(stdout, L);
	moveFront(L);
	printf("front element is %d\n", L->cursor->value);
	moveNext(L);
	printf("cursor element is %d\n", L->cursor->value);
	moveBack(L);
	printf("back element is %d\n", L->cursor->value);
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

	List A = newList();
	List B = newList();
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
	return 1;
}
