#pragma

typedef struct {
	void* data;
	struct Node* prev;
	struct Node* next;
} Node;

// List管理的由Node组成的双链表
typedef struct {
	int length;
	Node* head;
	Node* tail;
} List;

Node* createNode(void* data);

List* createList();

Node* addListFirst(List* l, void* pdata);

Node* addListLast(List* l, void* pdata);

Node* addListIdx(List* l, void* pdata, int idx);

Node* delListFirst(List* l);

Node* delListLast(List* l);

Node* delListIdx(List* l, int idx);

void destroyList(List* l);

Node* findElem(List* l, void* data, int isDataEqual(void*, void*));
