#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

static void sort_list_size2(Node* head, Node** new_head)
{
	Node* curr = head -> next;
	Node* prev = head;
	
	if(curr -> value < prev -> value)
	{		
		curr -> next = prev;
		prev -> next = NULL;
		*new_head = curr;
	}
	else
		*new_head = prev;
}

static void bubble_sort_list(long sentinal, Node* head, Node** new_head, int num_elems)
{
}

static void find_sentinal(Node* head, Node** new_head, int num_elems) // Sentinal Is The Largest Val In The List
{
	Node* curr = head -> next;
	Node* prev = head;
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
}
	

/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */	
