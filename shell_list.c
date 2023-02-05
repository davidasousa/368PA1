#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

Node *List_Load_From_File(char *filename);

int List_Save_To_File(char *filename, Node *list);

Node *List_Shellsort(Node *list, long *n_comp);

typedef struct _dummy 
{
	Node* curr;
	Node* prev;
} dummy;

static void bubble_sort_list(Node *head, int size, Node** head_ptr)
{
	*head_ptr = head;
	Node* curr;
	Node* temp;
	Node* prev;
	Node* next;


	for(int j = 0; j < size - 1; j++) 
	{
		dummy dummy_node = (dummy){.prev = NULL, .curr = *head_ptr};
		for(int i = 0; i < size - 1 - j; i++)
		{
			if(dummy_node.prev == NULL && dummy_node.curr -> value > dummy_node.curr -> next -> value)
			{
				curr = dummy_node.curr;
				next = dummy_node.curr -> next;
				temp = dummy_node.curr -> next -> next;	
				curr -> next = temp;
				next -> next = curr;

				*head_ptr = next;
				dummy_node.curr = next;
				
			}
			else if(dummy_node.curr -> next -> next == NULL && dummy_node.curr -> value > dummy_node.curr -> next -> value)
			{
				prev = dummy_node.prev;
				curr = dummy_node.curr;
				next = dummy_node.curr -> next;

				curr -> next = NULL;
				next -> next = curr;
				prev -> next = next;

				dummy_node.curr = next;
			}
			dummy_node.prev = dummy_node.curr;
			dummy_node.curr = dummy_node.curr -> next;
		}
	}

/*	
	for(int i = 0; i < size - 1; i++)
	{
		dummy dummy_node = (dummy){.prev = NULL, .curr = *head_ptr};
		while(dummy_node.curr -> next -> next != NULL)
		{	
			// Front Two Elems
			if(dummy_node.prev == NULL && dummy_node.curr -> value > dummy_node.curr -> next -> value)
			{
				
				curr = dummy_node.curr;
				next = dummy_node.curr -> next;
				temp = dummy_node.curr -> next -> next;

				curr -> next = temp;
				next -> next = curr;

				dummy_node.curr = next;
				*head_ptr = next;
				
			}
			else if(dummy_node.curr -> next -> next != NULL && dummy_node.curr -> value > dummy_node.curr -> next -> value) // TESTING MIDDLE CONDITION
			{
				prev = dummy_node.prev;
				curr = dummy_node.curr;
				next = dummy_node.curr -> next;	
				temp = dummy_node.curr -> next -> next;

				prev -> next = next;
				next -> next = curr;
				curr -> next = temp;

				dummy_node.curr = next;
			}
			else if(dummy_node.curr -> next -> next == NULL && dummy_node.curr -> value > dummy_node.curr -> next -> value)
			{
				
				prev = dummy_node.prev;
				curr = dummy_node.curr;
				next = dummy_node.curr -> next;

				next -> next = curr;
				curr -> next = NULL;
				prev -> next = next;

				dummy_node.curr = next;

			}
			dummy_node.prev = dummy_node.curr;
			dummy_node.curr = dummy_node.curr -> next;	
		}
	}
	*/
	return;
}


/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
