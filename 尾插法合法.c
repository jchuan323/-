#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    struct Node *next;
    int data;
} Node;

// 创建链表函数
Node* createlist() {
    Node *head = NULL;
    Node *tail = NULL;
    int data;
    printf("请输入您要插入的数据 (-1 结束输入):\n");
    scanf("%d", &data);

    while (data != -1) {
        // 创建新节点并分配内存
        Node *newnode = (Node*)malloc(sizeof(Node));
        if (newnode == NULL) {
            printf("内存分配失败！\n");
            exit(1); // 退出程序
        }

        newnode->data = data;
        newnode->next = NULL;

        if (head == NULL) {
            // 如果是第一个节点
            head = newnode;
            tail = newnode;
        } else {
            // 否则添加到链表的末尾
            tail->next = newnode;
            tail = newnode;
        }

        scanf("%d", &data); // 读取下一个数据
    }

    return head; // 返回链表头指针
}

// 打印链表函数
void printlist(Node *head) {
    Node *current = head;

    if (current == NULL) {
        printf("链表为空\n");
        return;
    }

    // 遍历链表并打印数据
    while (current != NULL) {
        printf("%d", current->data);
        if (current->next != NULL) {
            printf("->"); // 打印箭头
        }
        current = current->next;
    }
    printf("\n");
}

// 释放链表内存
void freelist(Node *head) {
    Node *current = head;
    Node *nextNode;
    while (current != NULL) {
        nextNode = current->next;
        free(current); // 释放当前节点
        current = nextNode;
    }
}

int main() {
    Node *head = createlist();
    printlist(head);
    freelist(head); // 释放链表内存
    return 0;
}






