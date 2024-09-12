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
	// 添加一些元素到 Seqlist 中
	L.data[0] = 10;
	L.data[1] = 20;
	L.data[2] = 30;
	L.length = 3;  // 更新 length

	// 打印元素以验证
	for (int i = 0; i < L.length; i++) {
		printf("Element at index %d: %d\n", i, L.data[i]);
	}
	IncreaseSize(&L, 5);
	// 继续添加更多元素
	L.data[3] = 40;
	L.data[4] = 50;
	L.length += 2;  // 更新 length

	// 再次打印元素以验证
	for (int i = 0; i < L.length; i++) {
		printf("Element at index %d: %d\n", i, L.data[i]);
	}
	free(L.data);
	return 0;
}
