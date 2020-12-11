#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode { // TreeNode 생성
	int data;
	struct TreeNode* left, * right;
}TreeNode;

int sum_key(TreeNode* p) { // 노드의 key값의 합계를 구하는 함수
	if (p == NULL)
		return 0;
	else { //p가 null이 아니라면
		return p->data + sum_key(p->left) + sum_key(p->right); // 재귀
	}
}

int one_child_node(TreeNode* node) { // child를 한 개 갖는 노드의 수
	int count = 0;
	if (node != NULL) { // node가 NULL이 아닐 경우에
		if ((node->left == NULL && node->right != NULL) || (node->right == NULL && node->left != NULL)) // 노드의 left나 right 중 하나만 NULL이고 다른 하나는 NULL이 아닌 경우
			return 1 + one_child_node(node->left) + one_child_node(node->right); // 재귀
		else
			count = one_child_node(node->left) + one_child_node(node->right); // 재귀
	}
	return count; // child를 한 개 갖는 노드의 수 리턴 해줌
}

int Findmax(TreeNode* node) { // 최대 key값 찾는 함수
	int root, left, right;
	int max = 0; // 최대 key값 담을 변수
	if (node != NULL) { // node가 null이 아닐경우
		root = node->data;
		left = Findmax(node->left); // 재귀
		right = Findmax(node->right); //재귀
		if (left > right)  // left와 right 먼저 비교하여 최댓값 찾기
			max = left;
		else max = right;
		if (root > max) // root와 max 값을 다시 비교 최댓값 찾기
			max = root;
	}
	return max; //최댓값 리턴해줌
}

int Findmin(TreeNode* node) { // 최소 key 값 갖는 함수
	int root, left, right;
	int min = 999; // 최소 key값 담을 변수
	if (node != NULL) { // node가 null 이 아닐 경우
		root = node->data;
		left = Findmin(node->left); // 재귀
		right = Findmin(node->right); // 재귀
		if (left < right) // left와 right 먼저 비교하여 최솟값 찾기
			min = left;
		else min = right;
		if (root < min) // root와 min 값을 비교하여 최솟값 찾기
			min = root;
	}
	return min; // 최솟값 리턴해줌
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
	printf("Sum of keys in binary tree: %d\n", sum_key(exp)); // key값의 합계 출력
	printf("Num of one child nodes: %d\n", one_child_node(exp)); // child를 한 개 갖는 노드의 수 출력
	printf("Max value: %d\n", Findmax(exp)); // 최대 key값 출력
	printf("Min value: %d\n", Findmin(exp)); // 최소 key값 출력
}