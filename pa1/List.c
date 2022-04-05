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

//delete the front element of the list until the list is empty 
//when the list is empty, free the list and set its pointer to NULL
void freeList(List* pL){
	if(pL != NULL && *pL != NULL){
		while(length(*pL) > 0){
			deleteFront(*pL);
		}
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
	while(L->front != NULL){
		freeNode((*L)->front);
		L->front = L->next;
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
		L->length += 1;
		if(index(L) >=0){
			L->index += 1;
		}
	}
	else{
		L->front->prev = N;
		N->next = L->front;
		L->front = N;
		L->length += 1;
		if(index(L) >= 0){
			L->index += 1;
		}	
	}
}


