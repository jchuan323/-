#include <stdio.h>
#include <stdlib.h>
#define MAX 50
typedef struct {
	int top;
	int data[MAX];
}Stack;
//��ʼ�� 
void initStack(Stack *stack){
	stack->top=-1;
}
//�п�
int isEmpty(Stack *stack){
	return stack->top==-1;
}
//����
int isFull(Stack *stack){
	return stack->top==MAX-1;
}
//��ջ
void push(Stack *stack, int value){
	if(!isFull(stack)){
		stack->data[++(stack->top)]=value;
	}
	else{
		printf("ջ�����޷���ջ\n"); 
	}
}
//��ջ
int pop(Stack *stack){
	if(!isEmpty(stack)){
		return stack->data[(stack->top)--];
	}
	else{
		printf("ջ�գ��޷���ջ\n");
		return -1;
	}
}
//�жϻ����� 
int isPalindrome(int num){
	Stack stack;
	initStack(&stack);
	//���������
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
	printf("��������Ҫ�жϵ�����");
	scanf("%d",&num);
	Stack stack;
	initStack(&stack);
	if(isPalindrome(num)){
		printf("���� %d �ǻ�����\n",num);
	}
	else{
		printf("���� %d ���ǻ�����\n",num);
	}
	return 0; 
}











