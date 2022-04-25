#pragma once
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
typedef struct ListObj* List;
typedef struct NodeObj* Node;

List newList(void);
void freeList(List *pL);

//Access functions
void* length(List L);
void* index(List L);
void* front(List L);
void* back(List L);
void* get(List L);
//bool equals(List A, List B);

//Manipulation procedures
void clear(List L);
void set(List L, int x);
void moveFront(List L);
void moveBack(List L);
void movePrev(List L);
void moveNext(List L);
void prepend(List L, int x);
void append(List L, int x);
void insertBefore(List L, int x);
void insertAfter(List L, int x);
void deleteFront(List L);
void deleteBack(List L);
void delete(List L);

//Other Operations
void printList(FILE *out, List L);
//List copyList(List L);

