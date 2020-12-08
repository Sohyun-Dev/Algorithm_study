#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTICES 50

/*graph ��������Ʈ �ڵ�*/

typedef struct GraphNode {
	int vertex;
	struct GraphNode* link; // ���� ��带 ����Ű�� link
} GraphNode;

typedef struct GraphType {
	int n; // vertex�� ����
	GraphNode* adj_list[MAX_VERTICES]; // vertex���� ũ���� ������ �迭
} GraphType;

void init(GraphType* g) { // �׷��� �ʱ�ȭ
	g->n = 0; // ��� �� 0���� �ʱ�ȭ
	for (int i = 0;i < MAX_VERTICES;i++)
		g->adj_list[i] = NULL; // ��� vertex NULL�� �ʱ�ȭ
}

void insert_vertex(GraphType* g, int v) { // vertex insertion ����
	if (g->n + 1 > MAX_VERTICES) {
		fprintf(stderr, "�׷���: ������ ���� �ʰ�\n");
		return;
	}
	else g->n++; // vertex ���� ����
}

void insert_edge(GraphType* g, int u, int v) { // edge insertion ����
	if (u >= g->n || v >= g->n) {
		fprintf(stderr, "�׷���: ���� ��ȣ ����\n");
		return;
	}
	GraphNode* node = (GraphNode*)malloc(sizeof(GraphNode)); // �߰��Ǵ� vertex ����
	node->vertex = v;
	node->link = g->adj_list[u]; // ����Ʈ�� �� �տ� insert
	g->adj_list[u] = node; // insert�� ��尡 �� �� vertex�� ��
}

void print_adj_list(GraphType* g) {
	for (int i = 0;i < g->n;i++) {
		GraphNode* p = g->adj_list[i]; // �� vertex���� �ݺ��ؼ� ���
		printf("vertex %d�� adj list ", i);
		while (p != NULL) {
			printf(" -> %d ", p->vertex);
			p = p->link;
		}
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
	insert_edge(g, 1, 0);
	insert_edge(g, 0, 2);
	insert_edge(g, 2, 0);
	insert_edge(g, 0, 3);
	insert_edge(g, 3, 0);
	insert_edge(g, 1, 2);
	insert_edge(g, 2, 1);
	insert_edge(g, 2, 3);
	insert_edge(g, 3, 2);
	print_adj_list(g);
	free(g);
	return 0;
}
