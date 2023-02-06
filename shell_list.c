#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "shell_list.h"
#include "sequence.h"

typedef struct _dummy 
{
	Node* curr;
	Node* prev;
} dummy;

static int exponent(long base, long power)
{
	int final = base;
	for(int exp_idx = power; exp_idx > 1; exp_idx--)
		final = final * base;
	
	if(power == 0)
		final = 1;

	return final;
}

static long logg(long base, long value) // Returns One Above The Largest Exponent Value For Mallocing The Sequence
{
	long exp = 1;
	while(value >= base)
	{
		value /= base;
		exp++;
	}
	return exp;
}

static void append_list(Node* head, long value)
{
	if(head -> next == NULL)
	{	
		Node* new_node = malloc(sizeof(*new_node));
		head -> next = new_node;
		new_node -> next = NULL;
		new_node -> value = value;
	}
	else
	{
		append_list(head -> next, value);
	}	
}

static Node* scanner(Node* head, int value)
{
	Node* base = head;
	for(int scan_idx = 0; scan_idx < value; scan_idx++)
	{
		base = base -> next;
	}
	return base;
}

static int list_size(Node* head)
{
	int size = 0;
	while(head != NULL)
	{
		size++;
		head = head -> next;
	}
	return size;
}

Node *List_Load_From_File(char *filename)
{	
	FILE* fp = fopen(filename, "r");
	int bytes = 0;
	int size = 0;

	if(fp == NULL)
	{
		return NULL;
	}
	else
	{
		fseek(fp, 0, SEEK_END);
		bytes = ftell(fp);
		fseek(fp, 0, SEEK_SET);
		if(bytes == 0) // If File Can Be Opened And Is Empty
		{
			return NULL;
		}
		size = bytes / 8;
	}
	
	long* buffer = malloc(sizeof(*buffer) * size);
	int longs = fread(buffer, 8, size, fp);

	fclose(fp);

	Node* head = malloc(sizeof(*head));
	head -> value = buffer[0];
	head -> next = NULL;
	
	for(int list_idx = 1; list_idx < longs ; list_idx++)
	{
		append_list(head, buffer[list_idx]);
	}

	free(buffer);
	return head;	
}

int List_Save_To_File(char *filename, Node *list)
{
	
	FILE *fp = fopen(filename, "w");
	int size = list_size(list);

	if(list == NULL || size == 0)
	{
		fclose(fp);
	}
	
	long* storage = malloc(sizeof(*storage) * size);
	Node* curr = list;

	for(int print_idx = 0; print_idx < size; print_idx++)
	{
		*(storage + print_idx) = curr -> value;
		curr = curr -> next;
	}
	fwrite(storage, 8, size, fp);
	free(storage);

	fclose(fp);
	return size;
	
}

static void stack_push(Node* head, long val)
{
	if(head -> next == NULL)
	{
		Node* temp = malloc(sizeof(*temp));
		temp -> value = val;
		temp -> next = NULL;
		head -> next = temp;
	}
	else
		stack_push(head -> next, val);
	return;
}

static void bubble_sort_list(Node *head, int size, Node** head_ptr)
{
	*head_ptr = head;
	Node* curr;
	Node* temp;
	Node* prev;
	Node* next;

	for(int j = 0; j < size - 1; j++) // WORKS
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
			else if(dummy_node.curr -> next -> value < dummy_node.curr -> value)
			{
				prev = dummy_node.prev;
				curr = dummy_node.curr;
				next = dummy_node.curr -> next;
				temp = dummy_node.curr -> next -> next;
				curr -> next = temp;
				next -> next = curr;
				prev -> next = next;
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
	return;
}

static void free_list(Node* head)
{
	if(head -> next != NULL)
	{
		free_list(head -> next);
	}
	free(head);
}

Node *List_Shellsort(Node *list, long *n_comp)
{
	int size = list_size(list); // FINDING SIZE WORKS
								
	int num_ks = exponent(logg(2,size),2);
	n_comp = Generate_2p3q_Seq(size, &num_ks); // GENERATION OF THE SEQUENCE WORKS
	
	//Node* stack_base; // Initializing Stack Base
	int k;
	
	for(int k_idx = num_ks - 1; k_idx >= 0; k_idx--) // ITERATING K FROM K_MAX TO 1
	{
		k = n_comp[k_idx]; // ASSIGNING K FOR EACH K VAL - WORKS

		for(int sub_array_idx = 0; sub_array_idx < k; sub_array_idx++) // Iterating For Each Subarray 0 - K
		{		
			Node* stack_base; // Initializing Stack Base
							  
			// For Each SubArray Place The Relevant Node Values In The Stack -> Sort The Stack -> Put Them Back In True Order
			
			Node* temp_base = malloc(sizeof(*temp_base)); // Initializing The Base Of The Stack Temporarily
			temp_base -> value = 0; 
			temp_base -> next = NULL;

			int sub_elem_idx;
			for(sub_elem_idx = 0; (sub_elem_idx * k + sub_array_idx) < size; sub_elem_idx++) // Incrementing Based On Sub Array Width And The Number Of The Sub Array
			{
																   // ADD THESE TO A STACK
				stack_push(temp_base, scanner(list, sub_elem_idx * k + sub_array_idx) -> value); // ADDING TO STACK
			}

			stack_base = temp_base -> next; // Removing and freeing dummy_head
			free(temp_base);


			bubble_sort_list(stack_base, sub_elem_idx, &stack_base); // Sorting The Stack

			for(int stack_idx = 0; (stack_idx * k + sub_array_idx) < size; stack_idx++)
			{
				scanner(list, (stack_idx * k + sub_array_idx)) -> value = scanner(stack_base, stack_idx) -> value;
			}
			free_list(stack_base);
		}
						   
	}	
	free(n_comp);
	return list;

}

/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
