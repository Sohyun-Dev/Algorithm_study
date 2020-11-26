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
}QueueType; // Queuetype 정의

void error(const char* message) { // 에러 발생시 문구를 출력하는 함수
	fprintf(stderr, "%s\n", message);
	exit(1);
}

void init_queue(QueueType* q) { //queue를 초기화하는 함수
	q->front = -1;
	q->rear = -1;
}

bool is_full(QueueType* q) { // queue가 꽉 찼는지 확인하는 함수
	return(q->rear == MAX_QUEUE_SIZE - 1);
}

bool is_empty(QueueType* q) { // queue가 비었는지 확인하는 함수
	return(q->front == q->rear);
}

void enqueue(QueueType* q, element item) { // queue에 값을 넣어주는 함수
	if (is_full(q)) { // queue가 꽉 찼을 경우 에러 발생
		error("queue is full");
		return;
	}
	else q->data[++q->rear] = item; // rear를 증가시키고 queue에 값을 넣어줌
}

element dequeue(QueueType* q) { // queue에 값을 꺼내는 함수
	if (is_empty(q)) { // queue가 비었을 경우 에러 발생
		error("queue is empty");
		return -1;
	}
	else return q->data[++(q->front)]; // front를 증가시키고 증가된 front가 가리키는 값을 queue에서 꺼내 리턴해줌
}

void print_queue(QueueType* q) { //queue를 출력하는 함수
	for (int i = 0;i < MAX_QUEUE_SIZE;i++) {
		if (i <= q->front || i > q->rear) printf(""); // queue가 비었으면 빈 상태로 출력
		else printf("%3d |", q->data[i]);
	}
}

void print_bucket(QueueType* q) {// bucket을 출력하는 함수
	for (int i = 0;i < 10;i++) { // 반복문을 이용하여
		printf("[%d]", i);
		print_queue(&q[i]); // queue를 출력하는 함수 호출
		printf("\n");
	}
}

void radix_sort(int list[], int n, int digit) {
	int i, b, d, factor = 1;
	QueueType queues[BUCKETS]; // bucket수만큼의 queue가 추가로 필요
	for (b = 0;b < BUCKETS;b++) init_queue(&queues[b]); // 큐들을 초기화함(index 0~9번까지)
	for (d = 0;d < digit;d++) { // 자리수가 낮은 것부터 높은 순으로
		for (i = 0;i < n;i++) { // 데이터들을 자리수에 따라 큐에 입력
			enqueue(&queues[(list[i] / factor) % 10], list[i]); // 모든 리스트 요소를 해당 queue에 insert함
		}
		print_bucket(queues); // bucket을 출력
		for (b = i = 0;b < BUCKETS;b++) // 반복문을 이용하여 bucket에서 꺼내어 list에 순서대로 insert함
			while (!is_empty(&queues[b])) //while문을 이용하여 반복
				list[i++] = dequeue(&queues[b]); // dequeue한 값을 list에 넣음
		printf("\n");
		factor *= 10; // 그 다음 높은 자리수로 이동
	}
}

int main(void) {
	int list[MAX_SIZE]; // 리스트 생성
	int i, n;
	n = MAX_SIZE;
	int digit;
	int divideNum = 10;
	srand(time(NULL)); // 매번 다른 패턴이 나오게 하기 위해 사용
	printf("자리수입력(1~4):");
	scanf("%d", &digit);// 사용자로부터 digit을 입력받음
	if (digit == 1) // 각 digit에 맞게 난수 생성할 때 나눠줄 수를 설정함
		divideNum = 10;
	else if (digit == 2)
		divideNum = 100;
	else if (digit == 3)
		divideNum = 1000;
	else if (digit == 4)
		divideNum = 10000;
	for (i = 0;i < n;i++) // 반복문을 이용하여 
		list[i] = rand() % divideNum; // 난수생성하여 list에 그 값을 넣음
	printf("\n<Before sorting>\n");
	for (i = 0;i < n;i++)
		printf("%d ", list[i]); // sort 되기 전 list 출력
	printf("\n");
	radix_sort(list, n, digit); // radix-sort(기수 정렬)
	printf("<After Radix Sorting>\n");
	for (i = 0;i < n;i++)
		printf("%d ", list[i]); //sort 후 list 출력
	printf("\n");
	return 0;
}

