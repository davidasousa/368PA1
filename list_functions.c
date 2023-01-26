#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

static Node* node_finder(Node* head, int idx) // Works Based On 0 Based Index
{
	Node* current_node = head;
	for(int i = 0; i < idx; i++)
	{
		current_node = current_node -> next;	
	}
	return current_node;
}

static void swap_adj_nodes(Node* base) // Function Takes A Node And Swaps The Links Of The Next Two Nodes
{
	Node* temp = base -> next -> next -> next;
	Node* left = base -> next;
	
	base -> next = base -> next -> next;
	base -> next -> next = left;
	base -> next -> next -> next = temp;
}

static void list_sort(Node* head, int num_elems)
{
	// Insertion Sort With A Linked List
	printf("%ld\n", node_finder(head, 0) -> value);
	printf("%ld", node_finder(head, 1) -> value);
	
}

/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */	
