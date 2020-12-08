#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTICES 50

/*graph 인접 행렬 코드*/

typedef struct GraphType {
	int n; // vertex의 수
	int adj_mat[MAX_VERTICES][MAX_VERTICES];
}GraphType;

void init(GraphType* g) { // 그래프 초기화
	int r, c;
	g->n = 0;
	for (r = 0;r < MAX_VERTICES;r++)
		for (c = 0;c < MAX_VERTICES;c++)
			g->adj_mat[r][c] = 0; // 모든 원소 0으로 초기화
}

void insert_vertex(GraphType* g, int v) { // vertex insertion 연산
	if (g->n + 1 > MAX_VERTICES) {
		fprintf(stderr, "그래프: 정점의 개수\n");
		return;
	}
	else g->n++; // vertex 개수 증가
}

void insert_edge(GraphType* g, int start, int end) { // edge insertion 연산
	if (start >= g->n || end >= g->n) {
		fprintf(stderr, "그래프: 정점 번호 오류\n");
		return;
	}
	g->adj_mat[start][end] = 1; // 대칭위치에 모두 1로 set
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