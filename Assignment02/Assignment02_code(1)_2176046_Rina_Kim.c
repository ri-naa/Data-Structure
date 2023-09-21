#include <stdio.h>
#define MAX_TERMS 100
typedef struct {
	int row;
	int col;
	int value;
}element;

typedef struct SparseMatrix {
	element data[MAX_TERMS];
	int rows;
	int cols;
	int terms;
}SparseMatrix;

//trans
SparseMatrix matrix_trans(SparseMatrix a) 
{
	SparseMatrix ta;

	//a의 cols, rows를 각각 ta의 rows, cols에 바꿔서 저장하고, a의 terms는 그대로 ta의 terms에 저장한다.
	ta.rows = a.cols;
	ta.cols = a.rows;
	ta.terms = a.terms;

	//a.cols(ta.rows)를 오름차순으로 정렬해서 ta에 저장
	int ind = 0; //index

	for (int i = 0; i < ta.rows; i++) {
		for (int j = 0; j < ta.terms; j++) {
			if (a.data[j].col == i) {
				ta.data[ind] = a.data[j];
				ind++;
			}
		}
	}

	//ta에 data.row <-> data.col 위치 바꿔서 저장
	int temp = 0;
	for (int i = 0; i < ta.terms; i++) {
		temp = ta.data[i].col;
		ta.data[i].col = ta.data[i].row;
		ta.data[i].row = temp;
	}

	return ta;
}

void main()
{
	//Add B as an input Use your own example freely SparseMatrix b = ;
	SparseMatrix B = {
		{{0,3,7},{1,0,9},{1,5,8},{3,0,6},{3,1,5},{4,5,1},{5,2,2}}, 6, 6, 7
	};

	//Perform the transpose operation
	SparseMatrix tB;
	tB = matrix_trans(B);


	//Print out B in a dense matrix form to check
	printf("Sparse Matrix B\n");
	for (int i = 0; i < B.terms; i++) {
		printf("(%d, %d, %d) \n", B.data[i].row, B.data[i].col, B.data[i].value);
	}

	printf("\n");
	
	//값이 정리된 '구조체 SparseMatrix B'를 이용해 원래 sparse matrix로 출력하기
	int cnt = 0; //몇번째 terms인지 세는 변수
	for (int i = 0; i < B.rows; i++) {
		for (int j = 0; j < B.cols; j++) {
			if ((B.data[cnt].row == i) && (B.data[cnt].col == j)) {
				printf("%d ", B.data[cnt].value);
				cnt++;
			}
			else
				printf("%d ", 0);
			if (j == B.cols-1)
				printf("\n");
		}
	}

	//Print out B^T in a dense matrix form to check
	printf("\nSparse Matrix B^T\n");
	for (int i = 0; i < tB.terms; i++) {
		printf("(%d, %d, %d) \n", tB.data[i].row, tB.data[i].col, tB.data[i].value);
	}

	printf("\n");
	cnt = 0;

	//값이 정리된 '구조체 SparseMatrix tB'를 이용해 sparse matrix의 전치행렬을 출력하기
	for (int i = 0; i < tB.rows; i++) {
		for (int j = 0; j < tB.cols; j++) {
			if ((tB.data[cnt].row == i) && (tB.data[cnt].col == j)) {
				printf("%d ", tB.data[cnt].value);
				cnt++;
			}
			else
				printf("%d ", 0);
			if (j == tB.cols-1)
				printf("\n");
		}
	}
}