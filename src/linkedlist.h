#pragma once

struct node
{
	struct node* next;
	struct node* prev;
	void*(*free_data)();
	void* data;
	// 0 ==, -1 <, 1 >
	int (*compare_data)(void*);
};

struct linkedlist
{
	struct node* top;
	struct node* bot;
	int size;
};


void* linkedlist_get_data(struct linkedlist* l, const int n);
void* linkedlist_append_data(struct linkedlist* l, void* data);
void* linkedlist_prepend_data(struct linkedlist* l, void* data);
void* linkedlist_disconnect_node_bnode(struct linkedlist* l, struct node* n);
void* linkedlist_disconnect_node_bnumb(struct linkedlist* l, struct node* n);
void* linkedlist_init(struct linkedlist* l);
void  linkedlist_print_list(struct linkedlist* l);
void linkedlist_free(struct linkedlist*  l);


