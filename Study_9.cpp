#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100

typedef struct Stack {
	char data[MAX]; // char�� ������ ���
	int top; // top ���� ����� ���Խ�Ŵ
}Stack;

void init_stack(Stack* s) { // stack �ʱ�ȭ �Լ��ε� ����ü �����͸� ���ڷ� ����
	s->top = -1; // top�� -1�� �ʱ�ȭ
}

void error(const char X[]) { // ���� �߻��� ���� �޼��� ���
	fprintf(stderr, X);
}

bool is_full(Stack* s) { // stack�� full���� �ƴ��� Ȯ���ϴ� �Լ�
	return(s->top == (MAX - 1)); // top�� �ִ�� true ��ȯ
}

bool is_empty(Stack* s) { // stack�� empty���� �ƴ��� Ȯ���ϴ� �Լ�
	return(s->top == -1); // top�� -1�̸�(���� empty) true ��ȯ
}

char pop(Stack* s) { // pop���ִ� �Լ�
	if (is_empty(s)) { // stack�� ����ִ� ���
		error("Stack empty");
		exit(1);
	}
	else return s->data[(s->top)--]; //stack�� ������� ���� ���� top�� ����Ű�� ���Ұ� ��ȯ �� top �� ��ġ�� 1 ���� ����
}

void push(Stack* s, char item) {// push ���ִ� �Լ�
	if (is_full(s)) { // stack�� full�� ���
		error("Overflow");
		return;
	}
	else s->data[++(s->top)] = item; // stack�� �� ������ ���� ��� top�� 1 ������Ų ������ �ش� ��ġ�� ���Ұ� ������
}

void d_array(char str[]) {// �迭�� �̿��Ͽ� �Էµ� ���ڿ��� ��Ī�� �̷���� üũ�ϴ� �Լ�
	int length = strlen(str); // ���ڿ��� ���̸� ����
	int pnum2 = 0; // ��Ī���� �ƴ��� �����ϱ� ���� ���� ���
	for (int i = 0;i < length / 2;i++) {// �¿��Ī���ڰ� �´��� �ϳ��� Ȯ��
		if (str[i] != str[length - 1 - i]) { // ���� ���ϴµ� �ٸ� ��쿡
			pnum2 = 1; // pnum�� 1�� �ٲ���
			break;			// �ƴѰ�찡 �����, �ٷ� ���α׷� ����
		}
		else
			continue; // �¿��Ī���ڰ� ������, ��� �ݺ�Ȯ��
	}
	if (pnum2 == 1) // pnum�� 1�� ��쿡�� ���Ī
		printf("���Ī<�迭>\n");
	else if (pnum2 == 0) // pnum�� 0�� ���� ��Ī
		printf("��Ī<�迭>\n");
}

void d_stack(char str[]) { // ������ �̿��Ͽ� �Էµ� ���ڿ��� ��Ī���� �ƴ��� üũ�ϴ� �Լ�
	Stack s; // ���� ����
	int i = 0;
	int length = strlen(str); // length�� ���ڿ��� ���̸� ����
	init_stack(&s); // ���� �ʱ�ȭ
	for (i = 0;i < length;i++) { // ���ڿ��� ���̸�ŭ ��ü�� stack�� push����
		push(&s, str[i]);
	}
	int pnum1 = 0; // ��Ī���� �ƴ��� �����ϱ� ���� ���� ���
	for (i = 0;i < length / 2;i++) { // �¿� ��Ī �������� �ϳ��� Ȯ���ϴµ� �ݸ� �ݺ��ϸ� ��
		if (str[i] != pop(&s)) { // ���ÿ��� pop�� ���� str[i]��°�� ���� ���� �ʴٸ�
			pnum1 = 1; // ���Ī�̹Ƿ� pnum�� 1�� �ٲ��ְ� �ݺ��� ����
			break;
		}
	}
	if (pnum1 == 1) // pnum1�� 1�� ��쿡�� ���Ī
		printf("���Ī<����>\n");
	else if (pnum1 == 0) // pnum1�� 0�� ��쿡�� ��Ī
		printf("��Ī<����>\n");
}

int main(void) {
	char str[MAX];
	while (true) { //while���� �̿��Ͽ� �ݺ�
		printf("���ĺ����� ������ ���ڿ� �Է�\n");
		scanf("%s", str); // ����ڷκ��� ���ڿ� �Է¹���
		if (strcmp(str, "0") == 0) // ���ڿ��� 0�Է� ���� ��� �ݺ��� ����
			break;
		d_array(str); // �迭 �̿��Ͽ� ��Ī Ȯ���ϴ� �Լ� ȣ��
		d_stack(str); // ���� �̿��Ͽ� ��Ī Ȯ���ϴ� �Լ� ȣ��
		printf("\n");
	}
	return 0;
}