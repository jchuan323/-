#include <stdio.h>
#include <stdlib.h>

// ��������ڵ�ṹ
struct Node {
    int data;
    struct Node* next;
};

// ����һ���½ڵ�
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// �������ͷ������Ԫ��
void insertAtHead(struct Node** head, int data) {
    struct Node* newNode = createNode(data);
    newNode->next = *head;
    *head = newNode;
}

// �����������λ�ò���Ԫ��
void insertAtPosition(struct Node** head, int data, int position) {
    struct Node* newNode = createNode(data);

    // �������ͷ������
    if (position == 0) {
        insertAtHead(head, data);
        return;
    }

    struct Node* temp = *head;
    // �ҵ�Ҫ����λ�õ�ǰһ���ڵ�
    for (int i = 0; temp != NULL && i < position - 1; i++) {
        temp = temp->next;
    }

    // ����ڵ�
    if (temp != NULL) {
        newNode->next = temp->next;
        temp->next = newNode;
    } else {
        printf("λ�ó�������Χ\n");
    }
}

// ��ӡ����
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

    // �������в���Ԫ��
    insertAtHead(&head, 3);
    insertAtHead(&head, 2);
    insertAtHead(&head, 1);

    printf("��ʼ����: ");
    printList(head);

    insertAtPosition(&head, 4, 2);
    printf("��λ�� 2 ���� 4 �������: ");
    printList(head);

    return 0;
}

