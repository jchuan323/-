#include <stdio.h>
#include <stdlib.h>

// ��������ڵ�ṹ
struct Node {
    int data;
    struct Node* next;
};

// β�巨��������
struct Node* createLinkedList() {
    struct Node* head = NULL;  // ��ʼ��ͷָ��Ϊ��
    struct Node* tail = NULL;  // ��ʼ��βָ��Ϊ��
    int data;

    printf("������ڵ�����ݣ���-1������\n");
    scanf("%d", &data);

    while (data != -1) {  // ֱ������-1Ϊֹ
        // �����½ڵ�
        struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode->data = data;
        newNode->next = NULL;

        if (head == NULL) {  // �������Ϊ�գ�ͷβ��ָ���½ڵ�
            head = newNode;
            tail = newNode;
        } else {  // �����½ڵ����ӵ�β�ڵ���棬������β�ڵ�
            tail->next = newNode;
            tail = newNode;
        }

        scanf("%d", &data);  // ������������
    }

    return head;  // ���������ͷָ��
}

// ��ӡ����
void printLinkedList(struct Node* head) {
    struct Node* temp = head;
    printf("����Ԫ��Ϊ��");
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    struct Node* head = createLinkedList();  // ��������
    printLinkedList(head);                   // ��ӡ����
    return 0;
}

