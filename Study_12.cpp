#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "quick_sort.h"
#define SIZE 100
#define INDEX_SIZE 100

typedef struct { // itable 정의
	int key;
	int index;
} itable;
itable index_list[INDEX_SIZE]; // index tabel

int list[SIZE]; // 전역변수로 원래 데이터가 들어가있는 리스트 생성

int seq_search(int key, int low, int high) { // sequential search 함수 정의
	int i;
	for (int i = low;i <= high;i++)
		if (list[i] == key)
			return i;
	return -1;
}

void makeIndexTable(int size, int interval) { // indextable 만드는 함수 생성
	int i, n;
	n = size / interval; // n은 전체 사이즈를 사용자로부터 입력받은 interval로 나눈 값
	if (size % interval > 0)
		n = n + 1;
	for (i = 0;i < n;i++) {
		index_list[i].index = i * interval;//index_list의 index에 저장
		index_list[i].key = list[i * interval]; // index_list의 key에 저장
	}
	printf("\n\n<Index tabel>\n");
	for (i = 0;i < n;i++) { // 반복문을 이용하여 i번째 index_list의 key값 출력
		printf("%3d:%4d\n", i, index_list[i].key);
	}
}

int index_search(int key, int n) { // indexed_search 함수 정의
	int i, low, high;
	if (key<list[0] || key>list[n - 1]) // list의 범위 밖인 경우 함수 종료
		return -1;
	for (i = 0;i < n;i++)
		if (index_list[i].key <= key && index_list[i + 1].key > key) { // 해당키가 포함된 위치 찾기
			printf("index location : %d\n", i); // 해당키 포함된 위치 출력
			break;
		}
	if (i == n) { // 마지막까지 i가 증가된 경우 마지막 index 구간에 key 포함된 경우
		low = index_list[i - 1].index;
		high = n;
	}
	else { // 특정 index i~i+1 사이에 key 포함된 경우
		low = index_list[i].index;
		high = index_list[i + 1].index;
	}
	return seq_search(key, low, high); //sequence search 값으로 리턴해줌
}

int main(void) {
	srand(time(NULL));
	int key, res, interval;
	for (int i = 0;i < SIZE;i++)
		list[i] = rand() % 1000; // 리스트에 0~999사이의 랜덤한 숫자를 담음
	for (int i = 0;i < SIZE;i++) { //list 출력
		if (i % 10 == 0)
			putchar('\n');
		printf("%4d", list[i]);
	}
	printf("\n\n<정렬결과>\n");
	quick_sort(list, 0, SIZE); // quick_sort를 이용하여 정렬해줌
	for (int i = 0;i < SIZE;i++) { // 정렬된 list 다시 출력
		if (i % 10 == 0)
			putchar('\n');
		printf("%4d", list[i]);
	}
	printf("\n\nInput index interval(1~100)");
	scanf("%d", &interval);// 사용자로부터 interval을 입력받음
	makeIndexTable(SIZE, interval); // index table 만듦
	printf("\n\nInput key to search:"); // 사용자로부터 검색할 key값 입력받음
	scanf("%d", &key);
	printf("\n<Indexed_search결과>\n");
	res = index_search(key, INDEX_SIZE);
	if (res != -1) // res가 -1이 아닐 경우는 찾은 경우
		printf("%d is found in position %d\n", key, res);
	else // res가 -1일 경우는 찾지 못했을 경우
		printf("search failed\n");
}