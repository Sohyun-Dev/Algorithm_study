#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "quick_sort.h"
#define SIZE 100
#define INDEX_SIZE 256

typedef struct { // itable ����
	int key;
	int index;
}itable;
itable index_list[INDEX_SIZE]; // index table ����

int list[SIZE];

int interpol_search(int key, int n) {
	int j, low, high;
	low = 0;
	high = n - 1;
	while ((list[high] >= key) && (key > list[low])) {
		j = ((float)(key - list[low]) / (list[high] - list[low]) * (high - low)) + low; // Ž����ġ ���
		if (key > list[j]) // ���� ��ġ�� �������� high, low ����
			low = j + 1;
		else if (key < list[j])
			high = j - 1;
		else
			low = j;
	}
	if (list[low] = key) // Ž�� ����
		return low;
	else // Ž�� ����
		return -1;
}

int main(void) {
	srand(time(NULL));
	int key, res;
	for (int i = 0;i < SIZE;i++)
		list[i] = rand() % 1000;
	for (int i = 0;i < SIZE;i++) {
		if (i % 10 == 0)
			putchar('\n');
		printf("%4d", list[i]);
	}
	printf("\n\n<���İ��>\n");
	quick_sort(list, 0, SIZE); // quick ���� ȣ��
	for (int i = 0;i < SIZE;i++) {
		if (i % 10 == 0)
			putchar('\n');
		printf("%4d", list[i]);
	}
	printf("\n\nInput key to search:");
	scanf("%d", &key);
	printf("\n<interpolation_search���>\n");
	res = interpol_search(key, SIZE);
	if (res != -1)
		printf("%d is found in position %d\n", key, res);
	else
		printf("search failed\n");
}