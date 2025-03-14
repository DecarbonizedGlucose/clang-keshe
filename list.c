#include "list.h"
#include <stdlib.h>
#include <math.h>
// 模块化

Node* createNode(void* data) {
	Node* node = (Node*)malloc(sizeof(Node));
	if (node == NULL) {
		return NULL;
	}
	node->data = data; // 浅拷贝
	return node;
}

List* createEmptyList() {
	List* list = (List*)malloc(sizeof(List));
	if (list == NULL) {
		return NULL;
	}
	list->length = 0;
	list->head = NULL;
	list->tail = NULL;
	return list;
}

// 下面新增数据全是浅拷贝

Node* addListFirst(List* list, void* data) {
	Node* new_head = createNode(data);
	if (new_head == NULL) {
		return NULL;
	}
	new_head->prev = NULL;
	new_head->next = list->head;
	if (list->head != NULL) {
		list->head->prev = new_head;
	}
	else {
		list->tail = new_head;
	}
	list->head = new_head;
	list->length++;
	return new_head;
}

Node* addListLast(List* list, void* data) {
	Node* new_tail = createNode(data);
	if (new_tail == NULL) {
		return NULL;
	}
	new_tail->next = NULL;
	new_tail->prev = list->tail;
	if (list->tail != NULL) {
		list->tail->next = new_tail;
	}
	else {
		list->head = new_tail;
	}
	list->tail = new_tail;
	list->length++;
	return list->tail;
}

// 算insert，所以不允许在最后追加
Node* addListIdx(List* list, void* data, int idx) {
	if (idx < 0 || idx > list->length || idx < 1) {
		return NULL;
	}
	if (list->length == 0) { // idx一定<=length
		return addListFirst(list, data);
	}
	Node* cur = list->head;
	for (int i = 1; i < idx; ++i) {
		cur = cur->next;
	}
	Node* new_node = createNode(data);
	if (new_node == NULL) {
		return NULL;
	}
	new_node->prev = cur->prev;
	cur->prev->next = new_node;
	new_node->next = cur;
	cur->prev = new_node;
	list->length++;
	return new_node;
}

Node* delListFirst(List* list) {
	if (list->length == 0) {
		return NULL;
	}
	Node* old_head = list->head;
	if (old_head->next == NULL) {
		list->head = NULL;
		list->tail = NULL;
	}
	else {
		old_head->next->prev = NULL;
		list->head = old_head->next;
	}
	free(old_head->data);
	old_head->data = NULL;
	old_head->next = NULL;
	old_head->prev = NULL;
	free(old_head);
	old_head = NULL;
	list->length--;
	return list->head;
}

Node* delListLast(List* list) {
	if (list->length == 0) {
		return NULL;
	}
	if (list->length == 1) {
		return delListFirst(list);
	}
	Node* old_tail = list->tail;
	list->tail = old_tail->prev;
	list->tail->next = NULL;
	free(old_tail->data);
	old_tail->data = NULL;
	old_tail->next = NULL;
	old_tail->prev = NULL;
	free(old_tail);
	old_tail = NULL;
	list->length--;
	return list->tail;
}

Node* delListIdx(List* list, int idx) {
	if (list->length == 0 || idx > list->length || idx < 1) {
		return NULL;
	}
	if (idx == 1) {
		return delListFirst(list);
	}
	if (idx == list->length) {
		return delListLast(list);
	}
	Node* cur = list->head;
	for (int i = 1; i < idx; ++i) {
		cur = cur->next;
	}
	cur->prev->next = cur->next;
	cur->next->prev = cur->prev;
	Node* re = cur->next;
	cur->next = NULL;
	cur->prev = NULL;
	free(cur->data);
	cur->data = NULL;
	free(cur);
	cur = NULL;
	list->length--;
	return re;
}

Node* getListIdxNode(List* list, int idx) {
	if (list == NULL || idx > list->length || idx < 1) {
		return NULL;
	}
	Node* cur = list->head;
	for (int i = 1; i < idx; ++i) {
		cur = cur->next;
	}
	return cur;
}

void destroyList(List* list) {
	if (list == NULL) {
		return;
	}
	while (list->length) {
		delListFirst(list);
	}
	free(list);
	list = NULL;
}

Node* findListElemNode(
	List* list,
	void* data,
	int isDataEqual(void*, void*)
) {
	if (list->length == 0) {
		return NULL;
	}
	Node* cur = list->head;
	while (cur != NULL) {
		if (isDataEqual(cur->data, data)) {
			return cur;
		}
		cur = cur->next;
	}
	return NULL;
}

int findListElemIdx(
	List* list,
	void* data,
	int isDataEqual(void*, void*)
) {
	if (list->length == 0) {
		return -1;
	}
	int idx = 1;
	Node* cur = list->head;
	while (cur != NULL) {
		if (isDataEqual(cur->data, data)) {
			return idx;
		}
		cur = cur->next;
		idx++;
	}
	return -1;
}

List* generateSublist_Ref(
	List* list,
	void* data_ref,
	int isDataFit(void*, void*),
	void* dataCopy(void*)
) {
	List* newList = createEmptyList();
	if (newList == NULL) {
		return NULL;
	}
	Node* cur = list->head;
	while (cur != NULL) {
		if (isDataFit(data_ref, cur->data)) {
			addListLast(newList, dataCopy(cur->data));
		}
		cur = cur->next;
	}
	return newList;
}

List* generateSublist_Det(
	List* list,
	int isDataFit(void*),
	void* dataCopy(void*)
) {
	List* newList = createEmptyList();
	if (newList == NULL) {
		return NULL;
	}
	Node* cur = list->head;
	while (cur != NULL) {
		if (isDataFit(cur->data)) {
			addListLast(newList, dataCopy(cur->data));
		}
		cur = cur->next;
	}
	return newList;
}

void merge(Node** arr, Node** help, int l, int r, int m, int cmp(void*, void*)) {
	int i = l;
	int a = l, b = m + 1;
	while (a <= m && b <= r) {
		help[i++] = cmp(arr[a]->data, arr[b]->data) <= 0 ? arr[a++] : arr[b++];
	}
	while (a <= m) {
		help[i++] = arr[a++];
	}
	while (b <= r) {
		help[i++] = arr[b++];
	}
	for (int j = l; j <= r; ++j) {
		arr[j] = help[j];
	}
}

void mergeSort(Node** nodes, Node** help, int l, int r, int cmp(void*, void*)) {
	if (l == r) {
		return 0;
	}
	int m = l + ((r - l) >> 1);
	mergeSort(nodes, help, l, m, cmp);
	mergeSort(nodes, help, m + 1, r, cmp);
	merge(nodes, help, l, r, m, cmp);
}

int sortForList(List* list, int cmp(void*, void*)) {
	if (list == NULL || list->length == 0) {
		return 0;
	}
	if (list->length == 1) {
		return 1;
	}
	Node** nodes = (Node**)malloc(list->length * sizeof(Node*));
	if (nodes == NULL) {
		return 0;
	}
	Node* cur = list->head;
	int idx = 0;
	while (cur != NULL) {
		nodes[idx++] = cur;
		cur = cur->next;
	}
	Node** help = (Node**)malloc(list->length * sizeof(Node*));
	if (help == NULL) {
		free(nodes);
		return 0;
	}
	mergeSort(nodes, help, 0, list->length - 1, cmp);
	free(help);
	help = NULL;
	nodes[0]->prev = NULL;
	nodes[0]->next = nodes[1];
	nodes[list->length - 1]->next = NULL;
	nodes[list->length - 1]->prev = nodes[list->length - 2];
	for (int i = 1; i < list->length - 1; ++i) {
		nodes[i]->next = nodes[i + 1];
		nodes[i]->prev = nodes[i - 1];
	}
	list->head = nodes[0];
	list->tail = nodes[list->length - 1];
	free(nodes);
	nodes = NULL;
	return 1;
}

void reverseList(List* list) {
	Node** nodes = (Node**)malloc(list->length * sizeof(Node*));
	if (nodes == NULL) {
		return 0;
	}
	Node* cur = list->head;
	int idx = 0;
	while (cur != NULL) {
		nodes[idx++] = cur;
		cur = cur->next;
	}
	for (int i = 0; i < list->length; ++i) {
		Node* tmp = nodes[i]->next;
		nodes[i]->next = nodes[i]->prev;
		nodes[i]->prev = tmp;
	}
	list->head = nodes[list->length - 1];
	list->tail = nodes[0];
	free(nodes);
	nodes = NULL;
}