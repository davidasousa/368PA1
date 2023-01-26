#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "miniunit.h"
#include "sequence.h"
#include "shell_array.h"
#include "shell_list.h"
#include "array_functions.c"
#include "list_functions.c"

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

static void free_list(Node* head)
{
	if(head -> next != NULL)
	{
		free_list(head -> next);
	}
	free(head);
}

// TESTS FOR BASIC INSERTION SORT - SEEMING WORKING AS OF 1/23 - 12PM

static int _test_array_sort_1() {
	mu_start();
	//────────────────────
	int solo_array = 5;

	array_sort(&solo_array, 1);

	mu_check(solo_array == 5);
	//────────────────────
	mu_end();
}

static int _test_array_sort_3() {
	mu_start();
	//────────────────────
	int array[3] = {5,1,4};

	array_sort(array, 3);

	mu_check(*(array) == 1);
	mu_check(*(array + 1) == 4);
	mu_check(*(array + 2) == 5);

	//────────────────────
	mu_end();
}

static int _test_array_sort_10_neg() {
	mu_start();
	//────────────────────
	
	int array[10] = {5,1,4,-1,0,0,100,10000,-10000,17};

	array_sort(array, 10);

	mu_check(*(array) == -10000);
	mu_check(*(array + 1) == -1);
	mu_check(*(array + 2) == 0);
	mu_check(*(array + 3) == 0);
	mu_check(*(array + 4) == 1);
	mu_check(*(array + 5) == 4);
	mu_check(*(array + 6) == 5);
	mu_check(*(array + 7) == 17);
	mu_check(*(array + 8) == 100);
	mu_check(*(array + 9) == 10000);
	
	//────────────────────
	mu_end();
}

// TESTS FOR INSERT NODE TO LIST - APPEND AND FREE WORKING
static int _test_insert() {
	mu_start();
	//────────────────────
	
	Node* new_node = malloc(sizeof(*new_node));
	new_node -> next = NULL;
	new_node -> value = 1;

	append_list(new_node, 5);

	mu_check(new_node -> value == 1);
	mu_check(new_node -> next -> value == 5);

	free_list(new_node);

	//────────────────────
	mu_end();
}

static int _test_node_finder() {
	mu_start();
	//────────────────────
	
	Node* new_node = malloc(sizeof(*new_node));
	new_node -> next = NULL;
	new_node -> value = 0;

	append_list(new_node, 1);
	append_list(new_node, 2);
	append_list(new_node, 3);
	append_list(new_node, 6);
	append_list(new_node, 4);
	
	mu_check((node_finder(new_node, 3)) -> value == 3);
	mu_check((node_finder(new_node, 4)) -> value == 6);
	mu_check((node_finder(new_node, 5)) -> value == 4);

	free_list(new_node);
	
	//────────────────────
	mu_end();
}

static int _test_swap_nodes_2() { // WHEN USING A LL OF 2 NODES THE HEAD NODE IS LOST, requires a third dummy node at the beginning
	mu_start();
	//────────────────────
	
	Node* dummy_node = malloc(sizeof(*dummy_node));
	dummy_node -> next = NULL;
	dummy_node -> value = -2;

	append_list(dummy_node, 1);
	append_list(dummy_node, 2);

	swap_adj_nodes(dummy_node);

	free_list(dummy_node);
		
	//────────────────────
	mu_end();
}

static int _test_swap_nodes_4() {
	mu_start();
	//────────────────────
	Node* new_node = malloc(sizeof(*new_node));
	new_node -> next = NULL;
	new_node -> value = 1;

	append_list(new_node, 2);
	append_list(new_node, 3);
	append_list(new_node, 4);

	swap_adj_nodes(new_node);

	mu_check(new_node -> value = 1);
	mu_check(new_node -> next -> value = 3);
	mu_check(new_node -> next -> next -> value = 2);
	mu_check(new_node -> next -> next -> next -> value = 4);
	
	free_list(new_node);
	//────────────────────
	mu_end();
}

static int _test_list_sort() {
	mu_start();
	//────────────────────
	Node* new_node = malloc(sizeof(*new_node));
	new_node -> next = NULL;
	new_node -> value = 1;

	append_list(new_node, 2);
	append_list(new_node, 3);
	append_list(new_node, 4);

	mu_check(new_node -> value = 1);
	mu_check(new_node -> next -> value = 2);
	mu_check(new_node -> next -> next -> value = 3);
	mu_check(new_node -> next -> next -> next -> value = 4);
	
	list_sort(new_node, 0);
	free_list(new_node);
	//────────────────────
	mu_end();
}

// TESTS FOR SWAPING ADJACENT ELEMENTS IN A LINKED LIST TO BE USED IN LIST SORT

int main(int argc, char* argv[]) {
	
	mu_run(_test_array_sort_1);
	mu_run(_test_array_sort_3);
	mu_run(_test_array_sort_10_neg);
	mu_run(_test_insert);
	mu_run(_test_node_finder);
	mu_run(_test_swap_nodes_2);
	mu_run(_test_swap_nodes_4);
	mu_run(_test_list_sort);

	return EXIT_SUCCESS;
}
/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
