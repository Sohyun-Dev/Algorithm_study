#include <stdio.h>
#include <stdlib.h>

#define SIZE 10
#define TABLE_SIZE 11 // hash table ũ�� 11

/*chaining*/

typedef struct { // element ����
	int key;
} element;

struct list {
	element item;
	struct list* link;
};

struct list* hash_table[TABLE_SIZE]; // hash table ����

int hash_function(int key) { // modulo ���� ����� hash function
	return key % TABLE_SIZE;
}

void hash_chain_add(element item, struct list* ht[]) { // key�� hash table�� insert�ϴ� �Լ� ����
	int hash_value = hash_function(item.key); // �ؽ��Լ��� �־� ���ϵ� ���� ������ ����
	struct list* ptr; // ���� ����� ��� ����
	struct list* node_before = NULL, * node = ht[hash_value]; // ������ ���� �� �տ� ��� ����
	for (;node;node_before = node, node = node->link) { // �ش� ��ġ�� ��� �˻�
		if (node->item.key == item.key) { // ���� ���� ����ִٸ�
			fprintf(stderr, "%d is already stored\n", item.key);
			return;
		}
	}
	ptr = (struct list*)malloc(sizeof(struct list)); // �ش� key���� ����Ǿ� ���� ������
	ptr->item = item; // ���ο� ��忡 key ����
	ptr->link = NULL; // ���ο� ��忡 link ����
	if (node_before)
		node_before->link = ptr; // ������ ��ġ�� �߰�
	else
		ht[hash_value] = ptr; // �ش� ��ġ�� ��尡 �����Ƿ� ù ���� ������
}

void hash_chain_delete(element item, struct list* ht[]) { // key�� hash table���� delete�ϴ� �Լ� ����
	int hash_value = hash_function(item.key);  // �ؽ��Լ��� �־� ���ϵ� ���� ������ ����
	struct list* delNode = NULL; // ������ ��� ����
	if (ht[hash_value]->item.key == item.key) { // ���� ���� ��� �ִٸ�
		delNode = ht[hash_value]; // delNode�� ht[hash_value]�� ����
		ht[hash_value] = ht[hash_value]->link; // ht[hash_value]�� ht[hash_value]�� link�� ����
	}
	else {
		struct list* node = ht[hash_value];
		struct list* next = node->link;
		while (next) { // ���� Ž�� ����
			if (next->item.key == item.key) { // ���� ���� ��� �ִٸ�
				node->link = next->link; // node�� link�� next�� link�� ����
				delNode = next; // delNode�� next�� ���� 
				break;
			}
			node = next; // node�� next�� ����
			next = node->link; // next�� node�� link�� ����
		}
	}
	free(delNode); // free���ֱ�
}

void hash_chain_search(element item, struct list* ht[]) { // hash table�� ���� ���� �ִ��� ã�� �Լ�
	struct list* node;
	int hash_value = hash_function(item.key); // �ؽ��Լ��� �־� ���ϵ� ���� ������ ����
	for (node = ht[hash_value];node;node = node->link) { // �ش� ��ġ�� ��� �˻�
		if (node->item.key == item.key) { // ���� ���� ���������
			fprintf(stderr, "%d is found at index %d\n", item.key, hash_value); // �˻� ����
			return;
		}
	}
	fprintf(stderr, "%d is not in the table\n", item.key); // �׷��� ���� ��� �˻� ����
}

void hash_chain_print(struct list* ht[]) { // hash table ����ϴ� �Լ�
	struct list* node;
	int i;
	printf("\n==============================\n");
	for (i = 0;i < TABLE_SIZE;i++) {
		printf("[%d]", i);
		for (node = ht[i];node;node = node->link) // node�� link�� �̵��ذ��� ���
			printf(" -%3d", node->item.key);
		printf("\n");
	}
	printf("==============================\n\n");
}

int main(void) {
	int data[SIZE]; // ����ڷκ��� ���� �Է¹޾� ����� �迭 ����
	element e;
	printf("Input 10 keys to add\n");
	for (int i = 0;i < SIZE;i++) // ����ڷκ��� ���� 10���� �Է� ����
		scanf("%d", &data[i]);
	for (int i = 0;i < SIZE;i++) { // �Է¹��� �������� hash table�� �߰���
		e.key = data[i];
		hash_chain_add(e, hash_table);
	}
	hash_chain_print(hash_table); // �ؽ����̺��� ���
	while (true) { // ����ڷκ��� 5�� �Է¹ޱ� ������ �ݺ�
		int num;
		printf("\nChoose operation (1.insert 2.delete 3.search 4.print 5.exit):");
		scanf("%d", &num); // ����ڷκ��� ���ڸ� �Է¹���
		if (num == 1) { // �Է� ���� ���� 1�̶�� insert
			int input;
			element e;
			printf("input data to add:");
			scanf("%d", &input);//insert�� ���ڸ� ����ڷκ��� �Է¹���
			e.key = input;
			hash_chain_add(e, hash_table); // �ؽ����̺� �Է¹��� ���� insert
		}
		else if (num == 2) { // �Է� ���� ���� 2��� delete
			int input;
			element e;
			printf("inpudt data to delete:");
			scanf("%d", &input); // delete�� ���ڸ� ����ڷκ��� �Է¹���
			e.key = input;
			hash_chain_delete(e, hash_table); // �ؽ����̺��� �Է¹��� ���� delete
		}
		else if (num == 3) { // �Է� ���� ���� 3 �̶�� search
			int input;
			element e;
			printf("input data to search:");
			scanf("%d", &input); //search�� ���ڸ� ����ڷκ��� �Է¹���
			e.key = input;
			hash_chain_search(e, hash_table); // �ؽ����̺��� �Է¹��� ���� search
		}
		else if (num == 4) { // �Է� ���� ���� 4���
			hash_chain_print(hash_table); // �ؽ����̺� ���
		}
		else if (num == 5) { // �Է� ���� ���� 5���
			printf("Program finished\n");
			exit(1); // ���α׷� ����
		}
		else { // �Է� ���� ���� 1,2,3,4,5 ���� �ٸ� ���ڶ�� 
			printf("Wrong Input\n"); // �߸��� �Է�
		}
	}
}