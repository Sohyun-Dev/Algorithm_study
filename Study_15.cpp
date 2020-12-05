#include <stdio.h>
#include <stdlib.h>
#define SIZE 100

typedef struct TreeNode {
	int data;
	struct TreeNode* left, * right;
} TreeNode;

TreeNode* stack[SIZE];
int top = -1;

TreeNode n1 = { 1,NULL,NULL };
TreeNode n2 = { 4, &n1, NULL };
TreeNode n3 = { 16, NULL, NULL };
TreeNode n4 = { 25, NULL, NULL };
TreeNode n5 = { 20, &n3, &n4 };
TreeNode n6 = { 15, &n2, &n5 };
TreeNode* root = &n6;

bool is_full() {
	return (top == SIZE - 1);
}

bool is_empty() {
	return(top == -1);
}

void push(TreeNode* p) {
	if (!is_full()) {
		stack[++top] = p;
	}
}

TreeNode* pop(void) {
	TreeNode* p = NULL;
	if (!is_empty())
		p = stack[top--];
	return p;
}


void inorder_stack(TreeNode* root) {
	while (true) {
		for (;root;root = root->left) // left�� ��尡 ������ �ϴ� stack�� push
			push(root); 
		root = pop(); // left��尡 ���̻� ������ pop
		if (root == NULL) // ��� ��带 �� ��ȸ������ ����
			break; 
		printf("[%d]", root->data); // pop�� ��尡 root�� �Ǿ� ���
		root = root->right; // left, root�� �湮������ ������ ���� �̵��ؼ� ���� �۾� �ٽ� �ݺ�
	}
}

int main(void) { // �ݺ����� ��ȸ
	printf("Inorder:");
	inorder_stack(root);
	printf("\n");
	return 0;
}