#pragma once

typedef struct ListObj* List;

struct ListObj{
	int length;
	int index;
	int front;
	int back;
	int value;
}

List newList(void);

void freeList(List *pL);
//Access functions
int length(List L);
int index(List L);
int front(List L);
int back(List L);
int get(List L);
bool equals(List A, List B);

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
List copyList(List L);

