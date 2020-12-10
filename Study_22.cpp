#include <stdio.h>
#include <stdlib.h>

#define SIZE 10
#define TABLE_SIZE 11 // hash table 크기 11

/*chaining*/

typedef struct { // element 정의
	int key;
} element;

struct list {
	element item;
	struct list* link;
};

struct list* hash_table[TABLE_SIZE]; // hash table 생성

int hash_function(int key) { // modulo 연산 사용한 hash function
	return key % TABLE_SIZE;
}

void hash_chain_add(element item, struct list* ht[]) { // key를 hash table에 insert하는 함수 정의
	int hash_value = hash_function(item.key); // 해시함수에 넣어 리턴된 값을 변수에 담음
	struct list* ptr; // 새로 만드는 노드 생성
	struct list* node_before = NULL, * node = ht[hash_value]; // 마지막 노드와 그 앞에 노드 생성
	for (;node;node_before = node, node = node->link) { // 해당 위치의 노드 검색
		if (node->item.key == item.key) { // 같은 값이 들어있다면
			fprintf(stderr, "%d is already stored\n", item.key);
			return;
		}
	}
	ptr = (struct list*)malloc(sizeof(struct list)); // 해당 key값이 저장되어 있지 않으면
	ptr->item = item; // 새로운 노드에 key 설정
	ptr->link = NULL; // 새로운 노드에 link 설정
	if (node_before)
		node_before->link = ptr; // 마지막 위치에 추가
	else
		ht[hash_value] = ptr; // 해당 위치에 노드가 없으므로 첫 노드로 연결함
}

void hash_chain_delete(element item, struct list* ht[]) { // key를 hash table에서 delete하는 함수 정의
	int hash_value = hash_function(item.key);  // 해시함수에 넣어 리턴된 값을 변수에 담음
	struct list* delNode = NULL; // 삭제할 노드 생성
	if (ht[hash_value]->item.key == item.key) { // 같은 값이 들어 있다면
		delNode = ht[hash_value]; // delNode를 ht[hash_value]로 설정
		ht[hash_value] = ht[hash_value]->link; // ht[hash_value]를 ht[hash_value]의 link로 설정
	}
	else {
		struct list* node = ht[hash_value];
		struct list* next = node->link;
		while (next) { // 선형 탐색 시작
			if (next->item.key == item.key) { // 같은 값이 들어 있다면
				node->link = next->link; // node의 link를 next의 link로 설정
				delNode = next; // delNode를 next로 설정 
				break;
			}
			node = next; // node를 next로 설정
			next = node->link; // next를 node의 link로 설정
		}
	}
	free(delNode); // free해주기
}

void hash_chain_search(element item, struct list* ht[]) { // hash table에 같은 값이 있는지 찾는 함수
	struct list* node;
	int hash_value = hash_function(item.key); // 해시함수에 넣어 리턴된 값을 변수에 담음
	for (node = ht[hash_value];node;node = node->link) { // 해당 위치의 노드 검색
		if (node->item.key == item.key) { // 같은 값이 들어있으면
			fprintf(stderr, "%d is found at index %d\n", item.key, hash_value); // 검색 성공
			return;
		}
	}
	fprintf(stderr, "%d is not in the table\n", item.key); // 그렇지 않을 경우 검색 실패
}

void hash_chain_print(struct list* ht[]) { // hash table 출력하는 함수
	struct list* node;
	int i;
	printf("\n==============================\n");
	for (i = 0;i < TABLE_SIZE;i++) {
		printf("[%d]", i);
		for (node = ht[i];node;node = node->link) // node의 link를 이동해가며 출력
			printf(" -%3d", node->item.key);
		printf("\n");
	}
	printf("==============================\n\n");
}

int main(void) {
	int data[SIZE]; // 사용자로부터 정수 입력받아 담아줄 배열 생성
	element e;
	printf("Input 10 keys to add\n");
	for (int i = 0;i < SIZE;i++) // 사용자로부터 정수 10개를 입력 받음
		scanf("%d", &data[i]);
	for (int i = 0;i < SIZE;i++) { // 입력받은 정수들을 hash table에 추가함
		e.key = data[i];
		hash_chain_add(e, hash_table);
	}
	hash_chain_print(hash_table); // 해시테이블을 출력
	while (true) { // 사용자로부터 5를 입력받기 전까지 반복
		int num;
		printf("\nChoose operation (1.insert 2.delete 3.search 4.print 5.exit):");
		scanf("%d", &num); // 사용자로부터 숫자를 입력받음
		if (num == 1) { // 입력 받은 수가 1이라면 insert
			int input;
			element e;
			printf("input data to add:");
			scanf("%d", &input);//insert할 숫자를 사용자로부터 입력받음
			e.key = input;
			hash_chain_add(e, hash_table); // 해시테이블에 입력받은 숫자 insert
		}
		else if (num == 2) { // 입력 받은 수가 2라면 delete
			int input;
			element e;
			printf("inpudt data to delete:");
			scanf("%d", &input); // delete할 숫자를 사용자로부터 입력받음
			e.key = input;
			hash_chain_delete(e, hash_table); // 해시테이블에서 입력받은 숫자 delete
		}
		else if (num == 3) { // 입력 받은 수가 3 이라면 search
			int input;
			element e;
			printf("input data to search:");
			scanf("%d", &input); //search할 숫자를 사용자로부터 입력받음
			e.key = input;
			hash_chain_search(e, hash_table); // 해시테이블에서 입력받은 숫자 search
		}
		else if (num == 4) { // 입력 받은 수가 4라면
			hash_chain_print(hash_table); // 해시테이블 출력
		}
		else if (num == 5) { // 입력 받은 수가 5라면
			printf("Program finished\n");
			exit(1); // 프로그램 종료
		}
		else { // 입력 받은 수가 1,2,3,4,5 외의 다른 숫자라면 
			printf("Wrong Input\n"); // 잘못된 입력
		}
	}
}