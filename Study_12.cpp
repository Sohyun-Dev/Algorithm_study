#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "quick_sort.h"
#define SIZE 100
#define INDEX_SIZE 100

typedef struct { // itable ����
	int key;
	int index;
} itable;
itable index_list[INDEX_SIZE]; // index tabel

int list[SIZE]; // ���������� ���� �����Ͱ� ���ִ� ����Ʈ ����

int seq_search(int key, int low, int high) { // sequential search �Լ� ����
	int i;
	for (int i = low;i <= high;i++)
		if (list[i] == key)
			return i;
	return -1;
}

void makeIndexTable(int size, int interval) { // indextable ����� �Լ� ����
	int i, n;
	n = size / interval; // n�� ��ü ����� ����ڷκ��� �Է¹��� interval�� ���� ��
	if (size % interval > 0)
		n = n + 1;
	for (i = 0;i < n;i++) {
		index_list[i].index = i * interval;//index_list�� index�� ����
		index_list[i].key = list[i * interval]; // index_list�� key�� ����
	}
	printf("\n\n<Index tabel>\n");
	for (i = 0;i < n;i++) { // �ݺ����� �̿��Ͽ� i��° index_list�� key�� ���
		printf("%3d:%4d\n", i, index_list[i].key);
	}
}

int index_search(int key, int n) { // indexed_search �Լ� ����
	int i, low, high;
	if (key<list[0] || key>list[n - 1]) // list�� ���� ���� ��� �Լ� ����
		return -1;
	for (i = 0;i < n;i++)
		if (index_list[i].key <= key && index_list[i + 1].key > key) { // �ش�Ű�� ���Ե� ��ġ ã��
			printf("index location : %d\n", i); // �ش�Ű ���Ե� ��ġ ���
			break;
		}
	if (i == n) { // ���������� i�� ������ ��� ������ index ������ key ���Ե� ���
		low = index_list[i - 1].index;
		high = n;
	}
	else { // Ư�� index i~i+1 ���̿� key ���Ե� ���
		low = index_list[i].index;
		high = index_list[i + 1].index;
	}
	return seq_search(key, low, high); //sequence search ������ ��������
}

int main(void) {
	srand(time(NULL));
	int key, res, interval;
	for (int i = 0;i < SIZE;i++)
		list[i] = rand() % 1000; // ����Ʈ�� 0~999������ ������ ���ڸ� ����
	for (int i = 0;i < SIZE;i++) { //list ���
		if (i % 10 == 0)
			putchar('\n');
		printf("%4d", list[i]);
	}
	printf("\n\n<���İ��>\n");
	quick_sort(list, 0, SIZE); // quick_sort�� �̿��Ͽ� ��������
	for (int i = 0;i < SIZE;i++) { // ���ĵ� list �ٽ� ���
		if (i % 10 == 0)
			putchar('\n');
		printf("%4d", list[i]);
	}
	printf("\n\nInput index interval(1~100)");
	scanf("%d", &interval);// ����ڷκ��� interval�� �Է¹���
	makeIndexTable(SIZE, interval); // index table ����
	printf("\n\nInput key to search:"); // ����ڷκ��� �˻��� key�� �Է¹���
	scanf("%d", &key);
	printf("\n<Indexed_search���>\n");
	res = index_search(key, INDEX_SIZE);
	if (res != -1) // res�� -1�� �ƴ� ���� ã�� ���
		printf("%d is found in position %d\n", key, res);
	else // res�� -1�� ���� ã�� ������ ���
		printf("search failed\n");
}