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

List* createList() {
	List* list = (List*)malloc(sizeof(List));
	if (list == NULL) {
		return NULL;
	}
	list->length = 0;
	list->head = NULL;
	list->tail = NULL;
	return list;
}

Node* addListFirst(List* l, void* pdata) {
	Node* new_head = (Node*)malloc(sizeof(Node));
	if (new_head == NULL) {
		return NULL;
	}
	new_head->data = pdata;
	new_head->prev = NULL;
	new_head->next = l->head;
	l->head->prev = new_head;
	l->head = new_head;
	l->length++;
	return new_head;
}

Node* addListLast(List* l, void* pdata) {
	Node* new_tail = (Node*)malloc(sizeof(Node));
	if (new_tail == NULL) {
		return NULL;
	}
	new_tail->data = pdata;
	new_tail->next = NULL;
	new_tail->prev = l->tail;
	l->tail->next = new_tail;
	l->tail = new_tail;
	l->length++;
	return l->tail;
}

Node* addListIdx(List* l, void* pdata, int idx) {
	if (idx < 0 || idx > l->length) {
		return NULL;
	}
	if (idx == l->length) {
		return addListLast(l, pdata);
	}
	if (idx == 0 && l->length == 0) {
		return addListFirst(l, pdata);
	}
	Node* cur = l->head;
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
	return new_node;
}

Node* delListFirst(List* l) {
	if (l->length == 0) {
		return NULL;
	}
	Node* old_head = l->head;
	if (old_head->next == NULL) {
		l->head = NULL;
		l->tail = NULL;
	}
	else {
		l->head = old_head->next;
		l->head->prev = NULL;
	}
	free(old_head->data);
	old_head->next = NULL;
	old_head->prev = NULL;
	free(old_head);
	old_head = NULL;
	return l->head;
}

Node* delListLast(List* l) {
	if (l->length == 0) {
		return NULL;
	}
	if (l->length == 1) {
		return delListFirst(l);
	}
	Node* old_tail = l->tail;
	l->tail = old_tail->prev;
	l->tail->next = NULL;
	free(old_tail->data);
	old_tail->next = NULL;
	old_tail->prev = NULL;
	free(old_tail);
	old_tail = NULL;
	return l->tail;
}

Node* delListIdx(List* l, int idx) {
	if (l->length == 0 || idx > l->length) {
		return NULL;
	}
	if (idx == 1) {
		return delListFirst(l);
	}
	if (idx == l->length - 1) {
		return delListLast(l);
	}
	Node* cur = l->head;
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
	return re;
}

void destroyList(List* l) {
	while (l->length) {
		delListFirst(l);
	}
	free(l);
	l = NULL;
}

Node* findElem(List* l, void* data, int isDataEqual(void*, void*)) {
	if (l->length == 0) {
		return NULL;
	}
	Node* cur = l->head;
	while (cur != NULL) {
		if (isDataEqual(cur->data, data)) {
			return cur;
		}
	}
	return NULL;
}

