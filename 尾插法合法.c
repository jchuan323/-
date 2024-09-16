#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    struct Node *next;
    int data;
} Node;

// ����������
Node* createlist() {
    Node *head = NULL;
    Node *tail = NULL;
    int data;
    printf("��������Ҫ��������� (-1 ��������):\n");
    scanf("%d", &data);

    while (data != -1) {
        // �����½ڵ㲢�����ڴ�
        Node *newnode = (Node*)malloc(sizeof(Node));
        if (newnode == NULL) {
            printf("�ڴ����ʧ�ܣ�\n");
            exit(1); // �˳�����
        }

        newnode->data = data;
        newnode->next = NULL;

        if (head == NULL) {
            // ����ǵ�һ���ڵ�
            head = newnode;
            tail = newnode;
        } else {
            // ������ӵ������ĩβ
            tail->next = newnode;
            tail = newnode;
        }

        scanf("%d", &data); // ��ȡ��һ������
    }

    return head; // ��������ͷָ��
}

// ��ӡ������
void printlist(Node *head) {
    Node *current = head;

    if (current == NULL) {
        printf("����Ϊ��\n");
        return;
    }

    // ����������ӡ����
    while (current != NULL) {
        printf("%d", current->data);
        if (current->next != NULL) {
            printf("->"); // ��ӡ��ͷ
        }
        current = current->next;
    }
    printf("\n");
}

// �ͷ������ڴ�
void freelist(Node *head) {
    Node *current = head;
    Node *nextNode;
    while (current != NULL) {
        nextNode = current->next;
        free(current); // �ͷŵ�ǰ�ڵ�
        current = nextNode;
    }
}

int main() {
    Node *head = createlist();
    printlist(head);
    freelist(head); // �ͷ������ڴ�
    return 0;
}






