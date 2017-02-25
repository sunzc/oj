#include <stdio.h>
#include <assert.h>
#include <time.h>
#include <stdlib.h>

#define LIST_SIZE	10

typedef struct node {
	int val;
	struct node *next;
} node_t;

node_t *head;

node_t *initialize_llist(int size); 
node_t *initialize_llist(int size) {
	int i;
	node_t *head, *p;

	assert(size > 0);

	srand(time(NULL));

	head = NULL;
	for (i = 0; i < size; i++) {
		p = (node_t *) malloc(sizeof(node_t));
		p->val = rand() % LIST_SIZE;

		// insert p into link list
		if (head == NULL) {
			head = p;
			head->next = NULL;
		} else {
			p->next = head;
			head = p;
		}
	}

	return head;
}

void traverse_llist(node_t *head);
void traverse_llist(node_t *head) {
	node_t *p;
	p = head;

	assert (head != NULL);

	printf("traverse link list:\n");
	while(p != NULL) {
		printf("%d ", p->val);
		p = p->next;
	}
	printf("\n");

	return;
}

// Merge list in increase order
node_t *merge_list(node_t *head1, node_t *head2);
node_t *merge_list(node_t *head1, node_t *head2) {
	node_t *p1, *p2, *head, *tail;

	p1 = head1;
	p2 = head2;

	tail = NULL;
	head = NULL;
	while(p1 != NULL && p2 != NULL) {
		if(head == NULL) {
			if (p1->val > p2->val) {
				head = p2;
				p2 = p2->next;
				tail = head;
			} else {
				head = p1;
				p1 = p1->next;
				tail = head;
			}
		} else {
			if (p1->val > p2->val) {
				tail->next = p2;
				tail = p2;
				p2 = p2->next;
			} else {
				tail->next = p1;
				tail = p1;
				p1 = p1->next;
			}
		}
	}

	if (p1 != NULL)
		tail->next = p1;
	else if (p2 != NULL)
		tail->next = p2;

	return head;
}


node_t *sort_llist(node_t *head);
node_t *sort_llist(node_t *head) {
	node_t *mid, *pre_mid, *tail;
	node_t *head1, *head2, *nhead;

	assert(head != NULL);

	// simple case
	if (head->next == NULL)
		return head;

	// divide
	//	1. find the middle node
	pre_mid = tail = mid = head;
	while(tail != NULL && mid->next != NULL) {
		pre_mid = mid;
		mid = mid->next;

		tail = tail->next;
		if (tail != NULL)
			tail = tail->next;
		else
			break;
	}

	//	2. cut the first half
	pre_mid->next = NULL;

	// conquer
	//	1. sort two sublist
	head1 = sort_llist(head);
	head2 = sort_llist(mid);

	//	2. merge results
	nhead = merge_list(head1, head2);

	return nhead;
}

// divide and conquer
int main() {
	node_t *head;

	head = initialize_llist(LIST_SIZE);

	printf("before sort:\n");
	traverse_llist(head);

	head = sort_llist(head);

	printf("after sort:\n");
	traverse_llist(head);

	return 1;
	
}
