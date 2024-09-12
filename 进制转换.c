#include <stdio.h>
#include <stdlib.h>
#define MAX 100
int stack[MAX];
int top=-1;
//�п� 
int isEmpty()
{
	return top==-1;
 } 
 //���� 
int isFull(){
	return top==MAX-1;
}
//��ջ 
void push( int value){
	if(isFull())
	{
		printf("ջ��!"); 
	}
	else{
		top++;
		stack[top]=value;
	}
} 
//��ջ 
int pop()
{
	if(isEmpty())
	{
		printf("ջ�գ��޷���ջ\n");
		return -1;
	}
	else{
		return stack[top--];
	}
}
//����ת��decimal���������  base ���� 
void decimalToBase(int decimal, int base){

	if(decimal==0)
	{
		printf("0");
		return;
	 } 
	while(decimal>0){
		int remainder=decimal%base;
		push(remainder);
		decimal/=base;
	} 
	printf("ת�������Ϊ:");
	while(!isEmpty())
	{
		int digit=pop();
		if(digit<10)
			printf("%d",digit);
		else{
			printf("%c",digit-10+'A');
		}
	}
	printf("\n");
} 
int main(){
	int decimal;
	int base;
	printf("��������Ҫת����ʮ��������:");
	scanf("%d",&decimal);
	printf("��������Ҫת���Ľ���(2~16):");
	scanf("%d",&base);
	if(base<2||base>16){
		printf("��Ч�Ľ��ƣ�������2~16������");
		exit(1); 
	}
	decimalToBase(decimal, base);  // ���н���ת��
	return 0;
}














