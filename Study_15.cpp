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
		for (;root;root = root->left) // left에 노드가 있으면 일단 stack에 push
			push(root); 
		root = pop(); // left노드가 더이상 없으면 pop
		if (root == NULL) // 모든 노드를 다 순회했으면 종료
			break; 
		printf("[%d]", root->data); // pop한 노드가 root가 되어 출력
		root = root->right; // left, root를 방문했으니 오른쪽 노드로 이동해서 동일 작업 다시 반복
	}
}

int main(void) { // 반복적인 순회
	printf("Inorder:");
	inorder_stack(root);
	printf("\n");
	return 0;
}