#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_SIZE 50
#define SWAP(x,y,t) ((t)=(x), (x)=(y), (y)=(t)) // switch를 위해 매크로로 swap 정의

int partition1(int list[], int left, int right) {
	int pivot = list[left];
	printf("* pivot: %d\n", pivot); // pivot 값 출력
	int temp, low, high;
	low = left;
	high = right + 1;
	do {
		do
			low++;
		while (list[low] < pivot); // left 다음 요소부터 증가하면서 pivot 값 이상인 요소 찾기
		do
			high--;
		while (list[high] > pivot); // right 부터 줄여가면서 pivot 값 이하인 요소 찾기
		if (low < high) SWAP(list[low], list[high], temp); // 두 요소 switch
	} while (low < high); // low, high가 교차할 때까지 반복
	SWAP(list[left], list[high], temp); // pivot을 중앙에 위치시킴, 파이널 위치로 이동
	return high; // pivot 위치 반환
}

void quick_sort1(int list[], int left, int right) {
	if (left < right) {
		int p = partition1(list, left, right); //partition1 호출해서 pivot 찾기
		quick_sort1(list, left, p - 1); // pivot 중심으로 pivot 바로 앞까지 재귀호출
		quick_sort1(list, p + 1, right); // pivot 중심으로 pivot 다음부터 끝까지 재귀호출
	}
}

int median(int left, int right) { // 첫번째 수, 마지막 수, 중간에 위치한 수 중 median 값을 구하는함수
	int median = left + (right - left) / 2;
	return median;
}

int partition2(int list[], int left, int right) { // median of three의 값이 pivot이 되도록 설정
	int mid = median(left, right);
	int pivot = list[mid]; // median of three의 값이 pivot이 되도록 설정
	printf("* pivot: %d\n", pivot); // pivot 값 출력
	left = mid; // left값은 mid값으로 설정
	int temp, low, high;
	low = left;
	high = right + 1;
	do {
		do
			low++;
		while (list[low] < pivot); // left 다음 요소부터 증가하면서 pivot 값 이상인 요소 찾기
		do
			high--;
		while (list[high] > pivot); // right부터 줄여가면서 pivot 값 이하인 요소 찾기
		if (low < high) SWAP(list[low], list[high], temp); // 두 요소 switch
	} while (low < high); // low, high가 교차할 때까지 반복
	SWAP(list[left], list[high], temp); // pivot을 중앙에 위치시킴
	return high; // pivot 위치 반환
}

void quick_sort2(int list[], int left, int right) {
	if (left < right) {
		int p = partition2(list, left, right); // partition2 호출해서 pivot 찾기
		quick_sort2(list, left, p - 1); // pivot 중심으로 pviot 바로 앞까지 재귀호출
		quick_sort2(list, p + 1, right); // pivot 중심으로 pivot 다음부터 끝까지 재귀호출
	}
}

int main(void) {
	int i, n;
	printf("Input size of list(1~50):");
	scanf("%d", &n); // 사용자로부터 1~50사이의 숫자를 입력받음
	int list[MAX_SIZE];
	printf("Input %d numbers in the list\n", n);
	for (i = 0;i < n;i++)
		scanf("%d", &list[i]); // 사용자로부터 리스트의 값을 입력받음
	printf("\n<<정렬 이전 상태>>\n");
	for (i = 0;i < n;i++)
		printf("%5d ", list[i]); // sort 전 list 출력
	printf("\n");
	printf("<Quick Sorting>\n");
	quick_sort1(list, 0, n - 1); // quick sort 1 실행
	printf("\n<Result>\n");
	for (i = 0;i < n;i++)
		printf("%d ", list[i]); // sort 후 list 출력
	printf("\n");

	printf("\n<Quick Sorting<Median of three>>\n");
	quick_sort2(list, 0, n - 1); // quick sort 2 실행
	printf("\n<Result>\n");
	for (i = 0;i < n;i++)
		printf("%d ", list[i]); // sort 후 list 출력
	printf("\n");
	return 0;
}