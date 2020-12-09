#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define KEY_SIZE 10 // Ž��Ű�� �ִ����
#define TABLE_SIZE 13 // ht�� ũ��(prime number)
#define empty(item) (strlen(item.key)==0)
#define equal(item1, item2) (!strcmp(item1.key, item2.key))

/* linear probing */

typedef struct {
	char key[KEY_SIZE];
} element;

element hash_table[TABLE_SIZE];

void init_table(element ht[]) {
	int i;
	for (i = 0;i < TABLE_SIZE;i++)
		ht[i].key[0] = NULL;
}

int transform(char* key) { // �� ������ ASCII �ڵ� ���ؼ� ���ڷ� ��ȯ
	int number = 0;
	while (*key)
		number = number + *key++;
	return number;
}

int hash_function(char* key) { // modulo ���� ����� hash function
	return transform(key) % TABLE_SIZE;
}

void hash_lp_add(element item, element ht[]) { // key�� hash table�� insert
	int i, hash_value;
	hash_value = i = hash_function(item.key); // hash �� ���
	while (!empty(ht[i])) { // hash table�� �ش� ��ġ�� ���� ���������
		if (equal(item, ht[i])) { // ������ Ű���� �̹� ���������
			fprintf(stderr, "search key duplication\n");
			exit(1);
		}
		i = (i + 1) % TABLE_SIZE; // ���� ��ġ ã��
		if (i == hash_value) { // ó�� ��ġ�� ���ƿ�����
			fprintf(stderr, "table is full\n");
			exit(1);
		}
	}
	ht[i] = item; // �ش� ��ġ�� ��� ������ insert
}

void hash_lp_search(element item, element ht[]) {
	int i, hash_value;
	hash_value = i = hash_function(item.key);
	while (!empty(ht[i])) {
		if (equal(item, ht[i])) {
			fprintf(stderr, "%s: location = %d\n", item.key, i);
			return;
		}
		i = (i + 1) % TABLE_SIZE;
		if (i == hash_value) {
			fprintf(stderr, "not in the table\n");
			return;
		}
	}
	fprintf(stderr, "not in the table\n");
}

void hash_lp_printf(element ht[]) {
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
		hash_lp_add(e, hash_table);
		hash_lp_printf(hash_table);
	}
	return 0;
}

