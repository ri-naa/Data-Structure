#include <stdio.h>

void swap(int* a, int* b) {
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

int Decrease_key_min_heap(int A[], int i, int key) {
	if (key >= A[i]) {
		printf("new key is not larger than current key");
		return 1;
	}

	A[i] = key;
	int parent = i / 2;
	while (i > 1 && A[parent] > A[i]) {
		swap(&A[parent], &A[i]);
		i = parent;
		parent = i / 2;
	}
}

int Increase_key_min_heap(int A[], int i, int key, int size) {
	if (key <= A[i]) {
		printf("new key is not smaller than current key");
		return 1;
	}

	A[i] = key;
	int child = 2 * i;
	while (child <= size) {
		if ((child < size) && A[child] > A[child + 1])
			child++;
		if (A[i] <= A[child]) break;
		swap(&A[i], &A[child]);
		i = child;
		child = 2 * i;
	}
}

void main() {
	//heap의 첫번째는 비어있으므로
	int A[11] = { 0,1,4,2,7,5,3,3,7,8,9 };
	int size = sizeof(A) / sizeof(A[0]) - 1;
	Decrease_key_min_heap(A, 4, 3);
	Increase_key_min_heap(A, 3, 10, size);

	for (int i = 1; i <= 10; i++) {
		printf("[%d] %d\n", i, A[i]);
	}
}