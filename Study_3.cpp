#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode { // TreeNode ����
	int key;
	struct TreeNode* left, * right;
} TreeNode;


TreeNode* new_node(int item) {
	TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode)); // ���� �޸� �Ҵ�
	node->key = item; // ��(item)�� key�� ����
	node->left = node->right = NULL; // child ��带 NULL�� �ʱ�ȭ
	return node; // ���� ������ ��� ��ȯ
}

TreeNode* insert_node(TreeNode* node, int key) { // �ش� ��ġ ã�Ƽ� key �� ���� ��� insert 
	if (node == NULL) return new_node(key); // Ʈ���� ������ ��� insert �� ���ο� ��带 ��ȯ
	if (key < node->key) // insert �� ���� root�� Ű������ ������ left subtree�� root�� insert ��� ȣ��
		node->left = insert_node(node->left, key);
	else if (key > node->key) // insert �� ���� root�� Ű������ ũ�� right subtree�� root�� insert ��� ȣ��
		node->right = insert_node(node->right, key);
	return node; // ����� root ������ ��ȯ
}

void inorder(TreeNode* root) { // ������ �°� ����ϴ� �Լ�
	if (root == NULL) return; // empty tree �̸� NULL ��ȯ
	else {
		inorder(root->left); // left subtree traverse
		printf(" [%d]", root->key);
		inorder(root->right); // right subtree traverse
	}
}

TreeNode* min_value_node(TreeNode* node) { // ���� ������ �ܸ� ��� ã��(�ּҰ�)
	TreeNode* current = node;
	while (current->left != NULL) // NULL�� �� �� ���� ��� ���� child�� ã�� ������
		current = current->left;
	return current;
}

TreeNode* max_value_node(TreeNode* node) { // ���� �������� �ܸ� ��� ã��(�ִ밪)
	TreeNode* current = node;
	while (current->right != NULL) // NULL�� �� �� ���� ��� ������ child�� ã�� ������
		current = current->right;
	return current;
}

TreeNode* delete_node(TreeNode* root, int key) { // key�� ����� ��带 ã�� �����ϰ� ���ο� root ��ȯ
	if (root == NULL) return root; // root�� NULL�� ���� �׳� root return
	else if (root->key > key) // ���� subtree���� key���� ã�� �����ϵ��� ���ȣ��
		root->left = delete_node(root->left, key); // ���ο� left child�� ����
	else if (root->key < key) // ������ subtree���� key���� ã�� �����ϵ��� ���ȣ��
		root->right = delete_node(root->right, key); // ���ο� right child�� ����
	else { // delete�ϰ��� �ϴ� key�� ã���� ��
		if (root->left == NULL) { // leaf��� �̰ų� child�� �ϳ� ���� ��쿡 (left�� NULL�� ���) 
			TreeNode* temp = root->right;
			free(root);
			return temp;
		}
		else if (root->right == NULL) { // right�� NULL�� ���
			TreeNode* temp = root->left;
			free(root);
			return temp;
		}
		//child�� �� �� �ִ� ��� 
		TreeNode* temp1 = max_value_node(root->left); // ������  subtree�� ���� ���� ���� ���� ��� ã��(�ּڰ�)
		TreeNode* temp2 = min_value_node(root->right); // ���� subtree�� ���� ������ ���� ���� ��� ã��(�ִ밪)
		printf("left subtree�� max : %d\n", temp1->key); // ���� subtree�� max�� ������ subtree�� min ���
		printf("right subtree�� min :%d\n", temp2->key);

		int diff1 = key - temp1->key; // key ���� ���� subtree�� �ִ밪�� ���̸� ����
		int diff2 = temp2->key - key; // key ���� ������ subtree�� �ּڰ��� ���̸� ����
		if (diff1 >= diff2) { // ������ subtree�� �ּڰ��� key ���� ���̰� �� ���� �� 
			root->key = temp2->key; // ����� key���� ������ ��ġ�� ����
			root->right = delete_node(root->right, temp2->key); // ����� ���� ���� �ִ� ��� ����
			printf("original value : %d   new value : %d\n", key, root->key);
		}
		else { // ���� subtree�� �ּڰ��� key���� ���̰� �� ���� ��
			root->key = temp1->key; // ����� key���� ������ ��ġ�� ����
			root->left = delete_node(root->left, temp1->key); // ����� ���� ���� �ִ� ��� ����
			printf("original value : %d   new value : %d\n", key, root->key);
		}
	}
	return root;
}

int main(void) {
	TreeNode* root = NULL;
	root = insert_node(root, 30);
	root = insert_node(root, 20);
	root = insert_node(root, 10);
	root = insert_node(root, 45);
	root = insert_node(root, 50);
	root = insert_node(root, 60);

	printf("���� Ž�� Ʈ�� ���� ��ȸ ��� \n");
	inorder(root); // inorder traverse
	printf("\n\n");

	while (true) { // while���� �̿��Ͽ� �ݺ�
		char A;
		printf("* operation ���� : Insert(I) / Delete(D) / Exit(X) :");
		scanf("%s", &A); // ����ڷκ��� ���ڿ��� �Է¹���
		getchar();
		int num;
		if (A == 'I') { // Insert�ϴ� ���
			printf("Insert�� ����? ");
			scanf("%d", &num);
			insert_node(root, num); // ����ڷκ��� �Է¹��� ���� insert����
			inorder(root); // ���� ��ȸ ��� ���
			printf("\n\n");
		}
		else if (A == 'D') { // Delete�ϴ� ���
			printf("Delete�� ����? ");
			scanf("%d", &num);
			delete_node(root, num); // ����ڷκ��� �Է¹��� ���� delete����
			inorder(root); // ���� ��ȸ ��� ���
			printf("\n\n");
		}
		else if (A == 'X') { // ���α׷� ����
			printf("���α׷�����\n");
			exit(1);
		}
		else {
			printf("�߸��� �Է�\n");
		}
	}
}