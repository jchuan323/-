#include <stdio.h>
#include <stdlib.h>
//定义链表结构 
typedef struct Node{
	int data;
	struct Node *next; 
}Node; 
//创建一个新节点
Node *createnode(int data)
{
	Node *newNode =(Node*)malloc(sizeof(Node));
	newNode->data=data;
	newNode->next=NULL;
	return newNode;
 } 
 //在链表头插入元素 
void inserthead(Node **head,int data)
{
	Node *newNode=createnode(data);
	newNode->next=*head;
	*head=newNode;
}
//在任意位置插入元素
void insertlist(Node **head,int data,int position)
{	
	Node *newNode=createnode(data);
	//如果是在头部插入 
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
	//插入节点
	if(temp!=NULL)
	{
		newNode->next=temp->next;
		temp->next=newNode;
	 } 
	else
	{
		printf("超出链表！\n");
	}
}
//删除某个元素
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
		printf("该节点不在此链表中\n");
		return;
	}
	prev->next=temp->next;
	free(temp);
} 
void deleteposition(Node**head,int position)
{
	if(*head==NULL)
	{
		printf("链表为空，无法删除节点\n");
		return; 
	}
	Node*temp=*head;
	if(position==0)
	{
		*head=temp->next;
		free(temp);
		return;
	}
	//查找要删除节点的前一个节点
	for(int i=0;temp!=NULL&&i<position-1;i++)
	{
		temp=temp->next;
	 } 
	if(temp==NULL||temp->next==NULL)
	{
		printf("位置超出链表长度，无法删除节点\n");
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
	printf("请输入你要输入的元素个数:");
	scanf("%d",&n);
	printf("\n");
	printf("请输入%d个元素:",n);
	for(int i=0;i<n;i++)
	{
		int data;
		scanf("%d",&data);
		inserthead(&head,data);
	}
	printf("\n");
	printf("打印初始链表:");
	printlist(head);
	printf("\n");
	insertlist(&head,100,2);
	insertlist(&head,501,3);
	printf("插入后的链表为:");
	printlist(head);
	printf("\n");
	//删除元素
	deleteNode(&head,100);
	printf("删除后的链表");
	printlist(head); 
	printf("\n");
	int pos;
	printf("请输入你要删除第几个元素:");
	scanf("%d",&pos);
	deleteposition(&head,pos-1);
	printf("打印删除第%d个元素后的链表:",pos);
	printlist(head);
	return 0; 
}



 
 
 
 
 
 
 
 

