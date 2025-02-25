#pragma

struct Node {
	void* data;
	struct Node* prev;
	struct Node* next;
};

// List管理的由Node组成的双链表
struct List {
	int length;
	struct Node* head;
	struct Node* tail;
};

struct Node* createNode(void* data);

struct List* createList();

struct Node* addListFirst(struct List* l, void* pdata);

struct Node* addListLast(struct List* l, void* pdata);

struct Node* addListIdx(struct List* l, void* pdata, int idx);

struct Node* delListFirst(struct List* l);

struct Node* delListLast(struct List* l);

struct Node* delListIdx(struct List* l, int idx);

void destroyList(struct List* l);