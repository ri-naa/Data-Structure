#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "time.h"
#include "math.h"

#define SIZE 1000
#define range 64

bool check_sort_results(int output[], int n) {
	bool index = 1;
	for (int i = 0; i < n - 1; i++)
		if (output[i] > output[i + 1])
		{
			index = 0;
			break;
		}
	return index;
}

void counting_sort(int a[], int list[ ], int b[]) {
	int c[range]; 
	//initialize
	for (int i = 0; i < range; i++) {
		c[i] = 0;
	}
	for (int j = 0; j < SIZE; j++) {
		c[a[j]] ++;
	}
	for (int i = 1; i < range; i++) {
		c[i] = c[i] + c[i - 1];
	}
	for (int j = SIZE - 1; j >= 0; j--) { 
		b[c[a[j]] - 1] = list[j];
		c[a[j]] --;
	}
}

void radix_sort(int list[], int result[], int d) {
	int a[SIZE];
	for (int i = 0; i < d; i++) {
		for (int j = 0; j < SIZE; j++) 
			a[j] = (list[j] >> (6 * i)) & 63;
		counting_sort(a, list, result);
		for (int j = 0; j < SIZE; j++)
			list[j] = result[j];
	}
}

int main(void) {
	int list[SIZE]; 
	int result[SIZE];
	//·£´ý »ý¼º
	int p = pow(2, 12);
	for (int i = 0; i < SIZE; i++) {
		//int q = rand() % p;
		list[i] = (rand() % p) * (rand() % p);
	}

	radix_sort(list, result, 4);

	for (int i = 0; i < SIZE; i++)
		printf("%d\n", result[i]);

	if (check_sort_results(result, SIZE))
		printf("\n\nSorting result is correct.\n");
	else
		printf("\n\nSorting result is wrong.\n");
}