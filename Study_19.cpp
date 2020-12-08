#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTICES 50

/*graph 인접리스트 코드*/

typedef struct GraphNode {
	int vertex;
	struct GraphNode* link; // 다음 노드를 가리키는 link
} GraphNode;

typedef struct GraphType {
	int n; // vertex의 개수
	GraphNode* adj_list[MAX_VERTICES]; // vertex개수 크기의 포인터 배열
} GraphType;

void init(GraphType* g) { // 그래프 초기화
	g->n = 0; // 노드 수 0으로 초기화
	for (int i = 0;i < MAX_VERTICES;i++)
		g->adj_list[i] = NULL; // 모든 vertex NULL로 초기화
}

void insert_vertex(GraphType* g, int v) { // vertex insertion 연산
	if (g->n + 1 > MAX_VERTICES) {
		fprintf(stderr, "그래프: 정점의 개수 초과\n");
		return;
	}
	else g->n++; // vertex 개수 증가
}

void insert_edge(GraphType* g, int u, int v) { // edge insertion 연산
	if (u >= g->n || v >= g->n) {
		fprintf(stderr, "그래프: 정점 번호 오류\n");
		return;
	}
	GraphNode* node = (GraphNode*)malloc(sizeof(GraphNode)); // 추가되는 vertex 생성
	node->vertex = v;
	node->link = g->adj_list[u]; // 리스트의 맨 앞에 insert
	g->adj_list[u] = node; // insert된 노드가 맨 앞 vertex가 됨
}

void print_adj_list(GraphType* g) {
	for (int i = 0;i < g->n;i++) {
		GraphNode* p = g->adj_list[i]; // 각 vertex마다 반복해서 출력
		printf("vertex %d의 adj list ", i);
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
