#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_SIZE 10
#define SWAP(x,y,t) ((t)=(x), (x)=(y), (y)=(t)) // switch를 위해 매크로로 swap 정의

int partition(int list[], int left, int right, int num) { // 분할하는 함수
	int pivot = list[left]; // pivot의 초기값은 list의 left값
	printf("* pivot: %d\n", pivot); // pivot 값 출력
	int temp, low, high;
	low = left; // low와 high의 초기값 설정
	high = right + 1;
	do {
		do
			low++; // 증가시킨 다음에 조건 체크
		while (list[low] < pivot); // left 다음 요소부터 증가하면서 pivot 값 이상인 요소 찾기
		do
			high--; // 감소시킨 다음에 조건 체크
		while (list[high] > pivot); // right부터 줄여가면서 pivot 값 이하인 요소 찾기
		if (low < high) SWAP(list[low], list[high], temp); // 두 요소 switch
	} while (low < high); // low와 high가 교차할 때 까지 반복
	SWAP(list[left], list[high], temp); // pivot을 중앙에 위치시킴(파이널 위치 - high가 가리키는 값으로 이동)
	for (int i = 0;i < num;i++) // list 출력
		printf("%d ", list[i]);
	printf("\n");
	printf("left size: %d    right size: %d\n", low - left - 1, right - high); // 단계마다 left와 right의 사이즈 출력
	return high; // pivot 위치 반환
}

void quick_sort(int list[], int left, int right, int num) { //quick_sort 함수
	if (left < right) { // left가 right보다 작을 때만
		int p = partition(list, left, right, num); // partition 호출해서 pivot 찾기
		quick_sort(list, left, p - 1, num); // pivot 중심으로 pivot 바로 앞까지 재귀 호출
		quick_sort(list, p + 1, right, num); // pivot 중심으로 pivot 다음부터 끝까지 재귀호출
	}
}

int main(void) {
	int i, n;
	printf("Input size of list(1~10):");
	scanf("%d", &n); // 사용자로부터 1~10사이의 숫자를 입력받음
	int list[MAX_SIZE];
	printf("Input %d numbers in the list\n", n);
	for (i = 0;i < n;i++)
		scanf("%d", &list[i]); // 사용자로부터 리스트의 값을 입력받음
	printf("\n<Before sorting>\n");
	for (i = 0;i < n;i++)
		printf("%d ", list[i]); // sort 전 list 출력
	printf("\n");
	quick_sort(list, 0, n - 1, n); // quick sort 
	printf("\n<After Quick Sorting>\n");
	for (i = 0;i < n;i++)
		printf("%d ", list[i]); // sort 후 list 출력
	printf("\n");
	return 0;
}