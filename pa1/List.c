#include "List.h"
#include <stdio.h>
#include <stdlib.h>


//Maybe include node struct definintion at the top of this file for private var
//Remove from .h file

List newList(void){
	List L = malloc(sizeof(List));
	L->length = 0;
	L->index = -1;
	L->front = NULL;
	L->back = NULL;
	L->listElement = NULL;
	return L;
}

Node newNode(void){
	Node N = malloc(sizeof(Node));
	N->next = NULL;
	N->prev = NULL;
	N->value = 0;
	return N;
}
//find a way to free nodes per list
void freeList(List* pL){
	for(int i = 0; i < length(*pL); i +=1){
		free(pL->
	}
}
