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
		if (key == list[mid]) // 탐색 성공
			return mid;
		else if (key < list[mid])
			return bin_search_recursive(key, low, mid - 1); // 왼쪽 절반 다시 탐색
		else
			return bin_search_recursive(key, mid + 1, high); // 오른쪽 절반 다시 탐색
	}
	else
		return -1; // 탐색 실패
}

int bin_search_iterative(int key, int low, int high) {
	int mid;
	while (low <= high) {
		mid = (high + low) / 2; // 중간위치 계산
		if (key == list[mid]) // key값 발견
			return mid;
		else if (key > list[mid]) // 값이 mid 위쪽에 있으면 mid 아래쪽을 버림
			low = mid + 1;
		else // 값이 mid 아래쪽에 있으면 mid 위쪽을 버림
			high = mid - 1;
	}
	return -1; // 탐색 실패
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
	printf("\n\n<정렬결과>\n");
	quick_sort(list, 0, SIZE - 1); //quick정렬 호출
	for (int i = 0;i < SIZE - 1;i++) {
		if (i % 10 == 0)
			putchar('\n');
		printf("%4d", list[i]);
	}
	printf("\n\nInput key to search: ");
	scanf("%d", &key);
	printf("\n<재귀호출결과>\n");
	res = bin_search_recursive(key, 0, SIZE - 1);
	if (res != -1)
		printf("%d is found in position %d\n", key, res);
	else
		printf("search failed\n");
	printf("\n<반복호출결과>\n");
	res = bin_search_iterative(key, 0, SIZE - 1);
	if (res != -1)
		printf("%d is found in position %d\n", key, res);
	else
		printf("search failed\n");
}