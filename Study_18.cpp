#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTICES 50

/*graph ���� ��� �ڵ�*/

typedef struct GraphType {
	int n; // vertex�� ��
	int adj_mat[MAX_VERTICES][MAX_VERTICES];
}GraphType;

void init(GraphType* g) { // �׷��� �ʱ�ȭ
	int r, c;
	g->n = 0;
	for (r = 0;r < MAX_VERTICES;r++)
		for (c = 0;c < MAX_VERTICES;c++)
			g->adj_mat[r][c] = 0; // ��� ���� 0���� �ʱ�ȭ
}

void insert_vertex(GraphType* g, int v) { // vertex insertion ����
	if (g->n + 1 > MAX_VERTICES) {
		fprintf(stderr, "�׷���: ������ ����\n");
		return;
	}
	else g->n++; // vertex ���� ����
}

void insert_edge(GraphType* g, int start, int end) { // edge insertion ����
	if (start >= g->n || end >= g->n) {
		fprintf(stderr, "�׷���: ���� ��ȣ ����\n");
		return;
	}
	g->adj_mat[start][end] = 1; // ��Ī��ġ�� ��� 1�� set
	g->adj_mat[end][start] = 1;
}

void print_adj_mat(GraphType* g) {
	int r, c;
	for (r = 0;r < g->n;r++) {
		for (c = 0;c < g->n;c++)
			printf("%2d", g->adj_mat[r][c]);
		printf("\n");
	}
}



int main(void) {
	GraphType* g;
	g = (GraphType*)malloc(sizeof(GraphType));
	init(g);
	for (int i = 0;i < 4;i++)
		insert_vertex(g, i);
	insert_edge(g, 0, 1);
	insert_edge(g, 0, 2);
	insert_edge(g, 0, 3);
	insert_edge(g, 1, 2);
	insert_edge(g, 2, 3);
	print_adj_mat(g);
	free(g);
	return 0;
}