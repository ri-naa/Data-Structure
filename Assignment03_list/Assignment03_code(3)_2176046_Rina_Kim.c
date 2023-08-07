#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0

typedef int element;
typedef struct ListNode {
	element data;
	struct ListNode* link;
}ListNode;

typedef struct { //double pointer 역할
	ListNode* head; //address of first node
	ListNode* tail; //address of last node
	int length;
}ListType;
ListType list1;

int is_empty(ListType* list) {
	if (list->head == NULL) return 1;
	else return 0;
}

int get_length(ListType* list) 
{
	return list->length;
}

//return node pointer of pos in the list
ListNode* get_node_at(ListType* list, int pos) 
{
	int i;
	ListNode* tmp_node = list->head;
	if (pos < 0) return NULL;
	for (i = 0; i < pos; i++)
		tmp_node = tmp_node->link;
	return tmp_node;
}

element get_entry(ListType* list, int pos) 
{
	ListNode* p;
	if (pos >= list->length) {
		printf("Position error");
		exit(1);
	}
	p = get_node_at(list, pos);
	return p->data;
}

void display(ListType* list) 
{
	int i;
	ListNode* node = list->head;
	printf("(");
	for (i = 0; i < list->length; i++) {
		printf("%d ", node->data);
		node = node->link;
	}
	printf(")\n");
}

int is_in_list(ListType* list, element item) 
{
	ListNode* p;
	p = list->head;
	while ((p != NULL)) {
		if (p->data == item) break;
		p = p->link;
	}
	if (p == NULL) return FALSE;
	else return TRUE;
}

void init(ListType* list) {
	list->length = 0;
	list->head = list->tail = NULL;
}

void insert_node(ListType* list, ListNode* p, ListNode* new_node) { //list(double pointer), preceding node, new node
	if (list->head == NULL) {
		new_node->link = NULL;
		list->head = new_node;
	}
	else {
		if (p == NULL) {
			printf("The preceding node cannot be NULL.\n");
			exit(1);
		}
		else {
			new_node->link = p->link;
			p->link = new_node;
		}
	}
}

void remove_node(ListType* list, ListNode* p, ListNode* removed) { //list(double pointer), preceding node, new node
	if (list->head == NULL) {
		printf("The list is blank.\n");
	}
	else {
		if (p == NULL)
			printf("The preceding node cannot be NULL.\n");
		else {
			p->link = removed->link;
			free(removed);
		}
	}
}

void add(ListType* list, int position, element data) //중간에 node 추가
{
	ListNode* p;
	if ((position >= 0) && (position <= list->length)) {
		ListNode* node = (ListNode*)malloc(sizeof(ListNode));
		if (node == NULL) {
			printf("Memory allocation error");
			exit(1);
		}

		node->data = data;
		p = get_node_at(list, position - 1); //previous node
		insert_node(list, p, node);
		list->length++;
	}
}

void delete(ListType* list, int pos) //중간에 있는 node 삭제
{
	if (!is_empty(list) && (pos >= 0) && (pos < list->length)) {
		ListNode* p = get_node_at(list, pos - 1);
		ListNode* removed = get_node_at(list, pos);
		remove_node(list, p, removed);
		list->length--;
	}
}

void add_first(ListType* list, element data) {
	ListNode* new_node = (ListNode*)malloc(sizeof(ListNode));
	if (new_node == NULL) {
		printf("Memory allocation error");
		exit(1);
	}
	new_node->data = data;

	if (list->head == NULL) {//list에 아무것도 없는 경우
		new_node->link = NULL;
		list->head = list->tail = new_node;
	}
	else {
		new_node->link = list->head; //address of first node = *phead
		list->head = new_node;
	}
	list->length++;
}

void add_last(ListType* list, element data) { 
	ListNode* temp = (ListNode*)malloc(sizeof(ListNode));
	if (temp == NULL) {
		printf("Memory allocation error");
		exit(1);
	}
	temp->data = data;

	//여기부터가 add middle함수 에서는 insert_node역할
	if (list->tail == NULL) { //list에 아무것도 없는 경우
		temp->link = NULL;
		list->head = list->tail = temp; 
	}
	else {
		list->tail->link = temp;
		list->tail = temp; //tail은 temp로 update하기
		temp->link = NULL;
	}
	list->length++;
}

void delete_first(ListType* list) 
{
	if (list->head == NULL) {
		printf("The list is blank.\n");
	}
	else { //
		ListNode* removed = get_node_at(list, 0); //첫번째에 있는 지울 node를 p에 저장
		list->head = (list->head)->link; //head 업데이트해주기
		free(removed);	
	}
	list->length--;
}

void delete_last(ListType* list)	//delete last는 tail을 마지막에서 두번째 node로 업데이트하고 마지막 삭제
{ 
	ListNode* p = get_node_at(list, list->length - 2); //마지막에서 두번째 node
	ListNode* removed = get_node_at(list, list->length - 1); //마지막 node
	if (list->tail == NULL) {
		printf("The list is blank.\n");
	}
	else {
		list->tail = p;
		p->link = NULL;
		free(removed);
	}
	list->length--;
}

int main() 
{
	ListType list1;
	init(&list1);

	add_first(&list1, 20);
	add_last(&list1, 30);
	add_first(&list1, 10);
	add_last(&list1, 40);
	add(&list1, 2, 70);
	display(&list1);

	delete(&list1, 2);
	delete_first(&list1);
	delete_last(&list1);
	display(&list1);

	printf("%s\n", is_in_list(&list1, 20) == TRUE ? "TRUE" : "FALSE");
	printf("%d\n", get_entry(&list1, 0));
}

