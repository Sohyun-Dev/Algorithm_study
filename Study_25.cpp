#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTICES 100
#define TRUE 1
#define FALSE 0
#define INF 999

typedef struct GraphNode { // 그래프 노드 정의
	int vertex;
	int weight;
	struct GraphNode* link; // 다음 노드 가리키는 link
} GraphNode;

typedef struct GraphType {
	int n; // vertex의 개수
	GraphNode* adj_list[MAX_VERTICES]; // vertex개수 크기의 포인터배열
} GraphType;

void init_graph(GraphType* g) { // 그래프 초기화
	g->n = 0; // 노드 수 0으로 초기화
	for (int i = 0;i < MAX_VERTICES;i++)
		g->adj_list[i] = NULL; // 모든 vertex NULL로 초기화
}

void insert_vertex(GraphType* g, int v) { // vertex insertion 연산
	if (g->n + 1 > MAX_VERTICES) {
		fprintf(stderr, "그래프:정점의 개수 초과\n");
		return;
	}
	else g->n++; // vertex 개수 증가
}

void insert_edge(GraphType* g, int u, int v, int w) { // edge insertion 연산
	if (u >= g->n || v >= g->n) {
		fprintf(stderr, "그래프:정점 번호 오류\n");
		return;
	}
	GraphNode* node = (GraphNode*)malloc(sizeof(GraphNode)); // 추가되는 vertex 생성
	node->vertex = v;
	node->link = g->adj_list[u]; // 리스트의 맨 앞에 insert
	g->adj_list[u] = node; // insert된 노드가 맨 앞 vertex가 됨
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

void print_adj_list(GraphType* g) { // 인접 리스트 출력
	for (int i = 0;i < g->n;i++) {
		GraphNode* p = g->adj_list[i];
		printf("vertex %d", i);
		while (p != NULL) { // 반복문 이용해서 vertex와 weight 둘다 출력
			printf(" -> %d<%d> ", p->vertex, p->weight);
			p = p->link;
		}
		printf("\n");
	}
}

int found[MAX_VERTICES]; // 선택된 vertex의 집합
int distance[MAX_VERTICES]; // spanning tree내의 vertex에서 각 vertex까지의 distance

void print_status(GraphType* g) { // 현재 상태 출력해주는 함수 (단계별)
	static int step = 1;
	printf("STEP %d : \n", step++);
	printf(" distance: ");
	for (int i = 0; i < g->n;i++) {
		if (distance[i] == INF) // 무한대를 갖는 경우 *로 표시
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


void shortest_path(GraphType* g, int start) { // 최단경로 찾는 함수
	GraphNode* node;
	int i;
	int min, now;
	for (i = 0;i < MAX_VERTICES;i++) {
		distance[i] = INF; // distance를 모두 무한을 의미하는 큰수로 설정
		found[i] = FALSE; // 0일때 false
	}
	distance[start] = FALSE; // 출발점의 distance는 0으로 설정
	printf("<Shortest Path - Dijkstra 결과>\n");
	for (int j = 0; j < g->n;j++) {
		min = INF; // 최소값도 초기에는 무한을 의미하는 큰수로 설정해둠
		for (i = 0; i < MAX_VERTICES; i++)
			if (distance[i] < min && !found[i])
			{
				min = distance[i]; // 아직 선택안된 최소거리 vertex 찾기
				now = i; // 가장 짧은 disatnce 갖는 vertex
			}
		found[now] = TRUE; // 해당 vertex now를 집합에 추가
		node = g->adj_list[now]; // node 생성
		while (node != NULL) { // node가 NULL이 되지 않을 동안 반복
			if (!found[node->vertex]) {
				if (min + node->weight < distance[node->vertex]) // 원래의 distance보다 거쳐서 가는 거리가 더 짧으면
					distance[node->vertex] = min + node->weight; // 거쳐서 가는 거리 값으로 새로 update함
			}
			node = node->link; // node를 옮겨줌
		}
		print_status(g); // 최종 상태 출력
	}
}

int main(void) {
	GraphType* g; // 그래프 생성
	g = (GraphType*)malloc(sizeof(GraphType));
	init_graph(g); // 그래프 초기화
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
	printf("<Graph 형태>\n");
	print_adj_list(g); // adj_list를 출력하여 Graph형태 보여줌
	printf("\n시작 vertex 번호: ");
	int num;
	scanf("%d", &num); // 사용자로 부터 시작 vertex입력받음
	shortest_path(g, num); // 입력받은 vertex로 부터 시작하는 최단 경로 코드 찾음
	free(g);
	return 0;
}
