#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode { // TreeNode 정의
	int key;
	struct TreeNode* left, * right;
} TreeNode;


TreeNode* new_node(int item) {
	TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode)); // 동적 메모리 할당
	node->key = item; // 값(item)을 key에 복사
	node->left = node->right = NULL; // child 노드를 NULL로 초기화
	return node; // 새로 생성된 노드 반환
}

TreeNode* insert_node(TreeNode* node, int key) { // 해당 위치 찾아서 key 값 갖는 노드 insert 
	if (node == NULL) return new_node(key); // 트리가 공백일 경우 insert 된 새로운 노드를 반환
	if (key < node->key) // insert 할 값이 root의 키값보다 작으면 left subtree를 root로 insert 재귀 호출
		node->left = insert_node(node->left, key);
	else if (key > node->key) // insert 할 값이 root의 키값보다 크면 right subtree를 root로 insert 재귀 호출
		node->right = insert_node(node->right, key);
	return node; // 변경된 root 포인터 반환
}

void inorder(TreeNode* root) { // 순서에 맞게 출력하는 함수
	if (root == NULL) return; // empty tree 이면 NULL 반환
	else {
		inorder(root->left); // left subtree traverse
		printf(" [%d]", root->key);
		inorder(root->right); // right subtree traverse
	}
}

TreeNode* min_value_node(TreeNode* node) { // 가장 왼쪽의 단말 노드 찾기(최소값)
	TreeNode* current = node;
	while (current->left != NULL) // NULL이 될 때 까지 계속 왼쪽 child로 찾아 내려감
		current = current->left;
	return current;
}

TreeNode* max_value_node(TreeNode* node) { // 가장 오른쪽의 단말 노드 찾기(최대값)
	TreeNode* current = node;
	while (current->right != NULL) // NULL이 될 때 까지 계속 오른쪽 child로 찾아 내려감
		current = current->right;
	return current;
}

TreeNode* delete_node(TreeNode* root, int key) { // key가 저장된 노드를 찾아 삭제하고 새로운 root 반환
	if (root == NULL) return root; // root가 NULL일 때는 그냥 root return
	else if (root->key > key) // 왼쪽 subtree에서 key값을 찾아 삭제하도록 재귀호출
		root->left = delete_node(root->left, key); // 새로운 left child로 변경
	else if (root->key < key) // 오른쪽 subtree에서 key값을 찾아 삭제하도록 재귀호출
		root->right = delete_node(root->right, key); // 새로운 right child로 변경
	else { // delete하고자 하는 key를 찾았을 때
		if (root->left == NULL) { // leaf노드 이거나 child를 하나 갖을 경우에 (left가 NULL일 경우) 
			TreeNode* temp = root->right;
			free(root);
			return temp;
		}
		else if (root->right == NULL) { // right가 NULL일 경우
			TreeNode* temp = root->left;
			free(root);
			return temp;
		}
		//child가 둘 다 있는 경우 
		TreeNode* temp1 = max_value_node(root->left); // 오른쪽  subtree의 가장 왼쪽 값을 갖는 노드 찾기(최솟값)
		TreeNode* temp2 = min_value_node(root->right); // 왼쪽 subtree의 가장 오른쪽 값을 갖는 노드 찾기(최대값)
		printf("left subtree의 max : %d\n", temp1->key); // 왼쪽 subtree의 max와 오른쪽 subtree의 min 출력
		printf("right subtree의 min :%d\n", temp2->key);

		int diff1 = key - temp1->key; // key 값과 왼쪽 subtree의 최대값의 차이를 담음
		int diff2 = temp2->key - key; // key 값과 오른쪽 subtree의 최솟값의 차이를 담음
		if (diff1 >= diff2) { // 오른쪽 subtree의 최솟값과 key 값의 차이가 더 작을 때 
			root->key = temp2->key; // 가까운 key값을 삭제할 위치에 복사
			root->right = delete_node(root->right, temp2->key); // 복사된 값을 갖고 있던 노드 삭제
			printf("original value : %d   new value : %d\n", key, root->key);
		}
		else { // 왼쪽 subtree의 최솟값과 key값의 차이가 더 작을 때
			root->key = temp1->key; // 가까운 key값을 삭제할 위치에 복사
			root->left = delete_node(root->left, temp1->key); // 복사된 값을 갖고 있던 노드 삭제
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

	printf("이진 탐색 트리 중위 순회 결과 \n");
	inorder(root); // inorder traverse
	printf("\n\n");

	while (true) { // while문을 이용하여 반복
		char A;
		printf("* operation 선택 : Insert(I) / Delete(D) / Exit(X) :");
		scanf("%s", &A); // 사용자로부터 문자열을 입력받음
		getchar();
		int num;
		if (A == 'I') { // Insert하는 경우
			printf("Insert할 값은? ");
			scanf("%d", &num);
			insert_node(root, num); // 사용자로부터 입력받은 값을 insert해줌
			inorder(root); // 중위 순회 결과 출력
			printf("\n\n");
		}
		else if (A == 'D') { // Delete하는 경우
			printf("Delete할 값은? ");
			scanf("%d", &num);
			delete_node(root, num); // 사용자로부터 입력받은 값을 delete해줌
			inorder(root); // 중위 순회 결과 출력
			printf("\n\n");
		}
		else if (A == 'X') { // 프로그램 종료
			printf("프로그램종료\n");
			exit(1);
		}
		else {
			printf("잘못된 입력\n");
		}
	}
}