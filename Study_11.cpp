#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct dListNode {// ���߿����� ���� ��� ����
	element data;
	struct dListNode* llink; // ���� link
	struct dListNode* rlink; // ������ link
	int size; // ����� ���� 
} dListNode;

void init(dListNode* phead) {// ���߿��Ḯ��Ʈ �ʱ�ȭ �Լ�
	phead->rlink = phead;
	phead->llink = phead;
	phead->size = 0;
}

void dinsert(dListNode* pnode, element val) { // ���ο� �����͸� ���� ��� pnode�� �������� �����ϴ� �Լ�
	dListNode* newnode = (dListNode*)malloc(sizeof(dListNode)); // �����Ҵ����� ���ο� ��� ����
	newnode->data = val; // �Է¹��� ���� data�� ����
	newnode->rlink = pnode->rlink; // ���ο� ����� rlink�� ���� ����� rlink�� ����Ű�� ���� ����
	pnode->rlink->llink = newnode; // ���� ����� rlink����� llink�� ���ο� ��带 ����Ŵ
	newnode->llink = pnode; // ���ο� ����� llink�� ���� ��带 ����Ŵ
	pnode->rlink = newnode; // ���� ����� rlink�� ���ο� ��带 ����Ŵ
	pnode->size = pnode->size + 1; // ����� ���� 1 ���� ��Ŵ
}

void print_dlist1(dListNode* phead) {// ���߿��Ḯ��Ʈ ������ ��� �Լ�
	dListNode* p = phead->llink; // head�� ���� ������ ���
	for (int i = 0;i < phead->size - 1;i++) { // �������� ȭ��ǥ ������� �ʱ� ���ؼ� size-1��ŭ�� ���
		printf("%3d <->", p->data);
		p = p->llink;// p�� �̵�
	}
	printf("%3d\n", phead->rlink->data); // �Ǹ����� ���� ���� ���
}

void print_dlist2(dListNode* phead) { // ���߿��Ḯ��Ʈ ������ ��� �Լ�
	dListNode* p = phead->rlink; // head�� ������ ������ �ϳ��� ���
	for (int i = 0;i < phead->size - 1;i++) { // �������� ȭ��ǥ ������� �ʱ� ���ؼ� size-1��ŭ�� ���
		printf("%3d <->", p->data);
		p = p->rlink; // p�� �̵�
	}
	printf("%3d\n", phead->llink->data); // �Ǹ����� ���� ���� ���
}

int main(void) {
	dListNode* head = (dListNode*)malloc(sizeof(dListNode)); // head��� ����
	init(head); // head��� �ʱ�ȭ
	printf("Input data in dual linkedlist<0 to quit>\n");
	while (true) {
		int input = 0;
		scanf("%d", &input); // ����ڷκ��� ���� �Է¹���
		if (input == 0) // ����ڷκ��� �Է¹��� ���� 0�̸� �ݺ��� ����
			break;
		dinsert(head, input); // �Է¹��� ���� ��忡 ����
	}
	print_dlist1(head); // ������ ���
	printf("Print the list in reverse order\n");
	print_dlist2(head); // ������ ���
}
