/* Lucas Lee
 * luclee
 * pa4
 * CSE101-02 Spring 2022
 */
#include <stdio.h>
#include <stdlib.h>
#include "List.h"
#include "Matrix.h"

int main(int argc, char *argv[]){
	if(argc != 3){
		fprintf(stderr, "Usage: %s <input file> <output file>\n", argv[0]);
		exit(1);
	}
	FILE *in, *out;
	in = fopen(argv[1], "r");
	if(in == NULL){
		printf("Unable to open file %s for reading\n", argv[1]);
		exit(1);
	}
	out = fopen(argv[2], "w");
	if(out == NULL){
		printf("Unable to open file %s for writing\n", argv[2]);
		exit(1);
	}
	int n;
	int Alines;
	int Blines;
	fscanf(in, "%d %d %d\n", &n, &Alines, &Blines);
	Matrix A = newMatrix(n);
	for(int i = 0; i < Alines; i += 1){
		int row;
		int col;
		double val;
		fscanf(in, "%d %d %lf", &row, &col, &val);
		changeEntry(A, row, col, val);
	}
	fscanf(in, "\n");
	Matrix B = newMatrix(n);
	for(int i = 0; i < Blines; i += 1){
		int Brow;
		int Bcol;
		double Bval;
		fscanf(in, "%d %d %lf", &Brow, &Bcol, &Bval);
		changeEntry(B, Brow, Bcol, Bval);
	}
	fprintf(out, "A has %d non-zero entries:\n", Alines);
	printMatrix(out, A);
	fprintf(out, "\n");
	fprintf(out, "B has %d non-zero entries:\n", Blines);
	printMatrix(out, B);
	fprintf(out, "\n");
	fprintf(out, "(1.5)*A =\n");
	Matrix ScalarMult = scalarMult(1.5, A);
	printMatrix(out, ScalarMult);
	fprintf(out, "\n");
	Matrix ApB = sum(A, B);
	fprintf(out, "A+B =\n");
	printMatrix(out, ApB);
	fprintf(out, "\n");
	Matrix ApA = sum(A, A);
	fprintf(out, "A+A =\n");
	printMatrix(out, ApA);
	fprintf(out, "\n");
	fprintf(out, "B-A =\n");
	Matrix BmA = diff(B, A);
	printMatrix(out, BmA);
	fprintf(out, "\n");
	fprintf(out, "A-A =\n");
	Matrix AmA = diff(A, A);
	printMatrix(out, AmA);
	fprintf(out, "\n");
	fprintf(out, "Transpose(A) =\n");
	Matrix Transpose = transpose(A);
	printMatrix(out, Transpose);
	fprintf(out, "\n");
	fprintf(out, "A*B =\n");
	Matrix AB = product(A, B);
	printMatrix(out, AB);
	fprintf(out, "\n");
	fprintf(out, "B*B =\n");
	Matrix BB = product(B, B);
	printMatrix(out, BB);
	freeMatrix(&A);
	freeMatrix(&B);
	freeMatrix(&ScalarMult);
	freeMatrix(&ApB);
	freeMatrix(&ApA);
	freeMatrix(&BmA);
	freeMatrix(&AmA);
	freeMatrix(&Transpose);
	freeMatrix(&AB);
	freeMatrix(&BB);
	fclose(in);
	fclose(out);
}
