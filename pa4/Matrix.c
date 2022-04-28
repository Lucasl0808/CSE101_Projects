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
	for(int i = 1; i < size(A) + 1; i += 1){
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
}


