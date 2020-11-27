#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTICES 50

typedef struct GraphType { //GraphType 정의
	int n; // vertex의 수
	int adj_mat[MAX_VERTICES][MAX_VERTICES]; // 2차원 배열
}GraphType;

void init(GraphType* g) { // 그래프 초기화
	int r, c;
	g->n = 0;
	for (r = 0;r < MAX_VERTICES; r++)
		for (c = 0;c < MAX_VERTICES; c++)
			g->adj_mat[r][c] = 0; // 그래프의 모든 원소를 0으로 초기화 함
}

void insert_vertex(GraphType* g, int v) { // vertex 삽입 연산
	if (g->n + 1 > MAX_VERTICES) { // 초과했을 경우
		fprintf(stderr, "그래프 : 정점의 개수 초과\n");
		return;
	}
	else g->n++; // 그렇지 않을 경우 vertex 개수 증가
}

void insert_edge(GraphType* g, int start, int end) { // edge 삽입 연산
	if (start >= g->n || end >= g->n) {
		fprintf(stderr, "그래프 : 정점 번호 오류\n");
		return;
	}
	g->adj_mat[start][end] = 1; // 위치를 1로 set
}

void print_adj_mat(GraphType* g) { // 행렬 출력 함수
	int r, c;
	for (r = 0;r < g->n;r++) { // row 증가
		for (c = 0;c < g->n;c++) // column 증가
			printf("%2d", g->adj_mat[r][c]); // 배열 값 찍기
		printf("\n");
	}
}

int visited1[MAX_VERTICES]; // 재귀를 이용할 때 방문됐는지 안됐는지 체크하는 배열
void dfs_mat(GraphType* g, int v) {
	int w;
	visited1[v] = true; // dfs 시작된 vertex는 방문한 것으로 표시
	printf("vertex%d  ", v); // 방문한 vertex 출력
	for (w = 0;w < g->n;w++) // 해당 vertex의 row를 하나씩 검사해서
		if (g->adj_mat[v][w] && !visited1[w]) // 특정 vertex값이 1인데 아직 방문 안했으면
			dfs_mat(g, w); // 그 vertex(w)로 이동해서 다시 dfs 실행(재귀 호출)
}

typedef int element;
typedef struct StackType { // stacktype 정의
	element data[MAX_VERTICES];
	int top;
}StackType;

void init_stack(StackType* s) { // stack 초기화 함수
	s->top = -1;
}

void error(const char X[]) { //오류 메시지 출력 함수
	fprintf(stderr, X);
}

bool is_full(StackType* s) { // 스택이 꽉 찼는지 아닌지 확인하는 함수
	return (s->top == (MAX_VERTICES - 1)); // top이 최대이면 true 반환
}

bool is_empty(StackType* s) { // 스택이 비었는지 아닌지 확인하는 함수
	return (s->top == -1); // top이 -1이면 빈스택이므로 true 반환
}

element pop(StackType* s) { // pop 함수
	if (is_empty(s)) { // 빈스택이면 에러
		error("Stack empty");
		exit(1);
	}
	else return s->data[(s->top)--]; // pop한 값을 리턴해줌
}

void push(StackType* s, element item) { // push 함수
	if (is_full(s)) { // 스택이 꽉 찼다면 에러
		error("Overflow");
		return;
	}
	else s->data[++(s->top)] = item; // 입력받은 값을 push 해줌
}

int visited2[MAX_VERTICES]; // 스택을 이용할 때 방문됐는지 안됐는지 체크하는 배열
void dfs_stack(GraphType* g, int v) { // 스택과 반복문을 이용해서 dfs
	StackType s; // StackType 생성
	init_stack(&s); // s 초기화
	push(&s, v); // 입력받은 v를 push
	while (!is_empty(&s)) { // 스택이 비어있지 않는 동안 반복
		v = pop(&s); // 스택에서 pop한 값을 v라 함
		if (!visited2[v]) { // v가 방문되지 않았다면
			visited2[v] = true; // v를 방문되었다고 표시하고
			printf("vertex%d  ", v); // 출력해줌
		}
		for (int w = 0;w < g->n;w++) // 반복문을 이용하여
			if (g->adj_mat[v][w] && !visited2[w]) // w가 방문되지 않았다면
				push(&s, w); // w를 push해줌
	}
}

int main(void) {
	GraphType* g;
	g = (GraphType*)malloc(sizeof(GraphType)); // 동적 메모리 할당
	init(g); // g 초기화
	for (int i = 0;i < 5;i++) // 반복문 이용해서 insert_vertex 해주고
		insert_vertex(g, i);
	insert_edge(g, 0, 1); // 값을 입력함
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
	print_adj_mat(g); // 행렬 출력
	printf("<Depth First Search-recursive>\n");
	dfs_mat(g, 0); // 재귀를 이용했을 때 dfs
	printf("\n");
	printf("<Depth First Search-stack>\n");
	dfs_stack(g, 0); // stack과 반복문을 이용했을 때 dfs
	printf("\n");

	for (int i = 0;i < MAX_VERTICES;i++) { // 반복문을 이용해서 두 배열을 초기화 해줌
		visited1[i] = 0;
		visited2[i] = 0;
	}
	printf("\n");

	init(g); // g도 초기화 해줌
	for (int i = 0;i < 6;i++) // 반복문을 이용해서 insert_vertex해줌
		insert_vertex(g, i);
	insert_edge(g, 0, 2); // 값을 입력함
	insert_edge(g, 0, 4);
	insert_edge(g, 1, 5);
	insert_edge(g, 2, 1);
	insert_edge(g, 2, 3);
	insert_edge(g, 4, 5);
	printf("<Graph Matrix>\n");
	print_adj_mat(g); // 행렬 출력
	printf("<Depth First Search-recursive>\n");
	dfs_mat(g, 0); // 재귀를 이용했을 때 dfs
	printf("\n");
	printf("<Depth First Search-stack>\n");
	dfs_stack(g, 0); // stack과 반복문을 이용했을 때 dfs
	printf("\n");
}