#include <stdio.h>
#include <stdlib.h>
//��������ṹ 
typedef struct Node{
	int data;
	struct Node *next; 
}Node; 
//����һ���½ڵ�
Node *createnode(int data)
{
	Node *newNode =(Node*)malloc(sizeof(Node));
	newNode->data=data;
	newNode->next=NULL;
	return newNode;
 } 
 //������ͷ����Ԫ�� 
void inserthead(Node **head,int data)
{
	Node *newNode=createnode(data);
	newNode->next=*head;
	*head=newNode;
}
//������λ�ò���Ԫ��
void insertlist(Node **head,int data,int position)
{	
	Node *newNode=createnode(data);
	//�������ͷ������ 
	if(position==0)
	{
		inserthead(head,data);
		return; 
	}
	Node *temp=*head;
	for(int i=0;temp!=NULL&&i<position-1;i++)
	{
		temp=temp->next;
		
	}
	//����ڵ�
	if(temp!=NULL)
	{
		newNode->next=temp->next;
		temp->next=newNode;
	 } 
	else
	{
		printf("��������\n");
	}
}
//ɾ��ĳ��Ԫ��
void deleteNode(Node**head,int data)
{
	Node *temp=*head,*prev=NULL;
	if(temp!=NULL&&temp->data==data)
	{
		*head=temp->next;
		free(temp);
		return;
	}
	while(temp!=NULL&&temp->data!=data)
	{
		prev=temp;
		temp=temp->next;
	}
	if(temp==NULL)
	{
		printf("�ýڵ㲻�ڴ�������\n");
		return;
	}
	prev->next=temp->next;
	free(temp);
} 
void deleteposition(Node**head,int position)
{
	if(*head==NULL)
	{
		printf("����Ϊ�գ��޷�ɾ���ڵ�\n");
		return; 
	}
	Node*temp=*head;
	if(position==0)
	{
		*head=temp->next;
		free(temp);
		return;
	}
	//����Ҫɾ���ڵ��ǰһ���ڵ�
	for(int i=0;temp!=NULL&&i<position-1;i++)
	{
		temp=temp->next;
	 } 
	if(temp==NULL||temp->next==NULL)
	{
		printf("λ�ó��������ȣ��޷�ɾ���ڵ�\n");
		return;
	}
	Node*nodetodelete=temp->next;
	temp->next=nodetodelete->next;
	free(nodetodelete);
}
void printlist(Node *head)
{
	Node *temp=head;
	while(temp!=NULL)
	{
		printf("%d->",temp->data);
		temp=temp->next;
	 } 
	 printf("NULL\n");
}
int main()
{
	Node *head=NULL;
	int n;
	printf("��������Ҫ�����Ԫ�ظ���:");
	scanf("%d",&n);
	printf("\n");
	printf("������%d��Ԫ��:",n);
	for(int i=0;i<n;i++)
	{
		int data;
		scanf("%d",&data);
		inserthead(&head,data);
	}
	printf("\n");
	printf("��ӡ��ʼ����:");
	printlist(head);
	printf("\n");
	insertlist(&head,100,2);
	insertlist(&head,501,3);
	printf("����������Ϊ:");
	printlist(head);
	printf("\n");
	//ɾ��Ԫ��
	deleteNode(&head,100);
	printf("ɾ���������");
	printlist(head); 
	printf("\n");
	int pos;
	printf("��������Ҫɾ���ڼ���Ԫ��:");
	scanf("%d",&pos);
	deleteposition(&head,pos-1);
	printf("��ӡɾ����%d��Ԫ�غ������:",pos);
	printlist(head);
	return 0; 
}



 
 
 
 
 
 
 
 

