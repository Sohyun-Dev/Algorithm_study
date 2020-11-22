#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode { // TreeNode 정의
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

int get_node_count(TreeNode* exp) { // 이진트리 노드 개수 연산
	if (exp == NULL) return 0;
	else
		return get_node_count(exp->left) + get_node_count(exp->right) + 1; // 각각의 subtree에 대하여 재귀 호출하여 반환된 값에 1을 더하여 return해줌
}

int get_leaf_count(TreeNode* exp) { //이진트리 단말 노드 개수
	if (exp == NULL) return 0;
	else {
		if (exp->left == NULL && exp->right == NULL) return 1; // 단말일때
		else return get_leaf_count(exp->left) + get_leaf_count(exp->right); // 단말이 아닐때 
	}
}

int get_height(TreeNode* exp) { // 이진트리 높이 
	if (exp == NULL) return 0;
	else { // 각각 subtree의 높이를 비교하여 
		int l_height = get_height(exp->left);
		int r_height = get_height(exp->right);
		if (l_height >= r_height) return l_height + 1;// 더 큰 값의 반환값에 1을 더하여 최종적으로 리턴해줌
		else return r_height + 1;
	}
}

int balance(TreeNode* exp) { // balanced tree인지 아닌지 검사하는 함수
	int check;
	if (exp == NULL) return 0;
	else {
		int l_height = get_height(exp->left); // 왼쪽 subtree의 높이를 담음
		int r_height = get_height(exp->right); // 오른쪽 subtree의 높이를 담음
		int dif = l_height - r_height; // 두 subtree의 높이 차이를 변수에 담음
		if (dif >= -1 && dif <= 1) { // 높이의 차이가 1이상 -1이하인 경우
			check = 0; // check변수를 0으로 변경
		}
		else { // 그렇지 않을 경우
			check = 1; // check변수를 1로 변경
		}
	}
	if (check == 0) // check변수가 0인 경우 balanced tree임
		printf("Yes\n");
	else // check변수가 0이 아닐 경우 balanced tree가 아님
		printf("No\n");
}


void pbig(TreeNode* exp, int num) { // 사용자로부터 입력받은 값보다 큰 key값만 출력하는 함수
	if (exp) {
		pbig(exp->left, num);
		if (exp->data > num) // 사용자로부터 입력받은 값보다 key 값이 큰 경우 출력
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
	inorder(exp);// 중위 순회 결과 출력
	printf("\n");
	printf("Number of nodes in tree: %d\n", get_node_count(exp));
	printf("Height of the tree : %d\n", get_height(exp));
	printf("Number of leafs in tree : %d\n", get_leaf_count(exp));
	printf("Balanced tree?");
	balance(exp); // balanced함수인지 아닌지 판단
	printf("Input a number to check:");
	int n;
	scanf("%d", &n);// 사용자로부터 숫자를 입력받음
	printf("numbers greatr than %d:", n);
	pbig(exp, n); // 입력받은 숫자보다 큰 key 값만 출력
	printf("\n");
	return 0;
}