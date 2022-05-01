#include <stdio.h>
#include <stdlib.h>
#include "List.h"
#include "Matrix.h"

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
	Matrix T = transpose(B);
	Matrix Sum = sum(R, B);
	Matrix SelfDiff = diff(R, R);
	Matrix Diff = diff(R, B);
	Matrix Mult = product(R, B);
	printMatrix(stdout, R);
	printMatrix(stdout, S);
	printMatrix(stdout, T);
	printMatrix(stdout, Sum);
	printMatrix(stdout, SelfDiff);
	printMatrix(stdout, Diff);
	printMatrix(stdout, Mult);
	freeMatrix(&Mult);
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
/*
	Matrix A = newMatrix(10);
changeEntry(A, 1, 1, 4);
    changeEntry(A, 1, 2, 2);
    changeEntry(A, 1, 3, 0);
    changeEntry(A, 2, 1, 2);
    changeEntry(A, 3, 1, 0);
    changeEntry(A, 2, 2, 2);
    changeEntry(A, 3, 3, 0);
    Matrix pC = scalarMult(-20, A);
    if (NNZ(pC) != 4){
      printf("Fails Test 1\n");
	printMatrix(stdout, pC);
	printf("\n");
	}
    makeZero(A);
    Matrix pD = scalarMult(-20, A);
	printMatrix(stdout, A);
    if (NNZ(pD) != 0){
      printf("Fails Test 2\n");
	printMatrix(stdout, pD);
	printf("\n");
	}
    return 0;
}

	Matrix A = newMatrix(10);
	changeEntry(A, 1, 1, 4);
	changeEntry(A, 1, 2, 2);
	changeEntry(A, 1, 3, 0);
	changeEntry(A, 2, 1, 2);
	changeEntry(A, 3, 1, 0);
    changeEntry(A, 2, 2, 2);
    changeEntry(A, 3, 3, 0);
    Matrix pC = sum(A, A);
    if (NNZ(pC) != 4 || NNZ(A) != 4){
	printf("fails Test 1\n");
	printf("NNZ(pC) = %d, NNZ(A) = %d\n", NNZ(pC), NNZ(A));
	}
	Matrix Bs = newMatrix(10);
    changeEntry(Bs, 1, 1, -4);
    changeEntry(Bs, 1, 2, 0);
    changeEntry(Bs, 2, 1, 0);
    changeEntry(Bs, 2, 2, -2);
    changeEntry(Bs, 2, 4, 2);
    changeEntry(Bs, 3, 1, 0);
    changeEntry(Bs, 3, 2, 2);
    changeEntry(Bs, 7, 8, 5);
	printf("\n");
	printMatrix(stdout, A);
	printf("\n");
	printMatrix(stdout, Bs);
	printf("\n");
    Matrix pD = sum(A, Bs);
	printMatrix(stdout, pD);
    if (NNZ(pD) != 5){
	printf("fails Test 2\n");
	printf("NNZ(pD) = %d\n", NNZ(pD));
	}
    return 0;
*/



