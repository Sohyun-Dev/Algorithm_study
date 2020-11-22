#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode { // TreeNode ����
	int data;
	struct TreeNode* left, * right;
} TreeNode;

void inorder(TreeNode* root) {
	if (root) {
		inorder(root->left); // left subtree traverse
		printf("[%d]", root->data); // node visit
		inorder(root->right); // right subtree traverse
	}
}

int get_node_count(TreeNode* exp) { // ����Ʈ�� ��� ���� ����
	if (exp == NULL) return 0;
	else
		return get_node_count(exp->left) + get_node_count(exp->right) + 1; // ������ subtree�� ���Ͽ� ��� ȣ���Ͽ� ��ȯ�� ���� 1�� ���Ͽ� return����
}

int get_leaf_count(TreeNode* exp) { //����Ʈ�� �ܸ� ��� ����
	if (exp == NULL) return 0;
	else {
		if (exp->left == NULL && exp->right == NULL) return 1; // �ܸ��϶�
		else return get_leaf_count(exp->left) + get_leaf_count(exp->right); // �ܸ��� �ƴҶ� 
	}
}

int get_height(TreeNode* exp) { // ����Ʈ�� ���� 
	if (exp == NULL) return 0;
	else { // ���� subtree�� ���̸� ���Ͽ� 
		int l_height = get_height(exp->left);
		int r_height = get_height(exp->right);
		if (l_height >= r_height) return l_height + 1;// �� ū ���� ��ȯ���� 1�� ���Ͽ� ���������� ��������
		else return r_height + 1;
	}
}

int balance(TreeNode* exp) { // balanced tree���� �ƴ��� �˻��ϴ� �Լ�
	int check;
	if (exp == NULL) return 0;
	else {
		int l_height = get_height(exp->left); // ���� subtree�� ���̸� ����
		int r_height = get_height(exp->right); // ������ subtree�� ���̸� ����
		int dif = l_height - r_height; // �� subtree�� ���� ���̸� ������ ����
		if (dif >= -1 && dif <= 1) { // ������ ���̰� 1�̻� -1������ ���
			check = 0; // check������ 0���� ����
		}
		else { // �׷��� ���� ���
			check = 1; // check������ 1�� ����
		}
	}
	if (check == 0) // check������ 0�� ��� balanced tree��
		printf("Yes\n");
	else // check������ 0�� �ƴ� ��� balanced tree�� �ƴ�
		printf("No\n");
}


void pbig(TreeNode* exp, int num) { // ����ڷκ��� �Է¹��� ������ ū key���� ����ϴ� �Լ�
	if (exp) {
		pbig(exp->left, num);
		if (exp->data > num) // ����ڷκ��� �Է¹��� ������ key ���� ū ��� ���
			printf("   %d", exp->data);
		pbig(exp->right, num);
	}
}

//TreeNode n1 = { 1, NULL, NULL };
//TreeNode n2 = { 4, NULL, NULL };
//TreeNode n3 = { 15, &n1, &n2 };
//TreeNode n4 = { 16, NULL, NULL };
//TreeNode n5 = { 25, NULL, NULL };
//TreeNode n6 = { 7, &n4, &n5 };
//TreeNode n7 = { 30, &n3, &n6 };

TreeNode n1 = { 1, NULL, NULL };
TreeNode n2 = { 4, NULL, NULL };
TreeNode n3 = { 15, &n1, &n2 };
TreeNode n7 = { 30, &n3, NULL };
TreeNode* exp = &n7;

int main(void) {
	inorder(exp);// ���� ��ȸ ��� ���
	printf("\n");
	printf("Number of nodes in tree: %d\n", get_node_count(exp));
	printf("Height of the tree : %d\n", get_height(exp));
	printf("Number of leafs in tree : %d\n", get_leaf_count(exp));
	printf("Balanced tree?");
	balance(exp); // balanced�Լ����� �ƴ��� �Ǵ�
	printf("Input a number to check:");
	int n;
	scanf("%d", &n);// ����ڷκ��� ���ڸ� �Է¹���
	printf("numbers greatr than %d:", n);
	pbig(exp, n); // �Է¹��� ���ں��� ū key ���� ���
	printf("\n");
	return 0;
}