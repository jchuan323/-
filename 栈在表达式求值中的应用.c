#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX 100

// ����ջ�ṹ
typedef struct {
    int data[MAX];
    int top;
} Stack;

// ��ʼ��ջ
void initStack(Stack* stack) {
    stack->top = -1;
}

// �ж�ջ�Ƿ�Ϊ��
int isEmpty(Stack* stack) {
    return stack->top == -1;
}

// �ж�ջ�Ƿ���
int isFull(Stack* stack) {
    return stack->top == MAX - 1;
}

// ��ջ����
void push(Stack* stack, int value) {
    if (!isFull(stack)) {
        stack->data[++(stack->top)] = value;
    } else {
        printf("ջ�����޷���ջ��\n");
    }
}

// ��ջ����
int pop(Stack* stack) {
    if (!isEmpty(stack)) {
        return stack->data[(stack->top)--];
    } else {
        printf("ջΪ�գ��޷���ջ��\n");
        return -1;
    }
}

// ����Ƿ��ǲ�����
int isOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

// ִ�в�������Ӧ�ļ���
int performOperation(char operator, int operand1, int operand2) {
    switch (operator) {
        case '+': return operand1 + operand2;
        case '-': return operand1 - operand2;
        case '*': return operand1 * operand2;
        case '/': return operand1 / operand2;
        default: return 0;
    }
}

// �����׺���ʽ�ĺ���
int evaluatePostfix(char* expression) {
    Stack stack;
    initStack(&stack);

    for (int i = 0; expression[i] != '\0'; i++) {
        char ch = expression[i];

        // ����ǲ�����������ת��Ϊ��������ջ
        if (isdigit(ch)) {
            push(&stack, ch - '0');
        }
        // ����ǲ���������ջ�е����������������м��㣬���������ջ
        else if (isOperator(ch)) {
            int operand2 = pop(&stack);
            int operand1 = pop(&stack);
            int result = performOperation(ch, operand1, operand2);
            push(&stack, result);
        }
    }

    // ���ջ��ֻʣ�����ս��
    return pop(&stack);
}

int main() {
    char expression[MAX];

    printf("�������׺���ʽ������23*54*+����");
    scanf("%s", expression);

    int result = evaluatePostfix(expression);
    printf("������: %d\n", result);

    return 0;
}

