#include <stdio.h>
#include <stdlib.h>
#define MAX_ELEMENT 200
typedef struct {
	int key;
} element;

typedef struct { // HeapType 정의
	element heap[MAX_ELEMENT];
	int heap_size;
} HeapType;

HeapType* create() { // 동적 메모리 할당을 이용
	return (HeapType*)malloc(sizeof(HeapType));
}

void init(HeapType* h) { // 초기화 함수
	h->heap_size = 0;
}

void insert_max_heap(HeapType* h, element item) { // item 노드를 추가하는 함수(max heap)
	int i;
	i = ++(h->heap_size); // 노드 추가 후 증가된 말단 노드 인덱스를 i에 넣음
	while ((i != 1) && (item.key > h->heap[i / 2].key)) { // 트리를 거슬러 올라가면서 부모 노드 key 값과 비교
		h->heap[i] = h->heap[i / 2]; // 추가된 노드 key값보다 작은 경우 부모노드를 내림
		i /= 2; // 인덱스 새로운 위치(부모)로 이동
	}
	h->heap[i] = item; // 최종 결정된 위치에 새로운 노드를 insert함
}

element delete_max_heap(HeapType* h) { // delete하는 함수(max heap)
	int parent = 1, child = 2; // 두번째 노드부터 root노드와 비교시작
	element item = h->heap[1]; // 삭제되는 노드(삭제 후 반환하기 위해)
	element temp = h->heap[h->heap_size--]; // 말단노드 temp에 대입(노드 삭제 후 heap_size 감소)
	while (child <= h->heap_size) { // 최대 말단까지 트리를 내려가면서 자식노드 key값과 temp key 비교
		if ((child < h->heap_size) && (h->heap[child].key < h->heap[child + 1].key)) // sibling이 있을 때 둘 중 큰 값 찾기
			child++; // sibling이 비교대상 노드가 됨(subtree 선택)
		if (temp.key >= h->heap[child].key) break; // 자식노드보다 신규노드 key가 크면 위치 확정되어 반복 종료
		h->heap[parent] = h->heap[child]; //자식노드 key가 더 크면 parent노드에 child 노드 복사
		parent = child; // parent 인덱스를 child 인덱스로 변경
		child *= 2; // child 인덱스는 그 아래 child로 변경
	}
	h->heap[parent] = temp; // 확정위치(parent)에 신규노드 insert
	return item;
}

void insert_min_heap(HeapType* h, element item) { // 노드를 추가하는 함수(min heap)
	int i;
	i = ++(h->heap_size); // 노드 증가 후 증가된 말단 노드 인덱스를 i에 비교
	while ((i != 1) && (item.key < h->heap[i / 2].key)) { //트리를 거슬러 올라가면서 부모 노드 key 값과 비교
		h->heap[i] = h->heap[i / 2]; // 추가된 노드 key값보다 큰 경우 부모노드를 내림
		i /= 2; //인덱스 새로운 위치(부모)로 이동
	}
	h->heap[i] = item; // 최종 결정된 위치에 새로운 노드를 삽입
}

element delete_min_heap(HeapType* h) { // delete 하는 함수(min heap)
	int parent = 1, child = 2; // 두번째 노드부터 root노드와 비교시작
	element item = h->heap[1]; // 삭제되는 노드(삭제 후 반환하기 위해)
	element temp = h->heap[(h->heap_size)--]; // 말단노드 temp에 대입(노드 삭제 후 heap_size 감소)
	while (child <= h->heap_size) { // 최대 말단까지 트리를 내려가면서 자식노드 key값과 temp key 비교
		if ((child < h->heap_size) && (h->heap[child].key > h->heap[child + 1].key))
			child++; // sibling이 있는 경우 둘 중 작은 값 찾기
		if (temp.key < h->heap[child].key) break; // 자식노드보다 신규노드 key가 작으면 위치 확정되어 반복 종료
		h->heap[parent] = h->heap[child]; // 자식노드 key가 더 작으면 parent 노드에 child 노드 복사
		parent = child; // parent 인덱스를 child 인덱스로 변경
		child *= 2; // child 인덱스는 그 아래 child로 변경
	}
	h->heap[parent] = temp; // 확정위치(parent)에 신규노드 삽입
	return item;
}

void print_heap(HeapType* h) { // heap 전체를 출력하는 함수 
	int i;
	for (i = 1;i <= h->heap_size;i++) // 반복문을 돌면서 전체 출력
		printf("%d ", h->heap[i]);
	printf("\n");
}

int main(void) {
	HeapType* heap1 = create(); //heap1, heap2 생성
	HeapType* heap2 = create();
	init(heap1); // heap1, heap2 초기화
	init(heap2);
	while (true) { // while문을 이용하여 반복
		char A;
		printf("*Input Operation I(Insert)  D(Delete)  X(Exit):");
		scanf("%s", &A); // 사용자로부터 문자열을 입력받음
		getchar();
		switch (A) {
		case 'I': // I를 입력받은 경우
			printf("Input value to insert:");
			element insert;
			scanf("%d", &insert); // 사용자로부터 삽입할 value를 입력받음
			insert_max_heap(heap1, insert); // maxheap, min heap에 맞게 insert
			insert_min_heap(heap2, insert);
			printf("<MAX Heap>\n"); // max_heap, min_heap 맞게 삽입한 heap 출력
			print_heap(heap1);
			printf("<Min Heap>\n");
			print_heap(heap2);
			break;

		case 'D': // 사용자로부터 D를 입력받았을 경우
			delete_max_heap(heap1); // maxheap, min heap에 맞게 delete
			delete_min_heap(heap2);
			printf("<MAX Heap>\n");// maxheap, min heap에 맞게 delete한 heap 출력
			print_heap(heap1);
			printf("<Min Heap>\n");
			print_heap(heap2);
			break;

		case 'X': // 사용자로부터 X를 입력받았을 경우
			exit(1); // 프로그램 종료
			break;

		default: // 그외에 것들을 입력받았을 경우 잘못된 입력이라고 출력
			printf("Wrong Input\n");
		}
	}
}
