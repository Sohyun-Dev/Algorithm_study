#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode { // TreeNode ����
	int data;
	struct TreeNode* left, * right;
}TreeNode;

int sum_key(TreeNode* p) { // ����� key���� �հ踦 ���ϴ� �Լ�
	if (p == NULL)
		return 0;
	else { //p�� null�� �ƴ϶��
		return p->data + sum_key(p->left) + sum_key(p->right); // ���
	}
}

int one_child_node(TreeNode* node) { // child�� �� �� ���� ����� ��
	int count = 0;
	if (node != NULL) { // node�� NULL�� �ƴ� ��쿡
		if ((node->left == NULL && node->right != NULL) || (node->right == NULL && node->left != NULL)) // ����� left�� right �� �ϳ��� NULL�̰� �ٸ� �ϳ��� NULL�� �ƴ� ���
			return 1 + one_child_node(node->left) + one_child_node(node->right); // ���
		else
			count = one_child_node(node->left) + one_child_node(node->right); // ���
	}
	return count; // child�� �� �� ���� ����� �� ���� ����
}

int Findmax(TreeNode* node) { // �ִ� key�� ã�� �Լ�
	int root, left, right;
	int max = 0; // �ִ� key�� ���� ����
	if (node != NULL) { // node�� null�� �ƴҰ��
		root = node->data;
		left = Findmax(node->left); // ���
		right = Findmax(node->right); //���
		if (left > right)  // left�� right ���� ���Ͽ� �ִ� ã��
			max = left;
		else max = right;
		if (root > max) // root�� max ���� �ٽ� �� �ִ� ã��
			max = root;
	}
	return max; //�ִ� ��������
}

int Findmin(TreeNode* node) { // �ּ� key �� ���� �Լ�
	int root, left, right;
	int min = 999; // �ּ� key�� ���� ����
	if (node != NULL) { // node�� null �� �ƴ� ���
		root = node->data;
		left = Findmin(node->left); // ���
		right = Findmin(node->right); // ���
		if (left < right) // left�� right ���� ���Ͽ� �ּڰ� ã��
			min = left;
		else min = right;
		if (root < min) // root�� min ���� ���Ͽ� �ּڰ� ã��
			min = root;
	}
	return min; // �ּڰ� ��������
}

//**Test code 1
//TreeNode n0 = { 11, NULL, NULL };
//TreeNode n1 = { 2, &n0, NULL };
//TreeNode n2 = { 5, &n1, NULL };
//TreeNode n3 = { 13, &n2, NULL };
//TreeNode n4 = { 25, &n3, NULL };
//TreeNode n5 = { 8, NULL, NULL };
//TreeNode n6 = { 3, NULL, &n5 };
//TreeNode n7 = { 21, &n4, &n6 };
//TreeNode* exp = &n7;

//**Test code 2
TreeNode n0 = { 10, NULL, NULL };
TreeNode n1 = { 27, &n0, NULL };
TreeNode n2 = { 4, NULL, NULL };
TreeNode n3 = { 15, &n1, &n2 };
TreeNode n4 = { 16, NULL, NULL };
TreeNode n5 = { 25, NULL, NULL };
TreeNode n6 = { 7, &n4, &n5 };
TreeNode n7 = { 55, &n3, &n6 };
TreeNode n8 = { 40, NULL, NULL };
TreeNode n9 = { 36, NULL, &n8 };
TreeNode n10 = { 20, &n7, &n9 };
TreeNode* exp = &n10;

int main(void) {
	printf("Sum of keys in binary tree: %d\n", sum_key(exp)); // key���� �հ� ���
	printf("Num of one child nodes: %d\n", one_child_node(exp)); // child�� �� �� ���� ����� �� ���
	printf("Max value: %d\n", Findmax(exp)); // �ִ� key�� ���
	printf("Min value: %d\n", Findmin(exp)); // �ּ� key�� ���
}