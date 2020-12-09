#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define KEY_SIZE 10 // 탐색키의 최대길이
#define TABLE_SIZE 13 // ht의 크기(prime number)
#define empty(item) (strlen(item.key)==0)
#define equal(item1, item2) (!strcmp(item1.key, item2.key))

/* quadratic probing */

typedef struct {
	char key[KEY_SIZE];
} element;

element hash_table[TABLE_SIZE];

void init_table(element ht[]) {
	int i;
	for (i = 0;i < TABLE_SIZE;i++)
		ht[i].key[0] = NULL;
}

int transform(char* key) { // 각 문자의 ASCII 코드 더해서 숫자로 변환
	int number = 0;
	while (*key)
		number = number + *key++;
	return number;
}

int hash_function(char* key) { // modulo 연산 사용한 hash function
	return transform(key) % TABLE_SIZE;
}

void hash_qp_add(element item, element ht[]) { // key를 hash table에 insert
	int i, hash_value, inc = 1;
	hash_value = i = hash_function(item.key); //hashing 결과 계산
	while (!empty(ht[i])) { // hashing table의 해당 위치에 data가 있으면
		if (equal(item, ht[i])) { // 같은 값이 이미 들어있으면
			fprintf(stderr, "search key duplication\n");
			exit(1);
		}
		i = (hash_value + inc * inc) % TABLE_SIZE; // 다음 위치 찾기(quadratic probing)
		inc++;
		if (i == hash_value) { // 처음 위치까지 다시 돌아왔으면
			fprintf(stderr, "table is full\n");
			exit(1);
		}
	}
	ht[i] = item; // 해당 위치가 비어있으면
}

void hash_qd_search(element item, element ht[]) {
	int i, hash_value, inc=1;
	hash_value = i = hash_function(item.key);
	while (!empty(ht[i])) {
		if (equal(item, ht[i])) {
			fprintf(stderr, "%s: location = %d\n", item.key, i);
			return;
		}
		i = (hash_value+inc*inc) % TABLE_SIZE;
		inc++;
		if (i == hash_value) {
			fprintf(stderr, "not in the table\n");
			return;
		}
	}
	fprintf(stderr, "not in the table\n");
}

void hash_qp_printf(element ht[]) {
	int i;
	printf("\n==============================\n");
	for (i = 0;i < TABLE_SIZE;i++)
		printf("[%d]     %s\n", i, ht[i].key);
	printf("==============================\n\n");
}

int main(void) {
	const char* s[7] = { "do", "for", "if", "case", "else", "return", "function" };
	element e;

	for (int i = 0;i < 7;i++) {
		strcpy(e.key, s[i]);
		puts(s[i]);
		hash_qp_add(e, hash_table);
		hash_qp_printf(hash_table);
	}
	for (int i = 0;i < 7;i++) {
		strcpy(e.key, s[i]);
		hash_qd_search(e, hash_table);
	}
	return 0;
}

