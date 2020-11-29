#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100

typedef struct Stack {
	char data[MAX]; // char로 데이터 담기
	int top; // top 값을 멤버로 포함시킴
}Stack;

void init_stack(Stack* s) { // stack 초기화 함수인데 구조체 포인터를 인자로 받음
	s->top = -1; // top이 -1로 초기화
}

void error(const char X[]) { // 에러 발생시 오류 메세지 출력
	fprintf(stderr, X);
}

bool is_full(Stack* s) { // stack이 full인지 아닌지 확인하는 함수
	return(s->top == (MAX - 1)); // top이 최대면 true 반환
}

bool is_empty(Stack* s) { // stack이 empty인지 아닌지 확인하는 함수
	return(s->top == -1); // top이 -1이면(스택 empty) true 반환
}

char pop(Stack* s) { // pop해주는 함수
	if (is_empty(s)) { // stack이 비어있는 경우
		error("Stack empty");
		exit(1);
	}
	else return s->data[(s->top)--]; //stack이 비어있지 않을 때는 top이 가리키는 원소값 반환 후 top 의 위치를 1 빼서 조정
}

void push(Stack* s, char item) {// push 해주는 함수
	if (is_full(s)) { // stack이 full일 경우
		error("Overflow");
		return;
	}
	else s->data[++(s->top)] = item; // stack이 꽉 차있지 않을 경우 top을 1 증가시킨 다음에 해당 위치에 원소값 저장함
}

void d_array(char str[]) {// 배열을 이용하여 입력된 문자열이 대칭을 이루는지 체크하는 함수
	int length = strlen(str); // 문자열의 길이를 담음
	int pnum2 = 0; // 대칭인지 아닌지 구분하기 위한 변수 사용
	for (int i = 0;i < length / 2;i++) {// 좌우대칭문자가 맞는지 하나씩 확인
		if (str[i] != str[length - 1 - i]) { // 값을 비교하는데 다른 경우에
			pnum2 = 1; // pnum을 1로 바꿔줌
			break;			// 아닌경우가 생기면, 바로 프로그램 종료
		}
		else
			continue; // 좌우대칭문자가 맞으면, 계속 반복확인
	}
	if (pnum2 == 1) // pnum이 1일 경우에는 비대칭
		printf("비대칭<배열>\n");
	else if (pnum2 == 0) // pnum이 0일 경우는 대칭
		printf("대칭<배열>\n");
}

void d_stack(char str[]) { // 스택을 이용하여 입력된 문자열이 대칭인지 아닌지 체크하는 함수
	Stack s; // 스택 생성
	int i = 0;
	int length = strlen(str); // length에 문자열에 길이를 담음
	init_stack(&s); // 스택 초기화
	for (i = 0;i < length;i++) { // 문자열의 길이만큼 전체를 stack에 push해줌
		push(&s, str[i]);
	}
	int pnum1 = 0; // 대칭인지 아닌지 구분하기 위한 변수 사용
	for (i = 0;i < length / 2;i++) { // 좌우 대칭 문자인지 하나씩 확인하는데 반만 반복하면 됨
		if (str[i] != pop(&s)) { // 스택에서 pop한 값과 str[i]번째의 값이 같지 않다면
			pnum1 = 1; // 비대칭이므로 pnum을 1로 바꿔주고 반복문 종료
			break;
		}
	}
	if (pnum1 == 1) // pnum1이 1일 경우에는 비대칭
		printf("비대칭<스택>\n");
	else if (pnum1 == 0) // pnum1이 0일 경우에는 대칭
		printf("대칭<스택>\n");
}

int main(void) {
	char str[MAX];
	while (true) { //while문을 이용하여 반복
		printf("알파벳으로 구성된 문자열 입력\n");
		scanf("%s", str); // 사용자로부터 문자열 입력받음
		if (strcmp(str, "0") == 0) // 문자열에 0입력 받은 경우 반복문 종료
			break;
		d_array(str); // 배열 이용하여 대칭 확인하는 함수 호출
		d_stack(str); // 스택 이용하여 대칭 확인하는 함수 호출
		printf("\n");
	}
	return 0;
}