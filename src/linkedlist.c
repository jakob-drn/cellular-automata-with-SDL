#include "linkedlist.h"

#include <stdio.h>
#include <stdlib.h>

static void* linkedlist_print_traverse_down(const struct node* n);
static void* linkedlist_print_traverse_up(const struct node* n);

static void linkedlist_free_helper(struct node*  n);
static struct node* node_create()
{
	struct node* n=calloc(1,sizeof(struct node));
	return n;
}

static void node_free(struct node* n)
{
	free(n);
}

void* linkedlist_init(struct linkedlist* l)
{
	struct node* n0 = node_create();
	struct node* n1 = node_create();
	l->top=n0;
	l->bot=n1;
	l->top->next=l->bot;
	l->top->prev=0;
	l->bot->prev=l->top;
	l->bot->next=0;
	l->size=2;

	return l;
}

static void* linkedlist_print_traverse_down(const struct node* n)
{
	printf("%p/%p -> ",n,n->data);
	if(n->next==0)
	{	printf("%p",n->next); return 0;}
	return linkedlist_print_traverse_down(n->next);
}
static void* linkedlist_print_traverse_up(const struct node* n)
{
	printf("%p/%p <- ",n,n->data);
	if(n->prev==0)
	{	printf("%p",n->prev); return 0;}
	return linkedlist_print_traverse_up(n->prev);
}

void linkedlist_print_list(struct linkedlist* l)
{
	if(l==0)  {printf("%p\n",l); return;}
	if(l->top==0) {printf("%p | %p (%i)\n",l,l->top,l->size); return;}

	printf("%p | ",l);
	linkedlist_print_traverse_down(l->top);
	printf(" (%i)\n",l->size);
	printf("%p | ",l);
	linkedlist_print_traverse_up(l->bot);
	printf(" (%i)\n",l->size);
}

void* linkedlist_append_data(struct linkedlist* l, void* data)
{
	struct node* n=node_create();
	n->data=data;
	l->bot->next=n;
	n->prev=l->bot;
	l->bot=n;
	l->size++;
}

void linkedlist_free(struct linkedlist  *l)
{
	linkedlist_free_helper(l->top);	
	l->size=0;
	l->top=0;
	l->bot=0;
}

static void linkedlist_free_helper(struct node*  n)
{
	if(n->next==0) {node_free(n); return;}
	linkedlist_free_helper(n->next);
	if(n->free_data!=0) n->free_data();
	node_free(n);
}

static void* linkedlist_get_data_helper_d(struct node* n, const int q, int i)
{
	if(i==q) return n->data;
	return linkedlist_get_data_helper_d(n->next,q,++i);
}
static void* linkedlist_get_data_helper_u(struct node* n, const int q, int i)
{
	if(i==q) return n->data;
	return linkedlist_get_data_helper_u(n->prev,q,--i);
}
void* linkedlist_get_data(struct linkedlist* l, const int n)
{
	if(l->size/2>n) return linkedlist_get_data_helper_d(l->top,n,1);	
	else return linkedlist_get_data_helper_u(l->bot,n,l->size);	
}
