#include <stdio.h>
#include <stdlib.h>
//定义队列结构 
typedef struct Queue{
	int data;
	struct Queue *next;
}Q;
Q *front=NULL;
Q *rear=NULL;
//初始化
void initQueue(){
	front=rear=(Q*)malloc(sizeof(Q));
	front->next=NULL;
} 
//入队
void enQueue(int data){
	Q *s = (Q*)malloc(sizeof(Q)); // 为新元素分配空间
    if (!s) {
        printf("内存分配失败\n");
        return;
    }
	s->data=data;
	s->next=NULL;
	if(front==NULL){
		front=s;
		rear=s;
	}
	else{
		rear->next=s;
		rear=s;
	}
 
} 
//出队
int deQueue(){
	if(front==NULL){
		printf("队空，无法出队");
		return -1; 
	}
	Q* temp=front;
	int data=temp->data;
	front=front->next;
	if(front==NULL){
		rear=NULL;
	}
	free(temp);
	return data;
}
 
//打印队列元素
void printQueue(){
	if(front==NULL){
		printf("队空，无法打印"); 
		return ; 
	} 
	Q *temp=front->next;
	while(temp!=NULL)
	{
		printf("%d ",temp->data);
		temp=temp->next;
	}
	printf("\n");
} 
//主函数 
int main()
{
	initQueue();
	int n;
	printf("请输入您要输入的元素个数：\n");
	scanf("%d",&n);
	int data;
	printf("请输入您要输入的元素");
	for(int i=0;i<n;i++)
	{
		scanf("%d",&data);
		enQueue(data); 
	} 
	printf("队列的元素为:");
	printQueue();
	printf("\n");
	deQueue();
	printf("出队后的队列为:");
	printQueue();
	printf("\n");
	printf("出队后的队列为:");
	deQueue();
	printQueue();
 	return 0;
 } 
 
