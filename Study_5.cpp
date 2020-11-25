#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_SIZE 10
#define SWAP(x,y,t) ((t)=(x), (x)=(y), (y)=(t)) // switch�� ���� ��ũ�η� swap ����

int partition(int list[], int left, int right, int num) { // �����ϴ� �Լ�
	int pivot = list[left]; // pivot�� �ʱⰪ�� list�� left��
	printf("* pivot: %d\n", pivot); // pivot �� ���
	int temp, low, high;
	low = left; // low�� high�� �ʱⰪ ����
	high = right + 1;
	do {
		do
			low++; // ������Ų ������ ���� üũ
		while (list[low] < pivot); // left ���� ��Һ��� �����ϸ鼭 pivot �� �̻��� ��� ã��
		do
			high--; // ���ҽ�Ų ������ ���� üũ
		while (list[high] > pivot); // right���� �ٿ����鼭 pivot �� ������ ��� ã��
		if (low < high) SWAP(list[low], list[high], temp); // �� ��� switch
	} while (low < high); // low�� high�� ������ �� ���� �ݺ�
	SWAP(list[left], list[high], temp); // pivot�� �߾ӿ� ��ġ��Ŵ(���̳� ��ġ - high�� ����Ű�� ������ �̵�)
	for (int i = 0;i < num;i++) // list ���
		printf("%d ", list[i]);
	printf("\n");
	printf("left size: %d    right size: %d\n", low - left - 1, right - high); // �ܰ踶�� left�� right�� ������ ���
	return high; // pivot ��ġ ��ȯ
}

void quick_sort(int list[], int left, int right, int num) { //quick_sort �Լ�
	if (left < right) { // left�� right���� ���� ����
		int p = partition(list, left, right, num); // partition ȣ���ؼ� pivot ã��
		quick_sort(list, left, p - 1, num); // pivot �߽����� pivot �ٷ� �ձ��� ��� ȣ��
		quick_sort(list, p + 1, right, num); // pivot �߽����� pivot �������� ������ ���ȣ��
	}
}

int main(void) {
	int i, n;
	printf("Input size of list(1~10):");
	scanf("%d", &n); // ����ڷκ��� 1~10������ ���ڸ� �Է¹���
	int list[MAX_SIZE];
	printf("Input %d numbers in the list\n", n);
	for (i = 0;i < n;i++)
		scanf("%d", &list[i]); // ����ڷκ��� ����Ʈ�� ���� �Է¹���
	printf("\n<Before sorting>\n");
	for (i = 0;i < n;i++)
		printf("%d ", list[i]); // sort �� list ���
	printf("\n");
	quick_sort(list, 0, n - 1, n); // quick sort 
	printf("\n<After Quick Sorting>\n");
	for (i = 0;i < n;i++)
		printf("%d ", list[i]); // sort �� list ���
	printf("\n");
	return 0;
}