#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_SIZE 50
#define SWAP(x,y,t) ((t)=(x), (x)=(y), (y)=(t)) // switch�� ���� ��ũ�η� swap ����

int partition1(int list[], int left, int right) {
	int pivot = list[left];
	printf("* pivot: %d\n", pivot); // pivot �� ���
	int temp, low, high;
	low = left;
	high = right + 1;
	do {
		do
			low++;
		while (list[low] < pivot); // left ���� ��Һ��� �����ϸ鼭 pivot �� �̻��� ��� ã��
		do
			high--;
		while (list[high] > pivot); // right ���� �ٿ����鼭 pivot �� ������ ��� ã��
		if (low < high) SWAP(list[low], list[high], temp); // �� ��� switch
	} while (low < high); // low, high�� ������ ������ �ݺ�
	SWAP(list[left], list[high], temp); // pivot�� �߾ӿ� ��ġ��Ŵ, ���̳� ��ġ�� �̵�
	return high; // pivot ��ġ ��ȯ
}

void quick_sort1(int list[], int left, int right) {
	if (left < right) {
		int p = partition1(list, left, right); //partition1 ȣ���ؼ� pivot ã��
		quick_sort1(list, left, p - 1); // pivot �߽����� pivot �ٷ� �ձ��� ���ȣ��
		quick_sort1(list, p + 1, right); // pivot �߽����� pivot �������� ������ ���ȣ��
	}
}

int median(int left, int right) { // ù��° ��, ������ ��, �߰��� ��ġ�� �� �� median ���� ���ϴ��Լ�
	int median = left + (right - left) / 2;
	return median;
}

int partition2(int list[], int left, int right) { // median of three�� ���� pivot�� �ǵ��� ����
	int mid = median(left, right);
	int pivot = list[mid]; // median of three�� ���� pivot�� �ǵ��� ����
	printf("* pivot: %d\n", pivot); // pivot �� ���
	left = mid; // left���� mid������ ����
	int temp, low, high;
	low = left;
	high = right + 1;
	do {
		do
			low++;
		while (list[low] < pivot); // left ���� ��Һ��� �����ϸ鼭 pivot �� �̻��� ��� ã��
		do
			high--;
		while (list[high] > pivot); // right���� �ٿ����鼭 pivot �� ������ ��� ã��
		if (low < high) SWAP(list[low], list[high], temp); // �� ��� switch
	} while (low < high); // low, high�� ������ ������ �ݺ�
	SWAP(list[left], list[high], temp); // pivot�� �߾ӿ� ��ġ��Ŵ
	return high; // pivot ��ġ ��ȯ
}

void quick_sort2(int list[], int left, int right) {
	if (left < right) {
		int p = partition2(list, left, right); // partition2 ȣ���ؼ� pivot ã��
		quick_sort2(list, left, p - 1); // pivot �߽����� pviot �ٷ� �ձ��� ���ȣ��
		quick_sort2(list, p + 1, right); // pivot �߽����� pivot �������� ������ ���ȣ��
	}
}

int main(void) {
	int i, n;
	printf("Input size of list(1~50):");
	scanf("%d", &n); // ����ڷκ��� 1~50������ ���ڸ� �Է¹���
	int list[MAX_SIZE];
	printf("Input %d numbers in the list\n", n);
	for (i = 0;i < n;i++)
		scanf("%d", &list[i]); // ����ڷκ��� ����Ʈ�� ���� �Է¹���
	printf("\n<<���� ���� ����>>\n");
	for (i = 0;i < n;i++)
		printf("%5d ", list[i]); // sort �� list ���
	printf("\n");
	printf("<Quick Sorting>\n");
	quick_sort1(list, 0, n - 1); // quick sort 1 ����
	printf("\n<Result>\n");
	for (i = 0;i < n;i++)
		printf("%d ", list[i]); // sort �� list ���
	printf("\n");

	printf("\n<Quick Sorting<Median of three>>\n");
	quick_sort2(list, 0, n - 1); // quick sort 2 ����
	printf("\n<Result>\n");
	for (i = 0;i < n;i++)
		printf("%d ", list[i]); // sort �� list ���
	printf("\n");
	return 0;
}