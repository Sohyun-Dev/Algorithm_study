#include <stdio.h>
#include <stdlib.h>
#define MAX_QUEUE_SIZE 1000

typedef int element;
typedef struct QueueNode { // ���Ḯ��Ʈ�� �����ϱ� ���� QueueNode ����
	element data;
	struct QueueNode* link;
} QueueNode;

typedef struct {
	QueueNode* front, * rear; //front ���� rear ��� ����
	int count; // ��� ������ ���� ����
} LinkedQueueType;

void error(const char* message) {  // ���� �߻��� ���� �޼��� ���
	fprintf(stderr, "%s\n", message);
	exit(1);
}

void init_queue(LinkedQueueType* q) { // queue �ʱ�ȭ �Լ� 
	q->front = NULL;
	q->rear = NULL;
	q->count = 0;
}

bool is_full(LinkedQueueType* q) { // queue�� full���� �ƴ��� Ȯ���ϴ� �Լ�
	return 0;
}

bool is_empty(LinkedQueueType* q) { // queue�� empty���� �ƴ��� Ȯ���ϴ� �Լ�
	return(q->front == NULL); // front�� NULL �̸� empty
}

void enqueue(LinkedQueueType* q, element item) { // enqueue�Լ� ���� 
	QueueNode* temp = (QueueNode*)malloc(sizeof(QueueNode)); //�����Ҵ��� ���� ���ο� ��� ���� 
	temp->data = item; // ���ο� ����� data�� �Է¹��� �� ����
	temp->link = NULL; // ��ũ�� NULL
	if (is_empty(q)) { // q�� empty�� ��� ���� �߰��� node�� front���� rear�� ��
		q->front = temp;
		q->rear = temp;
	}
	else { // q�� empty���� ���� ���
		q->rear->link = temp; // ������ rear�� ���� �߰��� ��带 ����Ŵ
		q->rear = temp; // ���� �߰��� node�� rear�� ��
	}
	q->count++; // ����� ������ 1�� ����
}

element dequeue(LinkedQueueType* q) { // dequeue�Լ� ����
	if (is_empty(q)) // ������� ��� ���� �޼��� ���
		error("queue empty");
	element data;
	QueueNode* temp = q->front; // ������ front�� ����Ű�� ��� ��ġ�� �����ص�
	data = temp->data; // �������ֱ� ���Ͽ� ������ front ����Ű�� ���� �����ص�
	q->front = q->front->link; // ������ front�� ����Ű�� ��尡 ���ο� front�� ��
	if (q->front == NULL) // ��尡 �Ѱ� �ִ� ��쿡��
		q->rear = NULL; // queue�� �������� �������
	free(temp); // free����
	q->count--; // ����� ������ 1�� ��
	return data; // �����صξ��� ������ front�� ����Ű�� �� ����
}

void print_queue(LinkedQueueType* q) { // Queue�� ������ִ� �Լ�
	for (QueueNode* p = q->front; p != NULL; p = p->link) {
		printf("%4d |", p->data);
	}
	printf("\n");
}

int Ncount(LinkedQueueType* q) { // ����� ������ ��ȯ�ϴ� �Լ�
	int result = q->count;
	return result;
}

int main(void) {
	int card = 0;
	LinkedQueueType q; // Queue ����
	init_queue(&q); // q �ʱ�ȭ
	printf("Input number of cards: ");
	scanf("%d", &card); // ����ڷκ��� ���� �Է¹���
	for (int i = 1;i <= card;i++) { // 1���� �Է¹��� ���ڱ��� queue�� ����
		enqueue(&q, i);
	}
	print_queue(&q); // queue�� ������ְ�
	dequeue(&q); // dequeue �� �� ���� 
	print_queue(&q); // queue�� �������
	while (Ncount(&q) != 1) { // ����� ������ 1�� �Ǳ� ������ �ݺ�
		enqueue(&q, dequeue(&q));//dequeue�� ���� enqueue����
		print_queue(&q); // queue ���
		dequeue(&q); // dequeue����
		print_queue(&q); // queue�� ���
	}
	if (Ncount(&q) == 1) // ����� ������ 1�� ��쿡 ������ ���� �� dequeue���ָ鼭 �������
		printf("Final element is %d\n", dequeue(&q));
}