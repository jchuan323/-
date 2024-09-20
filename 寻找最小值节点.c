#include <stdio.h>
#include <stdlib.h>
typedef struct Node{
	int data;
	struct Node *next;
}Node;
Node *head=NULL;
Node *tail=NULL;
Node *createNode(int data)
{
	Node *newNode=(Node*)malloc(sizeof(Node));
	newNode->next=NULL;
	newNode->data=data;
	return newNode;
}

//尾插法
void insertTail(int value){
	Node *newNode=createNode(value);
	if(head==NULL){
		head=tail=newNode;
	}
	else{
		tail->next=newNode;
		tail=newNode;
	}
	
} 
void printlist(){
	Node *tail=head;
	while(tail!=NULL){
		printf("%d->",tail->data );
		tail=tail->next;
	}
	printf("NULL\n");
}
int main(){
	int n;
	printf("请输入您要输入的元素个数:");
	scanf("%d",&n);
	printf("\n");
	printf("请输入你要输入的元素:\n");
	for(int i=0;i<n;i++){
		int value;
		scanf("%d",&value);
		insertTail(value);
	}
	printf("链表:\n");
	printlist();
	Node *p=head;
	int minValue=p->data;
	while(p!=NULL){
		if(p->data<minValue){
			minValue=p->data;
		}
		p=p->next;
	}
	printf("最小值为%d\n",minValue);
	p=head;
	while(p->next!=NULL&&p->next->data!=minValue){
		p=p->next;
	}
	
	if(head->data==minValue){
		Node *temp=head;
		head=head->next;
		free(temp);
	}
	if(p->next!=NULL){
		Node *temp=p->next;
		p->next=temp->next;
		if(temp==tail){
			tail=p;
		}
		free(temp);
	}
	printf("打印删除后的链表:\n");
	printlist();
	return 0;	
} 
