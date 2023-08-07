#include <stdio.h>
#include <stdlib.h>

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

void init(ListType* list)
{
	list->length = 0;
	list->head = list->tail = NULL;
}

void add_last(ListType* list, element data)
{
	ListNode* temp = (ListNode*)malloc(sizeof(ListNode));
	if (temp == NULL) {
		printf("Memory allocation error");
		exit(1);
	}
	temp->data = data;

	if (list->tail == NULL) { //list에 아무것도 없는 경우
		list->head = list->tail = temp;
	}
	else {
		list->tail->link = temp;
		list->tail = temp; //tail은 temp로 update하기
		temp->link = NULL;
	}
	list->length++;
}

//time complexcity = O(m+n)
void merge(ListType* a, ListType* b)
{
	ListNode* head1 = a->head;
	ListNode* head2 = b->head;

	ListType c;
	init(&c);

	for (int i = 0; i < a->length + b->length; i++)
	{
		if ((head1->data) > (head2->data)) {
			add_last(&c, head2->data);
			head2 = head2->link;
		}
		else { // if (head1->data <= head2->data)
			add_last(&c, head1->data);
			head1 = head1->link;
		}

		if (head1 == NULL) { //listtype a가 모두 들어갔을 때
			while (head2 != NULL) { // b에 남은 node들 c에 넣어주기
				add_last(&c, head2->data);
				head2 = head2->link;
			}
			break;
		}
		else if (head2 == NULL) { //listType b가 모두 들어갔을 때
			while (head1 != NULL) { //a에 남은 node들 c에 넣어주기
				add_last(&c, head1->data);
				head1 = head1->link;
			}
			break;
		}
	}

	display(&c);
}


void main() {
	ListType a;
	ListType b;

	init(&a);
	init(&b);

	add_last(&a, 1);
	add_last(&a, 2);
	add_last(&a, 5);
	add_last(&a, 10);
	add_last(&a, 15);
	add_last(&a, 20);
	add_last(&a, 25);
	printf("a = ");
	display(&a);

	add_last(&b, 3);
	add_last(&b, 7);
	add_last(&b, 8);
	add_last(&b, 15);
	add_last(&b, 18);
	add_last(&b, 30);
	printf("b = ");
	display(&b);

	printf("c = ");
	merge(&a, &b);
}