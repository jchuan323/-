#include <stdio.h>
#include <stdlib.h>
#define MAX 100
int stack[MAX];
int top=-1;
//判空 
int isEmpty()
{
	return top==-1;
 } 
 //判满 
int isFull(){
	return top==MAX-1;
}
//入栈 
void push( int value){
	if(isFull())
	{
		printf("栈满!"); 
	}
	else{
		top++;
		stack[top]=value;
	}
} 
//出栈 
int pop()
{
	if(isEmpty())
	{
		printf("栈空，无法出栈\n");
		return -1;
	}
	else{
		return stack[top--];
	}
}
//进制转换decimal输入的数字  base 进制 
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
	printf("转换后的数为:");
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
	printf("请输入你要转换的十进制数字:");
	scanf("%d",&decimal);
	printf("请输入你要转换的进制(2~16):");
	scanf("%d",&base);
	if(base<2||base>16){
		printf("无效的进制，请输入2~16的数字");
		exit(1); 
	}
	decimalToBase(decimal, base);  // 进行进制转换
	return 0;
}














