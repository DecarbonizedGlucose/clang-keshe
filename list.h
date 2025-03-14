#pragma once

typedef struct Node {
	void* data;
	struct Node* prev;
	struct Node* next;
} Node;

// List管理的由Node组成的双链表
// 对于所有节点的索引idx，从1开始算
typedef struct List{
	int length;
	Node* head;
	Node* tail;
} List;

Node* createNode(void* data);

List* createEmptyList();

Node* addListFirst(List* list, void* pdata);

Node* addListLast(List* list, void* pdata);

Node* addListIdx(List* list, void* pdata, int idx);

Node* delListFirst(List* list);

Node* delListLast(List* list);

Node* delListIdx(List* list, int idx);

Node* getListIdxNode(List* list, int idx);

void destroyList(List* list);

Node* findListElemNode(
	List* list,
	void* data,
	int isDataEqual(void*, void*) // 这招只对windows有效
);

int findListElemIdx(
	List* list,
	void* data,
	int isDataEqual(void*, void*)
);

List* generateSublist_Ref(
	List* list,
	void* data_ref,
	int isDataFit(void*, void*),
	void* dataCopy(void*)
);

List* generateSublist_Det(
	List* list,
	int isDataFit(void*),
	void* dataCopy(void*)
);

void merge(Node** arr,Node** help,int l,int r,int m,int cmp(void*,void*));

void mergeSort(Node** nodes,Node** help,int l,int r,int cmp(void*,void*));

int sortForList(List* list,int cmp(void*,void*));

void reverseList(List* list);
