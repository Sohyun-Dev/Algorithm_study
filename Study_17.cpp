#include <stdio.h>
#include <stdlib.h>
#define MAX_ELEMENT 200
typedef struct {
	int key;
}element;

typedef struct { //HeapType ����
	element heap[MAX_ELEMENT];
	int heap_size;
} HeapType;


//**���� �޸� �Ҵ�/���� �޸� �Ҵ� �� �� 1

// HeapType heap; //���� �޸� �Ҵ� ���

HeapType* create() { // ���� �޸� �Ҵ�
	return (HeapType*)malloc(sizeof(HeapType));
}

void init(HeapType* h) {
	h->heap_size = 0;
}
 
void insert_max_heap(HeapType* h, element item) { // item ��带 �߰��ϴ� ����
	int i;
	i = ++(h->heap_size); // ��� �߰� �� ������ ���� ��� �ε����� i�� ����
	while ((i != 1) && (item.key > h->heap[i / 2].key)) { // Ʈ���� �Ž��� �ö󰡸鼭 �θ� ��� key���� ��
		h->heap[i] = h->heap[i / 2]; // �߰��� ��� key������ ���� ��� �θ� ��带 ����
		i /= 2; // �ε��� ���ο� ��ġ(�θ�)�� �̵�
	}
	h->heap[i] = item; // ���� ������ ��ġ�� ���ο� ��带 insert
}

element delete_max_heap(HeapType* h) { 
	int parent = 1; 
	int child = 2; // �ι�° ������ root ���� �� ����
	element item = h->heap[1]; // �����Ǵ� ���(���� �� ��ȯ)
	element temp = h->heap[h->heap_size--]; // ���ܳ�带 temp�� �븳(��� ���� �� heap_size�� ����)
	while (child <= h->heap_size) { // �ִ� ���ܱ��� Ʈ���� �������鼭 �ڽĳ�� key���� temp key ��
		if ((child < h->heap_size) && (h->heap[child].key < h->heap[child + 1].key)) // sibling�� ���� �� �� �� ū �� ã��
			child++; // sibling�� �񱳴�� ��尡 ��(subtree ����)
		if (temp.key >= h->heap[child].key) // �ڽ� ��庸�� �űԳ��key�� ũ�� ��ġ Ȯ���Ǿ� �ݺ� ����
			break; 
		h->heap[parent] = h->heap[child]; // �ڽĳ�� key�� �� ũ�� parent ��忡 child ��� ����
		parent = child; // parent �ε����� child �ε����� ����
		child *= 2; // child �ε����� �� �Ʒ� child�� ����
	}
	h->heap[parent] = temp; // Ȯ����ġ(parent)�� �űԳ�� insert
	return item; 
}

int main(void)
{
	element e1 = { 10 }, e2 = { 5 }, e3 = { 30 }, e4, e5, e6;
	HeapType* heap = create(); // ���� �޸� �Ҵ� ���
	init(heap);
	insert_max_heap(heap, e1);
	insert_max_heap(heap, e2);
	insert_max_heap(heap, e3);

	// ������� delete�ϰ� ���
	e4 = delete_max_heap(heap);
	printf("< %d > ", e4.key);
	e5 = delete_max_heap(heap);
	printf("< %d > ", e5.key);
	e6 = delete_max_heap(heap);
	printf("< %d >\n", e6.key);

	free(heap);
	return 0;
}