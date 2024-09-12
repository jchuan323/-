#include <stdio.h>
#include <stdlib.h>

#define MAX 5 // 定义栈的最大容量

int stack[MAX];  // 定义一个栈
int top = -1;    // 栈顶指针，初始值为-1，表示栈为空

// 检查栈是否为空
int isEmpty() {
    return top == -1;
}

// 检查栈是否满
int isFull() {
    return top == MAX - 1;
}

// 入栈操作
void push(int value) {
    if (isFull()) {
        printf("栈满，无法入栈\n");
    } else {
        top++;          // 栈顶指针向上移动
        stack[top] = value;  // 将值压入栈中
        printf("元素 %d 入栈\n", value);
    }
}

// 出栈操作
int pop() {
    if (isEmpty()) {
        printf("栈空，无法出栈\n");
        return -1; // 返回一个无效值
    } else {
        int value = stack[top]; // 获取栈顶元素
        top--;                  // 栈顶指针向下移动
        printf("元素 %d 出栈\n", value);
        return value;           // 返回栈顶元素
    }
}

// 查看栈顶元素
int peek() {
    if (isEmpty()) {
        printf("栈空，无栈顶元素\n");
        return -1; // 返回一个无效值
    } else {
        return stack[top];
    }
}

// 打印栈中的元素
void printStack() {
    if (isEmpty()) {
        printf("栈空，无法显示\n");
    } else {
        printf("栈中的元素: ");
        for (int i = 0; i <= top; i++) {
            printf("%d ", stack[i]);
        }
        printf("\n");
    }
}

// 主函数
int main() {
    int choice, value;
    
    while (1) {
        printf("\n--- 栈操作 ---\n");
        printf("1. 入栈\n");
        printf("2. 出栈\n");
        printf("3. 查看栈顶元素\n");
        printf("4. 显示栈\n");
        printf("5. 退出\n");
        printf("请输入你的选择: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("输入要入栈的元素: ");
                scanf("%d", &value);
                push(value);
                break;
            case 2:
                pop();
                break;
            case 3:
                value = peek();
                if (value != -1)
                    printf("栈顶元素为: %d\n", value);
                break;
            case 4:
                printStack();
                break;
            case 5:
                exit(0);
            default:
                printf("无效选择，请重新输入\n");
        }
    }
    
    return 0;
}

