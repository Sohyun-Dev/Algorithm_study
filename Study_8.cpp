#include <stdio.h>
#include <stdlib.h>
#define MAX_QUEUE_SIZE 1000

typedef int element;
typedef struct QueueNode { // 연결리스트로 구현하기 위한 QueueNode 정의
	element data;
	struct QueueNode* link;
} QueueNode;

typedef struct {
	QueueNode* front, * rear; //front 노드와 rear 노드 저장
	int count; // 노드 개수를 담을 변수
} LinkedQueueType;

void error(const char* message) {  // 오류 발생시 에러 메세지 출력
	fprintf(stderr, "%s\n", message);
	exit(1);
}

void init_queue(LinkedQueueType* q) { // queue 초기화 함수 
	q->front = NULL;
	q->rear = NULL;
	q->count = 0;
}

bool is_full(LinkedQueueType* q) { // queue가 full인지 아닌지 확인하는 함수
	return 0;
}

bool is_empty(LinkedQueueType* q) { // queue가 empty인지 아닌지 확인하는 함수
	return(q->front == NULL); // front가 NULL 이면 empty
}

void enqueue(LinkedQueueType* q, element item) { // enqueue함수 정의 
	QueueNode* temp = (QueueNode*)malloc(sizeof(QueueNode)); //동적할당을 통한 새로운 노드 생성 
	temp->data = item; // 새로운 노드의 data에 입력받은 값 저장
	temp->link = NULL; // 링크는 NULL
	if (is_empty(q)) { // q가 empty인 경우 새로 추가된 node가 front이자 rear가 됨
		q->front = temp;
		q->rear = temp;
	}
	else { // q가 empty이지 않은 경우
		q->rear->link = temp; // 기존의 rear가 새로 추가된 노드를 가리킴
		q->rear = temp; // 새로 추가된 node가 rear가 됨
	}
	q->count++; // 노드의 갯수에 1을 더함
}

element dequeue(LinkedQueueType* q) { // dequeue함수 정의
	if (is_empty(q)) // 비어있을 경우 에러 메세지 출력
		error("queue empty");
	element data;
	QueueNode* temp = q->front; // 기존의 front가 가리키던 노드 위치를 저장해둠
	data = temp->data; // 리턴해주기 위하여 기존의 front 가리키던 값을 저장해둠
	q->front = q->front->link; // 기존의 front가 가리키던 노드가 새로운 front가 됨
	if (q->front == NULL) // 노드가 한개 있는 경우에는
		q->rear = NULL; // queue를 공백으로 만들어줌
	free(temp); // free해줌
	q->count--; // 노드의 갯수에 1을 뺌
	return data; // 저장해두었던 기존의 front를 가리키던 값 리턴
}

void print_queue(LinkedQueueType* q) { // Queue를 출력해주는 함수
	for (QueueNode* p = q->front; p != NULL; p = p->link) {
		printf("%4d |", p->data);
	}
	printf("\n");
}

int Ncount(LinkedQueueType* q) { // 노드의 개수를 반환하는 함수
	int result = q->count;
	return result;
}

int main(void) {
	int card = 0;
	LinkedQueueType q; // Queue 생성
	init_queue(&q); // q 초기화
	printf("Input number of cards: ");
	scanf("%d", &card); // 사용자로부터 숫자 입력받음
	for (int i = 1;i <= card;i++) { // 1부터 입력받은 숫자까지 queue에 넣음
		enqueue(&q, i);
	}
	print_queue(&q); // queue를 출력해주고
	dequeue(&q); // dequeue 한 번 실행 
	print_queue(&q); // queue를 출력해줌
	while (Ncount(&q) != 1) { // 노드의 개수가 1이 되기 전까지 반복
		enqueue(&q, dequeue(&q));//dequeue한 값을 enqueue해줌
		print_queue(&q); // queue 출력
		dequeue(&q); // dequeue해줌
		print_queue(&q); // queue를 출력
	}
	if (Ncount(&q) == 1) // 노드의 개수가 1일 경우에 마지막 남은 값 dequeue해주면서 출력해줌
		printf("Final element is %d\n", dequeue(&q));
}