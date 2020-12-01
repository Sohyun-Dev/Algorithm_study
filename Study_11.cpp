#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct dListNode {// 이중연결을 위한 노드 구조
	element data;
	struct dListNode* llink; // 왼쪽 link
	struct dListNode* rlink; // 오른쪽 link
	int size; // 노드의 갯수 
} dListNode;

void init(dListNode* phead) {// 이중연결리스트 초기화 함수
	phead->rlink = phead;
	phead->llink = phead;
	phead->size = 0;
}

void dinsert(dListNode* pnode, element val) { // 새로운 데이터를 기존 노드 pnode의 오른족에 삽입하는 함수
	dListNode* newnode = (dListNode*)malloc(sizeof(dListNode)); // 동적할당으로 새로운 노드 생성
	newnode->data = val; // 입력받은 값을 data에 대입
	newnode->rlink = pnode->rlink; // 새로운 노드의 rlink는 기존 노드의 rlink가 가리키는 값을 가짐
	pnode->rlink->llink = newnode; // 기존 노드의 rlink노드의 llink가 새로운 노드를 가리킴
	newnode->llink = pnode; // 새로운 노드의 llink는 기존 노드를 가리킴
	pnode->rlink = newnode; // 기존 노드의 rlink는 새로운 노드를 가리킴
	pnode->size = pnode->size + 1; // 노드의 갯수 1 증가 시킴
}

void print_dlist1(dListNode* phead) {// 이중연결리스트 순방향 출력 함수
	dListNode* p = phead->llink; // head의 왼쪽 노드부터 출력
	for (int i = 0;i < phead->size - 1;i++) { // 마지막에 화살표 출력하지 않기 위해서 size-1만큼만 출력
		printf("%3d <->", p->data);
		p = p->llink;// p를 이동
	}
	printf("%3d\n", phead->rlink->data); // 맨마지막 값은 따로 출력
}

void print_dlist2(dListNode* phead) { // 이중연결리스트 역방향 출력 함수
	dListNode* p = phead->rlink; // head의 오른족 노드부터 하나씩 출력
	for (int i = 0;i < phead->size - 1;i++) { // 마지막에 화살표 출력하지 않기 위해서 size-1만큼만 출력
		printf("%3d <->", p->data);
		p = p->rlink; // p를 이동
	}
	printf("%3d\n", phead->llink->data); // 맨마지막 값은 따로 출력
}

int main(void) {
	dListNode* head = (dListNode*)malloc(sizeof(dListNode)); // head노드 생성
	init(head); // head노드 초기화
	printf("Input data in dual linkedlist<0 to quit>\n");
	while (true) {
		int input = 0;
		scanf("%d", &input); // 사용자로부터 숫자 입력받음
		if (input == 0) // 사용자로부터 입력받은 값이 0이면 반복문 종료
			break;
		dinsert(head, input); // 입력받은 수를 노드에 삽입
	}
	print_dlist1(head); // 순방향 출력
	printf("Print the list in reverse order\n");
	print_dlist2(head); // 역방향 출력
}
