#include <stdio.h>
#include <stdlib.h>

#define MAX 5 // ����ջ���������

int stack[MAX];  // ����һ��ջ
int top = -1;    // ջ��ָ�룬��ʼֵΪ-1����ʾջΪ��

// ���ջ�Ƿ�Ϊ��
int isEmpty() {
    return top == -1;
}

// ���ջ�Ƿ���
int isFull() {
    return top == MAX - 1;
}

// ��ջ����
void push(int value) {
    if (isFull()) {
        printf("ջ�����޷���ջ\n");
    } else {
        top++;          // ջ��ָ�������ƶ�
        stack[top] = value;  // ��ֵѹ��ջ��
        printf("Ԫ�� %d ��ջ\n", value);
    }
}

// ��ջ����
int pop() {
    if (isEmpty()) {
        printf("ջ�գ��޷���ջ\n");
        return -1; // ����һ����Чֵ
    } else {
        int value = stack[top]; // ��ȡջ��Ԫ��
        top--;                  // ջ��ָ�������ƶ�
        printf("Ԫ�� %d ��ջ\n", value);
        return value;           // ����ջ��Ԫ��
    }
}

// �鿴ջ��Ԫ��
int peek() {
    if (isEmpty()) {
        printf("ջ�գ���ջ��Ԫ��\n");
        return -1; // ����һ����Чֵ
    } else {
        return stack[top];
    }
}

// ��ӡջ�е�Ԫ��
void printStack() {
    if (isEmpty()) {
        printf("ջ�գ��޷���ʾ\n");
    } else {
        printf("ջ�е�Ԫ��: ");
        for (int i = 0; i <= top; i++) {
            printf("%d ", stack[i]);
        }
        printf("\n");
    }
}

// ������
int main() {
    int choice, value;
    
    while (1) {
        printf("\n--- ջ���� ---\n");
        printf("1. ��ջ\n");
        printf("2. ��ջ\n");
        printf("3. �鿴ջ��Ԫ��\n");
        printf("4. ��ʾջ\n");
        printf("5. �˳�\n");
        printf("���������ѡ��: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("����Ҫ��ջ��Ԫ��: ");
                scanf("%d", &value);
                push(value);
                break;
            case 2:
                pop();
                break;
            case 3:
                value = peek();
                if (value != -1)
                    printf("ջ��Ԫ��Ϊ: %d\n", value);
                break;
            case 4:
                printStack();
                break;
            case 5:
                exit(0);
            default:
                printf("��Чѡ������������\n");
        }
    }
    
    return 0;
}

