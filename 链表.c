#include <stdio.h>
#include <stdlib.h>
#define InitSize 10
typedef struct{
	int* data;
	int MaxSize;
	int length;
}Seqlist;
void InitList(Seqlist *L)
{
	L->data = (int*)malloc(InitSize * sizeof(int));
	L->length = 0;
	L->MaxSize = InitSize;
}
void IncreaseSize(Seqlist* L, int len)
{
	int* p = L->data;
	L->data = (int*)malloc((L->MaxSize + len) * sizeof(int));
	for (int i = 0;i < L->length; i++)
	{
		L->data[i] = p[i];
		
	}
	L->MaxSize = L->MaxSize + len;
	free(p);
}
int main() {
	Seqlist L;
	InitList(&L);
	// ���һЩԪ�ص� Seqlist ��
	L.data[0] = 10;
	L.data[1] = 20;
	L.data[2] = 30;
	L.length = 3;  // ���� length

	// ��ӡԪ������֤
	for (int i = 0; i < L.length; i++) {
		printf("Element at index %d: %d\n", i, L.data[i]);
	}
	IncreaseSize(&L, 5);
	// ������Ӹ���Ԫ��
	L.data[3] = 40;
	L.data[4] = 50;
	L.length += 2;  // ���� length

	// �ٴδ�ӡԪ������֤
	for (int i = 0; i < L.length; i++) {
		printf("Element at index %d: %d\n", i, L.data[i]);
	}
	free(L.data);
	return 0;
}
