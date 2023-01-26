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

static void list_sort(Node* head, Node** new_head, int num_elems)
{
	// Insertion Sort With A Linked List
	// Takes N Elements From 0 - N Of A List Sorts It 
	// Sorting A Linked List Goes From The Front To The Back Looking Forwards
	
	// First Find Smallest Element
	
	Node* curr = head -> next;
	Node* prev = head;
	
	if(num_elems == 2)
	{
		if(curr -> value < prev -> value)
		{		
			curr -> next = prev;
			prev -> next = NULL;
			*new_head = curr;
		}
		else
			*new_head = prev;
	}
	else
	{
		*new_head = prev;

		Node* first = prev;

		if(curr -> value < prev -> value)
		{
			Node* temp = curr -> next;
			curr -> next = prev;
			prev -> next = temp;
			*new_head = curr;

			first = curr;
			curr = prev -> next;	

		}
		else
		{	
			first = prev;
			prev = curr;
			curr = curr -> next;
		}

		for(int i = 1; i < num_elems - 1; i++)
		{
			if(curr -> value < prev -> value)
			{
				Node* temp = curr -> next;
				first -> next = curr;
				curr -> next = prev;
				prev -> next = temp;

				first = first -> next;
				curr = prev -> next;
			}
			else
			{	
				first = prev;
				prev = curr;
				curr = curr -> next;
			}
		}

		



// second pass

	}
}
	

/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */	
