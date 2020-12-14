#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTICES 100
#define TRUE 1
#define FALSE 0
#define INF 999

typedef struct GraphNode { // �׷��� ��� ����
	int vertex;
	int weight;
	struct GraphNode* link; // ���� ��� ����Ű�� link
} GraphNode;

typedef struct GraphType {
	int n; // vertex�� ����
	GraphNode* adj_list[MAX_VERTICES]; // vertex���� ũ���� �����͹迭
} GraphType;

void init_graph(GraphType* g) { // �׷��� �ʱ�ȭ
	g->n = 0; // ��� �� 0���� �ʱ�ȭ
	for (int i = 0;i < MAX_VERTICES;i++)
		g->adj_list[i] = NULL; // ��� vertex NULL�� �ʱ�ȭ
}

void insert_vertex(GraphType* g, int v) { // vertex insertion ����
	if (g->n + 1 > MAX_VERTICES) {
		fprintf(stderr, "�׷���:������ ���� �ʰ�\n");
		return;
	}
	else g->n++; // vertex ���� ����
}

void insert_edge(GraphType* g, int u, int v, int w) { // edge insertion ����
	if (u >= g->n || v >= g->n) {
		fprintf(stderr, "�׷���:���� ��ȣ ����\n");
		return;
	}
	GraphNode* node = (GraphNode*)malloc(sizeof(GraphNode)); // �߰��Ǵ� vertex ����
	node->vertex = v;
	node->link = g->adj_list[u]; // ����Ʈ�� �� �տ� insert
	g->adj_list[u] = node; // insert�� ��尡 �� �� vertex�� ��
	node->weight = w;
}

int choose(int distance[], int n, int found[]) {
	int i, min, minpos;
	min = INT_MAX;
	minpos = -1;
	for (i = 0;i < n;i++)
		if (distance[i] < min && !found) {
			min = distance[i];
			minpos = i;
		}
	return minpos;
}

void print_adj_list(GraphType* g) { // ���� ����Ʈ ���
	for (int i = 0;i < g->n;i++) {
		GraphNode* p = g->adj_list[i];
		printf("vertex %d", i);
		while (p != NULL) { // �ݺ��� �̿��ؼ� vertex�� weight �Ѵ� ���
			printf(" -> %d<%d> ", p->vertex, p->weight);
			p = p->link;
		}
		printf("\n");
	}
}

int found[MAX_VERTICES]; // ���õ� vertex�� ����
int distance[MAX_VERTICES]; // spanning tree���� vertex���� �� vertex������ distance

void print_status(GraphType* g) { // ���� ���� ������ִ� �Լ� (�ܰ躰)
	static int step = 1;
	printf("STEP %d : \n", step++);
	printf(" distance: ");
	for (int i = 0; i < g->n;i++) {
		if (distance[i] == INF) // ���Ѵ븦 ���� ��� *�� ǥ��
			printf(" * ");
		else
			printf("%2d ", distance[i]);
	}
	printf("\n");
	printf(" found: ");
	for (int i = 0; i < g->n;i++)
		printf("%2d ", found[i]);
	printf("\n\n");
}


void shortest_path(GraphType* g, int start) { // �ִܰ�� ã�� �Լ�
	GraphNode* node;
	int i;
	int min, now;
	for (i = 0;i < MAX_VERTICES;i++) {
		distance[i] = INF; // distance�� ��� ������ �ǹ��ϴ� ū���� ����
		found[i] = FALSE; // 0�϶� false
	}
	distance[start] = FALSE; // ������� distance�� 0���� ����
	printf("<Shortest Path - Dijkstra ���>\n");
	for (int j = 0; j < g->n;j++) {
		min = INF; // �ּҰ��� �ʱ⿡�� ������ �ǹ��ϴ� ū���� �����ص�
		for (i = 0; i < MAX_VERTICES; i++)
			if (distance[i] < min && !found[i])
			{
				min = distance[i]; // ���� ���þȵ� �ּҰŸ� vertex ã��
				now = i; // ���� ª�� disatnce ���� vertex
			}
		found[now] = TRUE; // �ش� vertex now�� ���տ� �߰�
		node = g->adj_list[now]; // node ����
		while (node != NULL) { // node�� NULL�� ���� ���� ���� �ݺ�
			if (!found[node->vertex]) {
				if (min + node->weight < distance[node->vertex]) // ������ distance���� ���ļ� ���� �Ÿ��� �� ª����
					distance[node->vertex] = min + node->weight; // ���ļ� ���� �Ÿ� ������ ���� update��
			}
			node = node->link; // node�� �Ű���
		}
		print_status(g); // ���� ���� ���
	}
}

int main(void) {
	GraphType* g; // �׷��� ����
	g = (GraphType*)malloc(sizeof(GraphType));
	init_graph(g); // �׷��� �ʱ�ȭ
	for (int i = 0;i < 7;i++)
		insert_vertex(g, i); // vertex insert
	insert_edge(g, 0, 1, 7); // edge insert
	insert_edge(g, 0, 4, 3);
	insert_edge(g, 0, 5, 10);
	insert_edge(g, 1, 0, 7);
	insert_edge(g, 1, 2, 4);
	insert_edge(g, 1, 3, 10);
	insert_edge(g, 1, 4, 2);
	insert_edge(g, 1, 5, 6);
	insert_edge(g, 2, 1, 4);
	insert_edge(g, 2, 3, 2);
	insert_edge(g, 3, 1, 10);
	insert_edge(g, 3, 2, 2);
	insert_edge(g, 3, 4, 11);
	insert_edge(g, 3, 5, 9);
	insert_edge(g, 3, 6, 4);
	insert_edge(g, 4, 0, 3);
	insert_edge(g, 4, 1, 2);
	insert_edge(g, 4, 3, 11);
	insert_edge(g, 4, 6, 5);
	insert_edge(g, 5, 0, 10);
	insert_edge(g, 5, 1, 6);
	insert_edge(g, 5, 3, 9);
	insert_edge(g, 6, 3, 4);
	insert_edge(g, 6, 4, 5);
	printf("<Graph ����>\n");
	print_adj_list(g); // adj_list�� ����Ͽ� Graph���� ������
	printf("\n���� vertex ��ȣ: ");
	int num;
	scanf("%d", &num); // ����ڷ� ���� ���� vertex�Է¹���
	shortest_path(g, num); // �Է¹��� vertex�� ���� �����ϴ� �ִ� ��� �ڵ� ã��
	free(g);
	return 0;
}
