#include <stdio.h>
#include <stdlib.h>
#define MAX 10
int x = 0, y = 0, z = 0;
int i = 0, j = 0, k = 0;

void mem_alloc_3D_double(double**** m3, double n, double r, double c) { //3차원 배열의 주소값과 그 배열의 행,열,층을 입력받는다.
	*m3 = (double***)malloc(sizeof(double**) * n);
	for (i = 0; i < n; i++) {
		*(*m3 + i) = (double**)malloc(sizeof(double*) * r);
		for (j = 0; j < r; j++)
			*(*(*m3 + i) + j) = (double*)malloc(sizeof(double) * c);
	}
}

void addition_3D(double*** a1, double*** a2, double n, double r, double c) {
	double sum[MAX][MAX][MAX] = { 0 };
	for (i = 0; i < n; i++) {
		for (j = 0; j < r; j++) {
			for (k = 0; k < c; k++) {
				sum[i][j][k] = a1[i][j][k] + a2[i][j][k];
				printf("%g ", sum[i][j][k]);
			}
			printf("\n");
		}
		printf("\n\n");
	}
}

void main() {
	//초기화하기
	double n = 2;
	double row = 4;
	double col = 5;

	//Define two matrices A and B using 'mem_alloc_3D_double'
	double*** A;
	double*** B;
	mem_alloc_3D_double(&A, n, row, col);
	mem_alloc_3D_double(&B, n, row, col);

	double cnta = 10;
	double cntb = 10;

	printf("3D Array 'A'\n\n");
	for (i = 0; i < n; i++) {
		for (j = 0; j < row; j++) {
			for (k = 0; k < col; k++) {
				A[i][j][k] = cnta++;
				printf("%g ", A[i][j][k]);
			}
			printf("\n");
		}
		printf("\n");
	}

	printf("\n3D Array 'B'\n\n");
	for (i = 0; i < n; i++) {
		for (j = 0; j < row; j++) {
			for (k = 0; k < col; k++) {
				B[i][j][k] = cntb++;
				printf("%g ", B[i][j][k]);
			}
			printf("\n");
		}
		printf("\n");
	}

	//Perform addtion of two matrices using 'addition_3D()'
	printf("\n3D Array 'Sum'\n\n");
	addition_3D(A, B, n, row, col);


	//Deallocate A
	if (A != NULL)
	{
		for (i = 0; i < n; i++) {
			for (j = 0; j < row; j++)
				free(A[i][j]);
		}
		for (int i = 0; i < n; i++) {
			free(A[i]);
		}
		free(A);

		A = NULL;
	}

	//Deallocate B
	if (B != NULL)
	{
		for (i = 0; i < n; i++) {
			for (j = 0; j < row; j++)
				free(B[i][j]);
		}
		for (int i = 0; i < n; i++) {
			free(B[i]);
		}
		free(B);

		B = NULL;
	}
}