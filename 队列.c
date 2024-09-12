#include <stdio.h>
#include <stdlib.h>
#define MAX 5
//������� 
typedef struct Queue{
	int items[MAX];
	int front;
	int rear;
}Queue;
void initQueue(Queue *q){
	q->front=-1;
	q->rear=-1;
}
//�п� 
int isEmpty(Queue *q)
{
	return q->front==-1;
 } 
//���� 
int isFull(Queue *q){
	return q->rear==MAX-1;
} 
//��� 
void enQueue(Queue *q,int value){
	if(isFull(q))
	{
		printf("�����������޷���ӣ�\n");
	}
	else{
		if(q->front==-1){
			q->front=0;
			
		}
		q->rear++;
		q->items[q->rear]=value;
		printf("Ԫ�� %d ����ӣ�\n",value);	
	}
}
//����
int deQueue(Queue *q){
	int item;
	if(isEmpty(q)){
		printf("����Ϊ�գ����ܳ��ӣ�");
		return -1;
	}
	else{
		item = q->items[q->front];
        q->front++;
        if (q->front > q->rear) {
            // ���ö���
            q->front = q->rear = -1;
        }
        return item;
	}
} 
//�鿴�Ӷ�Ԫ�� 
int peek(Queue *q){
	if(isEmpty(q)){
		printf("����Ϊ�գ�û�жӶ�Ԫ��");
		return -1; 
	} 
	else{
		return q->items[q->front];
	} 
}
//��ӡԪ��
void printQueue(Queue *q){
    if (isEmpty(q)) {
        printf("����Ϊ�գ�\n");
    } else {
        printf("�����е�Ԫ��: ");
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
	printf("��������Ҫ�����Ԫ�ظ���:");

	scanf("%d",&n);
	for(int i=1;i<=n;i++) {	
		printf("��������Ҫ�����Ԫ��:");
		scanf("%d",&data);
		enQueue(&q,data);
	}
	printQueue(&q);
	printf("����Ԫ��: %d\n", deQueue(&q));
    printf("����ͷԪ��: %d\n", peek(&q));
    printQueue(&q);
}













