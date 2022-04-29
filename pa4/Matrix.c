#include <stdio.h>
#include <stdlib.h>
#include "List.h"
#include "Matrix.h"

typedef struct EntryObj* Entry;

typedef struct EntryObj{
	int col;
	double value;
}EntryObj;

typedef struct MatrixObj{
	List *Matrix;
	int size;
	int elements;
}MatrixObj;

//Matrix is an array of pointers to Lists
//List is an "array" of nodes that contain pointers to entries
//Matrix->Lists->Nodes->Entries

Entry newEntry(int c, double v){
	Entry E = malloc(sizeof(EntryObj));
	E->col = c;
	E->value = v;
	return E;
}

void freeEntry(Entry *pE){
	if(pE != NULL && *pE != NULL){
		free(*pE);
		*pE = NULL;
	}
}

Matrix newMatrix(int n){
	Matrix M = malloc(sizeof(MatrixObj));
	M->Matrix = malloc((n + 1) * sizeof(List));
	for(int i = 1; i < (n+1); i += 1){
		M->Matrix[i] = newList();
	}
	M->elements = 0;
	M->size = n;
	return M;
}

void freeMatrix(Matrix *pM){
	if(pM != NULL && *pM != NULL){
		for(int i = 1; i < size(*pM) + 1; i += 1){
			//free entries, then free lists
			moveFront((*pM)->Matrix[i]);
			while(index((*pM)->Matrix[i]) >= 0){
				//for each item in the lists free the entry
				Entry E = get((*pM)->Matrix[i]);
				freeEntry(&E);
				E = NULL;
				moveNext((*pM)->Matrix[i]);
			}
			freeList(&(*pM)->Matrix[i]);
		} 
	}
	free((*pM)->Matrix);
	free(*pM);
	*pM = NULL;
}

int size(Matrix M){
	if(M == NULL){
		printf("Matrix Error: size() on a NULL Matrix\n");
		exit(EXIT_FAILURE);
	}
	return M->size;
}

int NNZ(Matrix M){
	if(M == NULL){
		printf("Matrix Error: NNZ() on a NULL Matrix\n");
		exit(EXIT_FAILURE);
	}
	return M->elements;
}

//false = 0, true = 1
int equals(Matrix A, Matrix B){
	if(A == NULL || B == NULL){
		printf("Matrix Error: equals() on a NULL Matrix\n");
		exit(EXIT_FAILURE);
	}
	if(size(A) != size(B) || NNZ(A) != NNZ(B)){
		return 0;
	}
	for(int i = 1; i < (size(A) + 1); i += 1){
		List AL = A->Matrix[i];
		List BL = B->Matrix[i];
		moveFront(AL);
		moveFront(BL);
		while(index(AL) >= 0){
			Entry AE = get(AL);
			Entry BE = get(BL);
			if( (AE->col != BE->col) || (AE->value != BE->value)){
				return 0;
			}
		}
	}
	return 1;
}

void makeZero(Matrix M){
	if(NNZ(M) == 0){
		return;
	}
	for(int i = 1; i < size(M) + 1; i += 1){
		moveFront(M->Matrix[i]);
		while(index(M->Matrix[i]) >= 0){
			Entry E = get(M->Matrix[i]);
			freeEntry(&E);
			E = NULL;
			moveNext(M->Matrix[i]);
		}
	}
	M->elements = 0;
}

void changeEntry(Matrix M, int i, int j, double x){
	if(M == NULL){
		printf("Matrix Error: changeEntry() on a NULL Matrix\n");
		exit(EXIT_FAILURE);
	}
	if(i < 1 || i > size(M)){
		printf("Matrix Error: changeEntry() invalid i value (row)\n");
		exit(EXIT_FAILURE);
	}
	if(j < 1 || j > size(M)){
		printf("Matrix Error: changeEntry() invalid j value (column)\n");
		exit(EXIT_FAILURE);
	}
	//M->Matrix[i] = Current list
	//if x is 0, remove an entry, do with: if x = 0 ... else append entry
	//if column entry already exists, replace value, dont increment M->elements
	//iterate through M->Matrix[i], if list is empty, append new entry
	//otherwise, insert entry in sorted column order
	//increment M->elements when done, unless x is 0, then decrement
}

Matrix copy(Matrix A){
	Matrix M = newMatrix(size(A));
	for(int i = 1; i < size(A) +1; i += 1){
		List L = A->Matrix[i];
		if(length(L) == 0){
			continue;
		}
		moveFront(L);
		while(index(L) >= 0){
			Entry E = get(L);
			//Entry N = newEntry(E->col, E->value);
			//append(M->Matrix[i], N);
			changeEntry(M, i, E->col, E->value);
			moveNext(L);
		}
	}
	return M;
}

int main(void){
	Matrix M = newMatrix(10);
	Matrix R = newMatrix(10);
	if(equals(M, R) == 1){
		printf("Matrices are equal");
	}
	freeMatrix(&R);
	freeMatrix(&M);
}
