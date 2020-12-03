#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "quick_sort.h"
#define SIZE 100

int list[SIZE];

int bin_search_recursive(int key, int low, int high) {
	int mid;
	if (low <= high) {
		mid = (low + high) / 2;
		if (key == list[mid]) // Ž�� ����
			return mid;
		else if (key < list[mid])
			return bin_search_recursive(key, low, mid - 1); // ���� ���� �ٽ� Ž��
		else
			return bin_search_recursive(key, mid + 1, high); // ������ ���� �ٽ� Ž��
	}
	else
		return -1; // Ž�� ����
}

int bin_search_iterative(int key, int low, int high) {
	int mid;
	while (low <= high) {
		mid = (high + low) / 2; // �߰���ġ ���
		if (key == list[mid]) // key�� �߰�
			return mid;
		else if (key > list[mid]) // ���� mid ���ʿ� ������ mid �Ʒ����� ����
			low = mid + 1;
		else // ���� mid �Ʒ��ʿ� ������ mid ������ ����
			high = mid - 1;
	}
	return -1; // Ž�� ����
}

int main(void) {
	srand(time(NULL));
	int key, res;
	for (int i = 0; i < SIZE - 1;i++)
		list[i] = rand() % 1000;
	for (int i = 0;i < SIZE - 1;i++) {
		if (i % 10 == 0)
			putchar('\n');
		printf("%4d", list[i]);
	}
	printf("\n\n<���İ��>\n");
	quick_sort(list, 0, SIZE - 1); //quick���� ȣ��
	for (int i = 0;i < SIZE - 1;i++) {
		if (i % 10 == 0)
			putchar('\n');
		printf("%4d", list[i]);
	}
	printf("\n\nInput key to search: ");
	scanf("%d", &key);
	printf("\n<���ȣ����>\n");
	res = bin_search_recursive(key, 0, SIZE - 1);
	if (res != -1)
		printf("%d is found in position %d\n", key, res);
	else
		printf("search failed\n");
	printf("\n<�ݺ�ȣ����>\n");
	res = bin_search_iterative(key, 0, SIZE - 1);
	if (res != -1)
		printf("%d is found in position %d\n", key, res);
	else
		printf("search failed\n");
}