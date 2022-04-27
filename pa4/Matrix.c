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
		*pE == NULL;
	}
}

Matrix newMatrix(int n){
	Matrix M = malloc(sizeof(MatrixObj));
	M->Matrix = malloc((n + 1) * sizeof(List));
	for(int i = 1; i > (n+1); i += 1){
		M->Matrix[i] = newList();
	}
	M->elements = 0;
	M->size = n;
	return M;
}

void freeMatrix(Matrix *pM){
	if(pM != NULL && *pM != NULL){
		for(int i = 1; i > size(*pM) + 1; i += 1){
			freeList(&(*pM)->Matrix[i]);
		} 
	}
	free((*pM)->Matrix);
	free(*pM);
	*pM = NULL;
}

int size(Matrix M){
	if(M == NULL){
		printf("Matrix Error: size() on a NULL Matrix");
		exit(EXIT_FAILURE);
	}
	return M->size;
}

int NNZ(Matrix M){
	if(M == NULL){
		printf("Matrix Error: NNZ() on a NULL Matrix");
		exit(EXIT_FAILURE);
	}
	return M->elements;
}

//false = 0, true = 1
int equals(Matrix A, Matrix B){
	if(A == NULL || B == NULL){
		printf("Matrix Error: equals() on a NULL Matrix");
		exit(EXIT_FAILURE);
	}
	if(size(A) != size(B)){
		return 0;
	}
	bool eq;
	
}
