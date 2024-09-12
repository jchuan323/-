#include <stdio.h>
#include <stdlib.h>
#define MAX 5
//定义队列 
typedef struct Queue{
	int items[MAX];
	int front;
	int rear;
}Queue;
void initQueue(Queue *q){
	q->front=-1;
	q->rear=-1;
}
//判空 
int isEmpty(Queue *q)
{
	return q->front==-1;
 } 
//判满 
int isFull(Queue *q){
	return q->rear==MAX-1;
} 
//入队 
void enQueue(Queue *q,int value){
	if(isFull(q))
	{
		printf("队列已满，无法入队！\n");
	}
	else{
		if(q->front==-1){
			q->front=0;
			
		}
		q->rear++;
		q->items[q->rear]=value;
		printf("元素 %d 已入队！\n",value);	
	}
}
//出队
int deQueue(Queue *q){
	int item;
	if(isEmpty(q)){
		printf("队列为空，不能出队！");
		return -1;
	}
	else{
		item = q->items[q->front];
        q->front++;
        if (q->front > q->rear) {
            // 重置队列
            q->front = q->rear = -1;
        }
        return item;
	}
} 
//查看队顶元素 
int peek(Queue *q){
	if(isEmpty(q)){
		printf("队列为空，没有队顶元素");
		return -1; 
	} 
	else{
		return q->items[q->front];
	} 
}
//打印元素
void printQueue(Queue *q){
    if (isEmpty(q)) {
        printf("队列为空！\n");
    } else {
        printf("队列中的元素: ");
        for (int i = q->front; i <= q->rear; i++) {
            printf("%d ", q->items[i]);
        }
        printf("\n");
    }
} 
int main()
{
	struct Queue q;
	initQueue(&q);
	int data,n;
	printf("请输入你要输入的元素个数:");

	scanf("%d",&n);
	for(int i=1;i<=n;i++) {	
		printf("请输入你要输入的元素:");
		scanf("%d",&data);
		enQueue(&q,data);
	}
	printQueue(&q);
	printf("出队元素: %d\n", deQueue(&q));
    printf("队列头元素: %d\n", peek(&q));
    printQueue(&q);
}













