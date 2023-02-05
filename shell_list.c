#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

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
		int size = bytes / 8;
	}
	
	long* buffer = malloc(sizeof(*buffer) * size);
	fread(buffer, 8, size, fp);

	int buff_idx = 0;

	Node* head = malloc(sizeof(*head));
	head -> value = *(buffer + buff_idx);
	head -> next = NULL;

	for(buff_idx = 1; buff_idx < size - 1; buff_idx++)
		append_list(head, buffer[buff_idx]);	

	fclose(fp);
	free(buffer);

	return head;
}

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


/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
