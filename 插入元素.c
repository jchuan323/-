#include <stdio.h>
#include <stdlib.h>

// 定义链表节点结构
struct Node {
    int data;
    struct Node* next;
};

// 创建一个新节点
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// 在链表的头部插入元素
void insertAtHead(struct Node** head, int data) {
    struct Node* newNode = createNode(data);
    newNode->next = *head;
    *head = newNode;
}

// 在链表的任意位置插入元素
void insertAtPosition(struct Node** head, int data, int position) {
    struct Node* newNode = createNode(data);

    // 如果是在头部插入
    if (position == 0) {
        insertAtHead(head, data);
        return;
    }

    struct Node* temp = *head;
    // 找到要插入位置的前一个节点
    for (int i = 0; temp != NULL && i < position - 1; i++) {
        temp = temp->next;
    }

    // 插入节点
    if (temp != NULL) {
        newNode->next = temp->next;
        temp->next = newNode;
    } else {
        printf("位置超出链表范围\n");
    }
}

// 打印链表
void printList(struct Node* head) {
    struct Node* temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

int main() {
    struct Node* head = NULL;

    // 向链表中插入元素
    insertAtHead(&head, 3);
    insertAtHead(&head, 2);
    insertAtHead(&head, 1);

    printf("初始链表: ");
    printList(head);

    insertAtPosition(&head, 4, 2);
    printf("在位置 2 插入 4 后的链表: ");
    printList(head);

    return 0;
}

