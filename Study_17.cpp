#include <stdio.h>
#include <stdlib.h>
#define MAX_ELEMENT 200
typedef struct {
	int key;
}element;

typedef struct { //HeapType 정의
	element heap[MAX_ELEMENT];
	int heap_size;
} HeapType;


//**정적 메모리 할당/동적 메모리 할당 중 택 1

// HeapType heap; //정적 메모리 할당 사용

HeapType* create() { // 동적 메모리 할당
	return (HeapType*)malloc(sizeof(HeapType));
}

void init(HeapType* h) {
	h->heap_size = 0;
}
 
void insert_max_heap(HeapType* h, element item) { // item 노드를 추가하는 과정
	int i;
	i = ++(h->heap_size); // 노드 추가 후 증가된 말단 노드 인덱스를 i에 대입
	while ((i != 1) && (item.key > h->heap[i / 2].key)) { // 트리를 거슬러 올라가면서 부모 노드 key값과 비교
		h->heap[i] = h->heap[i / 2]; // 추가된 노드 key값보다 작은 경우 부모 노드를 내림
		i /= 2; // 인덱스 새로운 위치(부모)로 이동
	}
	h->heap[i] = item; // 최종 결정된 위치에 새로운 노드를 insert
}

element delete_max_heap(HeapType* h) { 
	int parent = 1; 
	int child = 2; // 두번째 노드부터 root 노드와 비교 시작
	element item = h->heap[1]; // 삭제되는 노드(삭제 후 반환)
	element temp = h->heap[h->heap_size--]; // 말단노드를 temp에 대립(노드 삭제 후 heap_size가 감소)
	while (child <= h->heap_size) { // 최대 말단까지 트리를 내려가면서 자식노드 key값과 temp key 비교
		if ((child < h->heap_size) && (h->heap[child].key < h->heap[child + 1].key)) // sibling이 있을 때 둘 중 큰 값 찾기
			child++; // sibling이 비교대상 노드가 됨(subtree 선택)
		if (temp.key >= h->heap[child].key) // 자식 노드보다 신규노드key가 크면 위치 확정되어 반복 종료
			break; 
		h->heap[parent] = h->heap[child]; // 자식노드 key가 더 크면 parent 노드에 child 노드 복사
		parent = child; // parent 인덱스를 child 인덱스로 변경
		child *= 2; // child 인덱스는 그 아래 child로 변경
	}
	h->heap[parent] = temp; // 확정위치(parent)에 신규노드 insert
	return item; 
}

int main(void)
{
	element e1 = { 10 }, e2 = { 5 }, e3 = { 30 }, e4, e5, e6;
	HeapType* heap = create(); // 동적 메모리 할당 사용
	init(heap);
	insert_max_heap(heap, e1);
	insert_max_heap(heap, e2);
	insert_max_heap(heap, e3);

	// 순서대로 delete하고 출력
	e4 = delete_max_heap(heap);
	printf("< %d > ", e4.key);
	e5 = delete_max_heap(heap);
	printf("< %d > ", e5.key);
	e6 = delete_max_heap(heap);
	printf("< %d >\n", e6.key);

	free(heap);
	return 0;
}