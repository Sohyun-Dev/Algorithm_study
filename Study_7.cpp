#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTICES 50

typedef struct GraphType { //GraphType ����
	int n; // vertex�� ��
	int adj_mat[MAX_VERTICES][MAX_VERTICES]; // 2���� �迭
}GraphType;

void init(GraphType* g) { // �׷��� �ʱ�ȭ
	int r, c;
	g->n = 0;
	for (r = 0;r < MAX_VERTICES; r++)
		for (c = 0;c < MAX_VERTICES; c++)
			g->adj_mat[r][c] = 0; // �׷����� ��� ���Ҹ� 0���� �ʱ�ȭ ��
}

void insert_vertex(GraphType* g, int v) { // vertex ���� ����
	if (g->n + 1 > MAX_VERTICES) { // �ʰ����� ���
		fprintf(stderr, "�׷��� : ������ ���� �ʰ�\n");
		return;
	}
	else g->n++; // �׷��� ���� ��� vertex ���� ����
}

void insert_edge(GraphType* g, int start, int end) { // edge ���� ����
	if (start >= g->n || end >= g->n) {
		fprintf(stderr, "�׷��� : ���� ��ȣ ����\n");
		return;
	}
	g->adj_mat[start][end] = 1; // ��ġ�� 1�� set
}

void print_adj_mat(GraphType* g) { // ��� ��� �Լ�
	int r, c;
	for (r = 0;r < g->n;r++) { // row ����
		for (c = 0;c < g->n;c++) // column ����
			printf("%2d", g->adj_mat[r][c]); // �迭 �� ���
		printf("\n");
	}
}

int visited1[MAX_VERTICES]; // ��͸� �̿��� �� �湮�ƴ��� �ȵƴ��� üũ�ϴ� �迭
void dfs_mat(GraphType* g, int v) {
	int w;
	visited1[v] = true; // dfs ���۵� vertex�� �湮�� ������ ǥ��
	printf("vertex%d  ", v); // �湮�� vertex ���
	for (w = 0;w < g->n;w++) // �ش� vertex�� row�� �ϳ��� �˻��ؼ�
		if (g->adj_mat[v][w] && !visited1[w]) // Ư�� vertex���� 1�ε� ���� �湮 ��������
			dfs_mat(g, w); // �� vertex(w)�� �̵��ؼ� �ٽ� dfs ����(��� ȣ��)
}

typedef int element;
typedef struct StackType { // stacktype ����
	element data[MAX_VERTICES];
	int top;
}StackType;

void init_stack(StackType* s) { // stack �ʱ�ȭ �Լ�
	s->top = -1;
}

void error(const char X[]) { //���� �޽��� ��� �Լ�
	fprintf(stderr, X);
}

bool is_full(StackType* s) { // ������ �� á���� �ƴ��� Ȯ���ϴ� �Լ�
	return (s->top == (MAX_VERTICES - 1)); // top�� �ִ��̸� true ��ȯ
}

bool is_empty(StackType* s) { // ������ ������� �ƴ��� Ȯ���ϴ� �Լ�
	return (s->top == -1); // top�� -1�̸� �����̹Ƿ� true ��ȯ
}

element pop(StackType* s) { // pop �Լ�
	if (is_empty(s)) { // �����̸� ����
		error("Stack empty");
		exit(1);
	}
	else return s->data[(s->top)--]; // pop�� ���� ��������
}

void push(StackType* s, element item) { // push �Լ�
	if (is_full(s)) { // ������ �� á�ٸ� ����
		error("Overflow");
		return;
	}
	else s->data[++(s->top)] = item; // �Է¹��� ���� push ����
}

int visited2[MAX_VERTICES]; // ������ �̿��� �� �湮�ƴ��� �ȵƴ��� üũ�ϴ� �迭
void dfs_stack(GraphType* g, int v) { // ���ð� �ݺ����� �̿��ؼ� dfs
	StackType s; // StackType ����
	init_stack(&s); // s �ʱ�ȭ
	push(&s, v); // �Է¹��� v�� push
	while (!is_empty(&s)) { // ������ ������� �ʴ� ���� �ݺ�
		v = pop(&s); // ���ÿ��� pop�� ���� v�� ��
		if (!visited2[v]) { // v�� �湮���� �ʾҴٸ�
			visited2[v] = true; // v�� �湮�Ǿ��ٰ� ǥ���ϰ�
			printf("vertex%d  ", v); // �������
		}
		for (int w = 0;w < g->n;w++) // �ݺ����� �̿��Ͽ�
			if (g->adj_mat[v][w] && !visited2[w]) // w�� �湮���� �ʾҴٸ�
				push(&s, w); // w�� push����
	}
}

int main(void) {
	GraphType* g;
	g = (GraphType*)malloc(sizeof(GraphType)); // ���� �޸� �Ҵ�
	init(g); // g �ʱ�ȭ
	for (int i = 0;i < 5;i++) // �ݺ��� �̿��ؼ� insert_vertex ���ְ�
		insert_vertex(g, i);
	insert_edge(g, 0, 1); // ���� �Է���
	insert_edge(g, 0, 2);
	insert_edge(g, 0, 3);
	insert_edge(g, 1, 0);
	insert_edge(g, 1, 4);
	insert_edge(g, 2, 0);
	insert_edge(g, 2, 4);
	insert_edge(g, 3, 0);
	insert_edge(g, 4, 1);
	insert_edge(g, 4, 2);
	printf("<Graph Matrix>\n");
	print_adj_mat(g); // ��� ���
	printf("<Depth First Search-recursive>\n");
	dfs_mat(g, 0); // ��͸� �̿����� �� dfs
	printf("\n");
	printf("<Depth First Search-stack>\n");
	dfs_stack(g, 0); // stack�� �ݺ����� �̿����� �� dfs
	printf("\n");

	for (int i = 0;i < MAX_VERTICES;i++) { // �ݺ����� �̿��ؼ� �� �迭�� �ʱ�ȭ ����
		visited1[i] = 0;
		visited2[i] = 0;
	}
	printf("\n");

	init(g); // g�� �ʱ�ȭ ����
	for (int i = 0;i < 6;i++) // �ݺ����� �̿��ؼ� insert_vertex����
		insert_vertex(g, i);
	insert_edge(g, 0, 2); // ���� �Է���
	insert_edge(g, 0, 4);
	insert_edge(g, 1, 5);
	insert_edge(g, 2, 1);
	insert_edge(g, 2, 3);
	insert_edge(g, 4, 5);
	printf("<Graph Matrix>\n");
	print_adj_mat(g); // ��� ���
	printf("<Depth First Search-recursive>\n");
	dfs_mat(g, 0); // ��͸� �̿����� �� dfs
	printf("\n");
	printf("<Depth First Search-stack>\n");
	dfs_stack(g, 0); // stack�� �ݺ����� �̿����� �� dfs
	printf("\n");
}