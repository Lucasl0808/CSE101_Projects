#include "List.h"
#include <stdio.h>
#include <stdlib.h>

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


