#include <stdio.h>
#include <stdlib.h>

// 定义链表节点结构
struct Node {
    int data;
    struct Node* next;
};

// 尾插法创建链表
struct Node* createLinkedList() {
    struct Node* head = NULL;  // 初始化头指针为空
    struct Node* tail = NULL;  // 初始化尾指针为空
    int data;

    printf("请输入节点的数据，以-1结束：\n");
    scanf("%d", &data);

    while (data != -1) {  // 直到输入-1为止
        // 创建新节点
        struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode->data = data;
        newNode->next = NULL;

        if (head == NULL) {  // 如果链表为空，头尾都指向新节点
            head = newNode;
            tail = newNode;
        } else {  // 否则将新节点连接到尾节点后面，并更新尾节点
            tail->next = newNode;
            tail = newNode;
        }

        scanf("%d", &data);  // 继续输入数据
    }

    return head;  // 返回链表的头指针
}

// 打印链表
void printLinkedList(struct Node* head) {
    struct Node* temp = head;
    printf("链表元素为：");
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    struct Node* head = createLinkedList();  // 创建链表
    printLinkedList(head);                   // 打印链表
    return 0;
}

