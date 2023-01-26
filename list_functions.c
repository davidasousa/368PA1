#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

// NODED FINDER -> SLOW == NO LOOPS

static void swap_adj_nodes(Node* prev) // Function Takes A Node And Swaps The Links Of The Next Two Nodes
{
	Node* temp = prev -> next -> next -> next;
	Node* left = prev -> next;
	
	prev -> next = prev -> next -> next;
	prev -> next -> next = left;
	prev -> next -> next -> next = temp;
}

static Node** list_sort(Node* head, int num_elems)
{
	// Insertion Sort With A Linked List
	// Takes N Elements From 0 - N Of A List Sorts It 
	// Sorting A Linked List Goes From The Front To The Back Looking Forwards
	
	// First Find Smallest Element
	Node* curr = head -> next;
	Node* prev = head;

	Node** first_node = malloc(sizeof(*first_node));
	first_node = &prev;

	if(curr -> value < prev -> value)
	{
		curr -> next = prev;
		prev -> next = NULL;
		first_node = &curr;
	}
	return first_node;
}
	

/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */	
