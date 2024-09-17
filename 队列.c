#include <stdio.h>
#include <stdlib.h>
//������нṹ 
typedef struct Queue{
	int data;
	struct Queue *next;
}Q;
Q *front=NULL;
Q *rear=NULL;
//��ʼ��
void initQueue(){
	front=rear=(Q*)malloc(sizeof(Q));
	front->next=NULL;
} 
//���
void enQueue(int data){
	Q *s = (Q*)malloc(sizeof(Q)); // Ϊ��Ԫ�ط���ռ�
    if (!s) {
        printf("�ڴ����ʧ��\n");
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
//����
int deQueue(){
	if(front==NULL){
		printf("�ӿգ��޷�����");
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
 
//��ӡ����Ԫ��
void printQueue(){
	if(front==NULL){
		printf("�ӿգ��޷���ӡ"); 
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
//������ 
int main()
{
	initQueue();
	int n;
	printf("��������Ҫ�����Ԫ�ظ�����\n");
	scanf("%d",&n);
	int data;
	printf("��������Ҫ�����Ԫ��");
	for(int i=0;i<n;i++)
	{
		scanf("%d",&data);
		enQueue(data); 
	} 
	printf("���е�Ԫ��Ϊ:");
	printQueue();
	printf("\n");
	deQueue();
	printf("���Ӻ�Ķ���Ϊ:");
	printQueue();
	printf("\n");
	printf("���Ӻ�Ķ���Ϊ:");
	deQueue();
	printQueue();
 	return 0;
 } 
 
