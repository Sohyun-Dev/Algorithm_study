#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct ListNode { // �ܼ����Ḯ��Ʈ ������ ���� ��� 
    int data;
    struct ListNode* link;
}ListNode;

ListNode* insert_sort(ListNode* head, int num) { // ������������ �����Ǹ鼭 ���ԵǴ� �Լ�
    ListNode* p = (ListNode*)malloc(sizeof(ListNode));
    p->data = num; // p�� data�� �Է¹��� num ���� ����
    p->link = NULL;
    ListNode* pos = head; // ���ο� ListNode ����
    if (head == NULL) {// head�� NULL�� ��쿡�� head�� p�� ��(���� ���)
        head = p;
    }
    else if (p->data <= head->data) { // p�� data�� head�� data���� �۰ų� ���� ���
        p->link = head; // p�� link�� head�� ���� 
        head = p; // head�� p�� ��
    }
    else {// p�� data�� head�� data���� Ŭ ���
        while (true) {// while���� �̿��Ͽ� �ݺ�
            if (pos->link == NULL) { // pos�� link�� ����� ���� 
                pos->link = p; // pos�� link�� p�� �ǰ� �ݺ��� ����
                break;
            }
            else if (p->data <= pos->link->data) { // p�� data�� pos�� link�� data���� �۰ų� ���� ��
                p->link = pos->link; // p�� link���� pos�� link�� ��
                pos->link = p; // pos�� link���� p�� ��
                break;
            } // �ݺ��� ����
            pos = pos->link; // pos�� ���� ���� �̵�
        }
    }
    return head;// head�� ����
}

void display(ListNode* head) { // head���� ��ũ�� ����� ����� data�� ��� ����ϴ� �Լ�
    for (ListNode* p = head;p != NULL;p = p->link)
        printf("%3d -> ", p->data);
    printf("NULL\n");
}

int main() {
    int item;
    ListNode* head = NULL; // ��� ����
    printf("Input data to insert to linkedlist<0 to quit>\n");
    while (true) {// while���� �̿��Ͽ� �ݺ�
        scanf("%d", &item); //����ڷκ��� ������ �Է¹���
        if (item == 0) // 0�� �Է¹��� �� �ݺ��� ����
            break;
        head = insert_sort(head, item); // ������������ ������ �� ���� ���� ListNode�� head�� ���
        display(head); // ���
    }
    display(head); // ���������� �ѹ� �� ���
    printf("Program finished.\n");
}
