#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct ListNode { // 단순연결리스트 구현을 위한 노드 
    int data;
    struct ListNode* link;
}ListNode;

ListNode* insert_sort(ListNode* head, int num) { // 오름차순으로 유지되면서 삽입되는 함수
    ListNode* p = (ListNode*)malloc(sizeof(ListNode));
    p->data = num; // p의 data에 입력받은 num 값을 저장
    p->link = NULL;
    ListNode* pos = head; // 새로운 ListNode 생성
    if (head == NULL) {// head가 NULL일 경우에는 head가 p가 됨(유일 노드)
        head = p;
    }
    else if (p->data <= head->data) { // p의 data가 head의 data보다 작거나 같은 경우
        p->link = head; // p의 link에 head가 들어가고 
        head = p; // head는 p가 됨
    }
    else {// p의 data가 head의 data보다 클 경우
        while (true) {// while문을 이용하여 반복
            if (pos->link == NULL) { // pos의 link가 비었을 때는 
                pos->link = p; // pos의 link가 p가 되고 반복문 종료
                break;
            }
            else if (p->data <= pos->link->data) { // p의 data가 pos의 link의 data보다 작거나 같을 때
                p->link = pos->link; // p의 link에는 pos의 link가 들어감
                pos->link = p; // pos의 link에는 p가 들어감
                break;
            } // 반복문 종료
            pos = pos->link; // pos는 다음 노드로 이동
        }
    }
    return head;// head를 리턴
}

void display(ListNode* head) { // head부터 링크로 연결된 노드의 data를 계속 출력하는 함수
    for (ListNode* p = head;p != NULL;p = p->link)
        printf("%3d -> ", p->data);
    printf("NULL\n");
}

int main() {
    int item;
    ListNode* head = NULL; // 노드 생성
    printf("Input data to insert to linkedlist<0 to quit>\n");
    while (true) {// while문을 이용하여 반복
        scanf("%d", &item); //사용자로부터 정수를 입력받음
        if (item == 0) // 0을 입력받을 시 반복문 종료
            break;
        head = insert_sort(head, item); // 오름차순으로 삽입한 뒤 리턴 받은 ListNode를 head에 담고
        display(head); // 출력
    }
    display(head); // 마지막으로 한번 더 출력
    printf("Program finished.\n");
}
