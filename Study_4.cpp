#include <stdio.h>
#include <stdlib.h>
#define MAX_ELEMENT 200
typedef struct {
	int key;
} element;

typedef struct { // HeapType ����
	element heap[MAX_ELEMENT];
	int heap_size;
} HeapType;

HeapType* create() { // ���� �޸� �Ҵ��� �̿�
	return (HeapType*)malloc(sizeof(HeapType));
}

void init(HeapType* h) { // �ʱ�ȭ �Լ�
	h->heap_size = 0;
}

void insert_max_heap(HeapType* h, element item) { // item ��带 �߰��ϴ� �Լ�(max heap)
	int i;
	i = ++(h->heap_size); // ��� �߰� �� ������ ���� ��� �ε����� i�� ����
	while ((i != 1) && (item.key > h->heap[i / 2].key)) { // Ʈ���� �Ž��� �ö󰡸鼭 �θ� ��� key ���� ��
		h->heap[i] = h->heap[i / 2]; // �߰��� ��� key������ ���� ��� �θ��带 ����
		i /= 2; // �ε��� ���ο� ��ġ(�θ�)�� �̵�
	}
	h->heap[i] = item; // ���� ������ ��ġ�� ���ο� ��带 insert��
}

element delete_max_heap(HeapType* h) { // delete�ϴ� �Լ�(max heap)
	int parent = 1, child = 2; // �ι�° ������ root���� �񱳽���
	element item = h->heap[1]; // �����Ǵ� ���(���� �� ��ȯ�ϱ� ����)
	element temp = h->heap[h->heap_size--]; // ���ܳ�� temp�� ����(��� ���� �� heap_size ����)
	while (child <= h->heap_size) { // �ִ� ���ܱ��� Ʈ���� �������鼭 �ڽĳ�� key���� temp key ��
		if ((child < h->heap_size) && (h->heap[child].key < h->heap[child + 1].key)) // sibling�� ���� �� �� �� ū �� ã��
			child++; // sibling�� �񱳴�� ��尡 ��(subtree ����)
		if (temp.key >= h->heap[child].key) break; // �ڽĳ�庸�� �űԳ�� key�� ũ�� ��ġ Ȯ���Ǿ� �ݺ� ����
		h->heap[parent] = h->heap[child]; //�ڽĳ�� key�� �� ũ�� parent��忡 child ��� ����
		parent = child; // parent �ε����� child �ε����� ����
		child *= 2; // child �ε����� �� �Ʒ� child�� ����
	}
	h->heap[parent] = temp; // Ȯ����ġ(parent)�� �űԳ�� insert
	return item;
}

void insert_min_heap(HeapType* h, element item) { // ��带 �߰��ϴ� �Լ�(min heap)
	int i;
	i = ++(h->heap_size); // ��� ���� �� ������ ���� ��� �ε����� i�� ��
	while ((i != 1) && (item.key < h->heap[i / 2].key)) { //Ʈ���� �Ž��� �ö󰡸鼭 �θ� ��� key ���� ��
		h->heap[i] = h->heap[i / 2]; // �߰��� ��� key������ ū ��� �θ��带 ����
		i /= 2; //�ε��� ���ο� ��ġ(�θ�)�� �̵�
	}
	h->heap[i] = item; // ���� ������ ��ġ�� ���ο� ��带 ����
}

element delete_min_heap(HeapType* h) { // delete �ϴ� �Լ�(min heap)
	int parent = 1, child = 2; // �ι�° ������ root���� �񱳽���
	element item = h->heap[1]; // �����Ǵ� ���(���� �� ��ȯ�ϱ� ����)
	element temp = h->heap[(h->heap_size)--]; // ���ܳ�� temp�� ����(��� ���� �� heap_size ����)
	while (child <= h->heap_size) { // �ִ� ���ܱ��� Ʈ���� �������鼭 �ڽĳ�� key���� temp key ��
		if ((child < h->heap_size) && (h->heap[child].key > h->heap[child + 1].key))
			child++; // sibling�� �ִ� ��� �� �� ���� �� ã��
		if (temp.key < h->heap[child].key) break; // �ڽĳ�庸�� �űԳ�� key�� ������ ��ġ Ȯ���Ǿ� �ݺ� ����
		h->heap[parent] = h->heap[child]; // �ڽĳ�� key�� �� ������ parent ��忡 child ��� ����
		parent = child; // parent �ε����� child �ε����� ����
		child *= 2; // child �ε����� �� �Ʒ� child�� ����
	}
	h->heap[parent] = temp; // Ȯ����ġ(parent)�� �űԳ�� ����
	return item;
}

void print_heap(HeapType* h) { // heap ��ü�� ����ϴ� �Լ� 
	int i;
	for (i = 1;i <= h->heap_size;i++) // �ݺ����� ���鼭 ��ü ���
		printf("%d ", h->heap[i]);
	printf("\n");
}

int main(void) {
	HeapType* heap1 = create(); //heap1, heap2 ����
	HeapType* heap2 = create();
	init(heap1); // heap1, heap2 �ʱ�ȭ
	init(heap2);
	while (true) { // while���� �̿��Ͽ� �ݺ�
		char A;
		printf("*Input Operation I(Insert)  D(Delete)  X(Exit):");
		scanf("%s", &A); // ����ڷκ��� ���ڿ��� �Է¹���
		getchar();
		switch (A) {
		case 'I': // I�� �Է¹��� ���
			printf("Input value to insert:");
			element insert;
			scanf("%d", &insert); // ����ڷκ��� ������ value�� �Է¹���
			insert_max_heap(heap1, insert); // maxheap, min heap�� �°� insert
			insert_min_heap(heap2, insert);
			printf("<MAX Heap>\n"); // max_heap, min_heap �°� ������ heap ���
			print_heap(heap1);
			printf("<Min Heap>\n");
			print_heap(heap2);
			break;

		case 'D': // ����ڷκ��� D�� �Է¹޾��� ���
			delete_max_heap(heap1); // maxheap, min heap�� �°� delete
			delete_min_heap(heap2);
			printf("<MAX Heap>\n");// maxheap, min heap�� �°� delete�� heap ���
			print_heap(heap1);
			printf("<Min Heap>\n");
			print_heap(heap2);
			break;

		case 'X': // ����ڷκ��� X�� �Է¹޾��� ���
			exit(1); // ���α׷� ����
			break;

		default: // �׿ܿ� �͵��� �Է¹޾��� ��� �߸��� �Է��̶�� ���
			printf("Wrong Input\n");
		}
	}
}
