#include "list.h"
#include <stdlib.h>

Node* createNode(void* data) {
	Node* node = (Node*)malloc(sizeof(Node));
	if (node == NULL) {
		return NULL;
	}
	node->data = data;
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

Node* addListFirst(List* list, void* pdata) {
	Node* new_head = (Node*)malloc(sizeof(Node));
	if (new_head == NULL) {
		return NULL;
	}
	new_head->data = pdata;
	new_head->prev = NULL;
	new_head->next = list->head;
	list->head->prev = new_head;
	list->head = new_head;
	list->length++;
	return new_head;
}

Node* addListLast(List* list, void* pdata) {
	Node* new_tail = (Node*)malloc(sizeof(Node));
	if (new_tail == NULL) {
		return NULL;
	}
	new_tail->data = pdata;
	new_tail->next = NULL;
	new_tail->prev = list->tail;
	if (list->tail != NULL) {
		list->tail->next = new_tail;
		list->tail = new_tail;
	}
	else {
		list->head = new_tail;
		list->tail = new_tail;
	}
	list->length++;
	return list->tail;
}

Node* addListIdx(List* list, void* pdata, int idx) {
	if (idx < 0 || idx > list->length) {
		return NULL;
	}
	if (idx == list->length) {
		return addListLast(list, pdata);
	}
	if (idx == 0 && list->length == 0) {
		return addListFirst(list, pdata);
	}
	Node* cur = list->head;
	for (int i = 0; i < idx; ++i) {
		cur = cur->next;
	}
	Node* new_node = (Node*)malloc(sizeof(Node));
	if (new_node == NULL) {
		return NULL;
	}
	new_node->data = pdata;
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
		list->head = old_head->next;
		list->head->prev = NULL;
	}
	free(old_head->data);
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
	old_tail->next = NULL;
	old_tail->prev = NULL;
	free(old_tail);
	old_tail = NULL;
	list->length--;
	return list->tail;
}

Node* delListIdx(List* list, int idx) {
	if (list->length == 0 || idx > list->length) {
		return NULL;
	}
	if (idx == 1) {
		return delListFirst(list);
	}
	if (idx == list->length - 1) {
		return delListLast(list);
	}
	Node* cur = list->head;
	for (int i = 0; i < idx; ++i) {
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

Node* getListHead(List* list) {
	if (list == NULL) {
		return NULL;
	}
	return list->head;
}

Node* getListTail(List* list) {
	if (list == NULL) {
		return NULL;
	}
	return list->tail;
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
		return NULL;
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

//主播主播，有没有更优雅的解决办法?
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

List* mergeSortedLists(List* list1, List* list2) {

}

void listMergeSort(List* list) {

}