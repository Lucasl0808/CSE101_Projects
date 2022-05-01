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
			moveNext(AL);
			moveNext(BL);
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
	List L = M->Matrix[i];
	if(x == 0.0){
		if(length(L) == 0){
			return;
		}
		else{
			moveFront(L);
			while(index(L) >= 0){
				Entry E = get(L);
				if(E->col == j){
					freeEntry(&E);
					delete(L);
					M->elements -= 1;
					return;
				}
				moveNext(L);
			}
			return;
		}
	}
	else{
		if(length(L) == 0){
			Entry E = newEntry(j, x);
			append(L, E);
			M->elements += 1;
			return;
		}
		else{
			moveFront(L);
			while(index(L) >= 0){
				Entry E = get(L);
				if(E->col == j){
					E->value = x;
					return;
				}
				if(j < E->col){
					Entry R = newEntry(j, x);
					insertBefore(L, R);
					M->elements += 1;
					return;
				}
				moveNext(L);
			}
			if(index(L) == -1){
				Entry R = newEntry(j, x);
				append(L, R);
				M->elements += 1;
				return;
			}
		}
	}
	//if column entry already exists, replace value, dont increment M->elements
	//iterate through M->Matrix[i], if list is empty, append new entry
	//otherwise, insert entry in sorted column order
	//increment M->elements when done, unless x is 0, then decrement
}

Matrix copy(Matrix A){
	if(A == NULL){
		printf("Matrix Error: copy() on a NULL Matrix");
		exit(EXIT_FAILURE);
	}
	Matrix M = newMatrix(size(A));
	for(int i = 1; i < size(A) +1; i += 1){
		List L = A->Matrix[i];
		if(length(L) == 0){
			continue;
		}
		moveFront(L);
		while(index(L) >= 0){
			Entry E = get(L);
			Entry N = newEntry(E->col, E->value);
			append(M->Matrix[i], N);
			M->elements += 1;
			//changeEntry(M, i, E->col, E->value);
			moveNext(L);
		}
	}
	return M;
}

void printMatrix(FILE* out, Matrix M){
	fprintf(out, "Matrix size = %d\n", size(M));
	fprintf(out, "NNZ Matrix = %d\n", NNZ(M));
	for(int i = 1; i < size(M) + 1; i += 1){
		List L = M->Matrix[i];
		if(length(L) == 0){
			continue;
		}
		moveFront(L);
		fprintf(out, "%d: ", i);
		while(index(L) >= 0){
			Entry E = get(L);
			fprintf(out, "(%d, %.1f) ", E->col, E->value);
			moveNext(L);
		}
		fprintf(out, "\n");
	}
}

Matrix transpose(Matrix A){
	Matrix M = newMatrix(size(A));
	for(int i = 1; i < size(A) + 1; i += 1){
		List L = A->Matrix[i];
		if(length(L) == 0){
			continue;
		}
		moveFront(L);
		while(index(L) >= 0){
			Entry E = get(L);
			Entry N = newEntry(i, E->value);
			append(M->Matrix[E->col], N);
			M->elements += 1;
			moveNext(L);
		}
	}
	return M;
}


Matrix scalarMult(double x, Matrix A){
	if(A == NULL){
		printf("Matrix Error: scalarMult() on a NULL Matrix\n");
		exit(EXIT_FAILURE);
	}
	Matrix M = newMatrix(size(A));
	for(int i = 1; i < size(A) + 1; i += 1){
		List L = A->Matrix[i];
		if(length(L) == 0){
			continue;
		}
		moveFront(L);
		while(index(L) >= 0){
			Entry E = get(L);
			double y = (E->value * x);
			Entry N = newEntry(E->col, y);
			append(M->Matrix[i], N);
			M->elements += 1;
			moveNext(L);
		}
	}
	return M;
}

Matrix sum(Matrix A, Matrix B){
	if(A == NULL || B == NULL){
		printf("Matrix Error: sum() on a NULL Matrix A or B\n");
		exit(EXIT_FAILURE);
	}
	if(size(A) != size(B)){
		printf("Matrix Error: sum() matrices are of unequal size\n");
		exit(EXIT_FAILURE);
	}
	
	Matrix M = newMatrix(size(A));
	for(int i = 1; i < size(A) + 1; i += 1){
		List AL = A->Matrix[i];
		List BL = B->Matrix[i];
		//if current list in Matrix A is empty 
		if(length(AL) == 0){
			if(length(BL) == 0){
				continue;
			}
			else{
				moveFront(BL);
				while(index(BL) >= 0){
					Entry E = get(BL);
					Entry N = newEntry(E->col, E->value);
					append(M->Matrix[i], N);
					M->elements += 1;
					moveNext(BL);
				}
			}
		}
		//if current list in Matrix B is empty
		else if(length(BL) == 0){
			if(length(AL) != 0){
				moveFront(AL);
				while(index(AL) >= 0){
					Entry F = get(AL);
					Entry P = newEntry(F->col, F->value);
					append(M->Matrix[i], P);
					M->elements +=1;
					moveNext(AL);
				}
			}
		}
		//if both are NOT empty
		else{
			moveFront(AL);
			moveFront(BL);
			while(index(AL) >= 0 && index(BL) >= 0){
				if(index(AL) == -1){
					while(index(BL) >= 0){
						Entry BE = get(BL);
						Entry new = newEntry(BE->col, BE->value);
						append(M->Matrix[i], new);
						M->elements += 1;
						moveNext(BL);
					}
					break;
				}
				if(index(BL) == -1){
					while(index(AL) >= 0){
						Entry AE = get(AL);
						Entry new = newEntry(AE->col, AE->value);
						append(M->Matrix[i], new);
						M->elements += 1;
						moveNext(AL);
					}
					break;
				}
				Entry AE = get(AL);
				Entry BE = get(BL);
				if(AE->col == BE->col){
					//left off here
					double v = (AE->value + BE->value);
					Entry new = newEntry(AE->col, v);
					append(M->Matrix[i], new);
					M->elements += 1;
					moveNext(AL);
					moveNext(BL);
					if(v == 0.0){
						freeEntry(&new);
						deleteBack(M->Matrix[i]);
						M->elements -= 1;
						continue;
					}
				}
				else if(AE->col < BE->col){
					Entry new = newEntry(AE->col, AE->value);
					append(M->Matrix[i], new);
					M->elements += 1;
					moveNext(AL);
				}
				else if(BE->col < AE->col){
					Entry new = newEntry(BE->col, BE->value);
					append(M->Matrix[i], new);
					M->elements += 1;
					moveNext(BL);
				}
			}
		}
	}
	return M;
}

Matrix diff(Matrix A, Matrix B){
	if(A == NULL || B == NULL){
		printf("Matrix Error: sum() on a NULL Matrix A or B\n");
		exit(EXIT_FAILURE);
	}
	if(size(A) != size(B)){
		printf("Matrix Error: sum() matrices are of unequal size\n");
		exit(EXIT_FAILURE);
	}
	
	Matrix M = newMatrix(size(A));
	for(int i = 1; i < size(A) + 1; i += 1){
		List AL = A->Matrix[i];
		List BL = B->Matrix[i];
		//if list in matrix A is empty, add all values of B with swapped signs
		if(length(AL) == 0){
			if(length(BL) == 0){
				continue;
			}
			else{
				moveFront(BL);
				while(index(BL) >= 0){
					Entry E = get(BL);
					double val = (-1 * E->value);
					Entry N = newEntry(E->col, val);
					append(M->Matrix[i], N);
					M->elements += 1;
					moveNext(BL);
				}
			}
		}
		else if(length(BL) == 0){
			moveFront(AL);
			while(index(AL) >= 0){
				Entry E = get(AL);
				Entry N = newEntry(E->col, E->value);
				append(M->Matrix[i], N);
				M->elements += 1;
				moveNext(AL);
			}
		}
		else{
			moveFront(AL);
			moveFront(BL);
			while(index(AL) >= 0 && index(BL) >= 0){
				if(index(AL) == -1){
					while(index(BL) >= 0){
						Entry BE = get(BL);
						double val = (-1 * BE->value);
						Entry new = newEntry(BE->col, val);
						append(M->Matrix[i], new);
						M->elements += 1;
						moveNext(BL);
					}
					break;
				}
				if(index(BL) == -1){
					while(index(AL) >= 0){
						Entry AE = get(AL);
						Entry new = newEntry(AE->col, AE->value);
						append(M->Matrix[i], new);
						M->elements += 1;
						moveNext(AL);
					}
					break;
				}
				Entry AE = get(AL);
				Entry BE = get(BL);
				if(AE->col == BE->col){
					double v = (AE->value - BE->value);
					Entry new = newEntry(AE->col, v);
					append(M->Matrix[i], new);
					M->elements += 1;
					moveNext(AL);
					moveNext(BL);
					if(v == 0.0){
						freeEntry(&new);
						deleteBack(M->Matrix[i]);
						M->elements -= 1;
						continue;
					}
				}
				else if(AE->col < BE->col){
					Entry new = newEntry(AE->col, AE->value);
					append(M->Matrix[i], new);
					M->elements += 1;
					moveNext(AL);
				}
				else if(BE->col < AE->col){
					double v = (BE->value * -1);
					Entry new = newEntry(BE->col, v);
					append(M->Matrix[i], new);
					M->elements += 1;
					moveNext(BL);
				}
			}
		}
	}
	return M;
}


int main(void){
	Matrix M = newMatrix(10);
	Matrix R = newMatrix(10);
	Matrix B = newMatrix(10);
	changeEntry(B, 1, 1, 1);
	changeEntry(B, 1, 3, 1);
	changeEntry(B, 3, 1, 1);
	changeEntry(B, 3, 2, 1);
	changeEntry(B, 3, 3, 1);
	changeEntry(R, 1, 1, 1);
	changeEntry(R, 1, 2, 2);
	changeEntry(R, 1, 3, 3);
	changeEntry(R, 2, 1, 4);
	changeEntry(R, 2, 2, 5);
	changeEntry(R, 2, 3, 6);
	changeEntry(R, 3, 1, 7);
	changeEntry(R, 3, 2, 8);
	changeEntry(R, 3, 3, 9);
	Matrix C = copy(R);
	if(equals(C, R) == 1){
		printf("Matrices are equal\n");
	}
	Matrix S = scalarMult(1.5, R);
	Matrix T = transpose(R);
	Matrix Sum = sum(R, B);
	Matrix SelfDiff = diff(R, R);
	Matrix Diff = diff(R, B);
	printMatrix(stdout, R);
	printMatrix(stdout, S);
	printMatrix(stdout, T);
	printMatrix(stdout, Sum);
	printMatrix(stdout, SelfDiff);
	printMatrix(stdout, Diff);
	freeMatrix(&SelfDiff);
	freeMatrix(&Diff);
	freeMatrix(&Sum);
	freeMatrix(&B);
	freeMatrix(&S);
	freeMatrix(&T);
	freeMatrix(&C);
	freeMatrix(&R);
	freeMatrix(&M);
}

