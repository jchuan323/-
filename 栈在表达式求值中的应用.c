#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX 100

// 定义栈结构
typedef struct {
    int data[MAX];
    int top;
} Stack;

// 初始化栈
void initStack(Stack* stack) {
    stack->top = -1;
}

// 判断栈是否为空
int isEmpty(Stack* stack) {
    return stack->top == -1;
}

// 判断栈是否满
int isFull(Stack* stack) {
    return stack->top == MAX - 1;
}

// 入栈操作
void push(Stack* stack, int value) {
    if (!isFull(stack)) {
        stack->data[++(stack->top)] = value;
    } else {
        printf("栈满，无法入栈！\n");
    }
}

// 出栈操作
int pop(Stack* stack) {
    if (!isEmpty(stack)) {
        return stack->data[(stack->top)--];
    } else {
        printf("栈为空，无法出栈！\n");
        return -1;
    }
}

// 检查是否是操作符
int isOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

// 执行操作符对应的计算
int performOperation(char operator, int operand1, int operand2) {
    switch (operator) {
        case '+': return operand1 + operand2;
        case '-': return operand1 - operand2;
        case '*': return operand1 * operand2;
        case '/': return operand1 / operand2;
        default: return 0;
    }
}

// 计算后缀表达式的函数
int evaluatePostfix(char* expression) {
    Stack stack;
    initStack(&stack);

    for (int i = 0; expression[i] != '\0'; i++) {
        char ch = expression[i];

        // 如果是操作数，将其转换为整数并入栈
        if (isdigit(ch)) {
            push(&stack, ch - '0');
        }
        // 如果是操作符，从栈中弹出两个操作数进行计算，并将结果入栈
        else if (isOperator(ch)) {
            int operand2 = pop(&stack);
            int operand1 = pop(&stack);
            int result = performOperation(ch, operand1, operand2);
            push(&stack, result);
        }
    }

    // 最后栈中只剩下最终结果
    return pop(&stack);
}

int main() {
    char expression[MAX];

    printf("请输入后缀表达式（例如23*54*+）：");
    scanf("%s", expression);

    int result = evaluatePostfix(expression);
    printf("计算结果: %d\n", result);

    return 0;
}

