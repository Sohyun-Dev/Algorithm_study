#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define BUCKETS 10
#define MAX_QUEUE_SIZE 10
#define MAX_SIZE 10

typedef int element;
typedef struct {
	int front;
	int rear;
	element data[MAX_QUEUE_SIZE];
}QueueType; // Queuetype ����

void error(const char* message) { // ���� �߻��� ������ ����ϴ� �Լ�
	fprintf(stderr, "%s\n", message);
	exit(1);
}

void init_queue(QueueType* q) { //queue�� �ʱ�ȭ�ϴ� �Լ�
	q->front = -1;
	q->rear = -1;
}

bool is_full(QueueType* q) { // queue�� �� á���� Ȯ���ϴ� �Լ�
	return(q->rear == MAX_QUEUE_SIZE - 1);
}

bool is_empty(QueueType* q) { // queue�� ������� Ȯ���ϴ� �Լ�
	return(q->front == q->rear);
}

void enqueue(QueueType* q, element item) { // queue�� ���� �־��ִ� �Լ�
	if (is_full(q)) { // queue�� �� á�� ��� ���� �߻�
		error("queue is full");
		return;
	}
	else q->data[++q->rear] = item; // rear�� ������Ű�� queue�� ���� �־���
}

element dequeue(QueueType* q) { // queue�� ���� ������ �Լ�
	if (is_empty(q)) { // queue�� ����� ��� ���� �߻�
		error("queue is empty");
		return -1;
	}
	else return q->data[++(q->front)]; // front�� ������Ű�� ������ front�� ����Ű�� ���� queue���� ���� ��������
}

void print_queue(QueueType* q) { //queue�� ����ϴ� �Լ�
	for (int i = 0;i < MAX_QUEUE_SIZE;i++) {
		if (i <= q->front || i > q->rear) printf(""); // queue�� ������� �� ���·� ���
		else printf("%3d |", q->data[i]);
	}
}

void print_bucket(QueueType* q) {// bucket�� ����ϴ� �Լ�
	for (int i = 0;i < 10;i++) { // �ݺ����� �̿��Ͽ�
		printf("[%d]", i);
		print_queue(&q[i]); // queue�� ����ϴ� �Լ� ȣ��
		printf("\n");
	}
}

void radix_sort(int list[], int n, int digit) {
	int i, b, d, factor = 1;
	QueueType queues[BUCKETS]; // bucket����ŭ�� queue�� �߰��� �ʿ�
	for (b = 0;b < BUCKETS;b++) init_queue(&queues[b]); // ť���� �ʱ�ȭ��(index 0~9������)
	for (d = 0;d < digit;d++) { // �ڸ����� ���� �ͺ��� ���� ������
		for (i = 0;i < n;i++) { // �����͵��� �ڸ����� ���� ť�� �Է�
			enqueue(&queues[(list[i] / factor) % 10], list[i]); // ��� ����Ʈ ��Ҹ� �ش� queue�� insert��
		}
		print_bucket(queues); // bucket�� ���
		for (b = i = 0;b < BUCKETS;b++) // �ݺ����� �̿��Ͽ� bucket���� ������ list�� ������� insert��
			while (!is_empty(&queues[b])) //while���� �̿��Ͽ� �ݺ�
				list[i++] = dequeue(&queues[b]); // dequeue�� ���� list�� ����
		printf("\n");
		factor *= 10; // �� ���� ���� �ڸ����� �̵�
	}
}

int main(void) {
	int list[MAX_SIZE]; // ����Ʈ ����
	int i, n;
	n = MAX_SIZE;
	int digit;
	int divideNum = 10;
	srand(time(NULL)); // �Ź� �ٸ� ������ ������ �ϱ� ���� ���
	printf("�ڸ����Է�(1~4):");
	scanf("%d", &digit);// ����ڷκ��� digit�� �Է¹���
	if (digit == 1) // �� digit�� �°� ���� ������ �� ������ ���� ������
		divideNum = 10;
	else if (digit == 2)
		divideNum = 100;
	else if (digit == 3)
		divideNum = 1000;
	else if (digit == 4)
		divideNum = 10000;
	for (i = 0;i < n;i++) // �ݺ����� �̿��Ͽ� 
		list[i] = rand() % divideNum; // ���������Ͽ� list�� �� ���� ����
	printf("\n<Before sorting>\n");
	for (i = 0;i < n;i++)
		printf("%d ", list[i]); // sort �Ǳ� �� list ���
	printf("\n");
	radix_sort(list, n, digit); // radix-sort(��� ����)
	printf("<After Radix Sorting>\n");
	for (i = 0;i < n;i++)
		printf("%d ", list[i]); //sort �� list ���
	printf("\n");
	return 0;
}

