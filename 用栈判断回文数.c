#include <stdio.h>
#include <stdlib.h>
#define MAX 50
typedef struct {
	int top;
	int data[MAX];
}Stack;
//初始化 
void initStack(Stack *stack){
	stack->top=-1;
}
//判空
int isEmpty(Stack *stack){
	return stack->top==-1;
}
//判满
int isFull(Stack *stack){
	return stack->top==MAX-1;
}
//入栈
void push(Stack *stack, int value){
	if(!isFull(stack)){
		stack->data[++(stack->top)]=value;
	}
	else{
		printf("栈满，无法入栈\n"); 
	}
}
//出栈
int pop(Stack *stack){
	if(!isEmpty(stack)){
		return stack->data[(stack->top)--];
	}
	else{
		printf("栈空，无法出栈\n");
		return -1;
	}
}
//判断回文数 
int isPalindrome(int num){
	Stack stack;
	initStack(&stack);
	//处理负数情况
	if(num<0){
		return 0;
	} 
	int original=num;
	while(num>0){
		push(&stack,num%10);
		num/=10;
		
	}
	num=original;
	while(num>0){
		int lastDigit=num%10;
		int stackDigit=pop(&stack);
		if(lastDigit!=stackDigit)
		{
			return 0;
		}
		num/=10;
	}
	return 1;
}
int main(){
	int num;
	printf("请输入您要判断的数字");
	scanf("%d",&num);
	Stack stack;
	initStack(&stack);
	if(isPalindrome(num)){
		printf("数字 %d 是回文数\n",num);
	}
	else{
		printf("数字 %d 不是回文数\n",num);
	}
	return 0; 
}











