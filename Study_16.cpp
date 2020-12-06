#include <stdio.h>
#include <stdlib.h>
#define MAX_QUEUE_SIZE 100

typedef struct TreeNode {
	int data;
	struct TreeNode* left, * right;
}TreeNode;

typedef TreeNode* element;
typedef struct {
	element data[MAX_QUEUE_SIZE];
	int front, rear;
} QueueType;

void error(const char* message) {
	fprintf(stderr, "%s", message);
	exit(1);
}

bool is_full(QueueType* q) {
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

bool is_empty(QueueType* q) {
	return (q->front == q->rear);
}

void init_queue(QueueType* q) {
	q->front = q->rear = 0;
}

void enqueue(QueueType* q, element item) {
	if (is_full(q))
		error("Queue is full\n");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
}

element dequeue(QueueType* q) {
	if (is_empty(q))
		error("Queue is empty\n");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}

void level_order(TreeNode* ptr) {
	QueueType q;
	init_queue(&q);
	if (ptr == NULL)
		return;
	enqueue(&q, ptr); // root 값을 enqueue
	while (!is_empty(&q)) { // q에 데이터가 있는 동안
		ptr = dequeue(&q); // dequeue하고 나서 하위 두개 child를 enqueue
		printf("[%d]", ptr->data);
		if (ptr->left)
			enqueue(&q, ptr->left);
		if (ptr->right)
			enqueue(&q, ptr->right);
	}
}

TreeNode n1 = { 1, NULL, NULL };
TreeNode n2 = { 4, &n1, NULL };
TreeNode n3 = { 16, NULL, NULL };
TreeNode n4 = { 25, NULL, NULL };
TreeNode n5 = { 20, &n3, &n4 };
TreeNode n6 = { 15, &n2, &n5 };
TreeNode* root = &n6;

int main(void) {
	printf("level 순회:");
	level_order(root);
	printf("\n");
	return 0;
}

