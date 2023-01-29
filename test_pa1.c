#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "miniunit.h"
#include "sequence.h"
#include "shell_array.h"
#include "shell_list.h"
#include "sequence.c"
#include "list_functions.c"
#include "shell_array.c"

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

static int _test_array_sort() {
	mu_start();
	//────────────────────
	long solo_array = 5;
	array_sort(&solo_array, 1);
	mu_check(solo_array == 5);

	long array2[3] = {5,1,4};

	array_sort(array2, 3);

	mu_check(*(array2) == 1);
	mu_check(*(array2 + 1) == 4);
	mu_check(*(array2 + 2) == 5);

	long array3[10] = {5,1,4,-1,0,0,100,10000,-10000,17};

	array_sort(array3, 10);

	mu_check(*(array3) == -10000);
	mu_check(*(array3 + 1) == -1);
	mu_check(*(array3 + 2) == 0);
	mu_check(*(array3 + 3) == 0);
	mu_check(*(array3 + 4) == 1);
	mu_check(*(array3 + 5) == 4);
	mu_check(*(array3 + 6) == 5);
	mu_check(*(array3 + 7) == 17);
	mu_check(*(array3 + 8) == 100);
	mu_check(*(array3 + 9) == 10000);
	//────────────────────
	mu_end();
}

static int _test_list_find_sentinal() {
	mu_start();
	//────────────────────
	Node* new_node = malloc(sizeof(*new_node));
	new_node -> next = NULL;
	new_node -> value = 9;

	append_list(new_node, 7);
	append_list(new_node, 2);
	
	Node* new_head = NULL;
	find_sentinal(new_node, &new_head, 3);

	mu_check(new_head -> value == 7);
	mu_check(new_head -> next -> value == 2);
	mu_check(new_head -> next -> next -> value == 9);

	free_list(new_head);

	//────────────────────
	mu_end();
}

static int _test_list_find_sentinal_2() {
	mu_start();
	//────────────────────
	Node* new_node = malloc(sizeof(*new_node));
	new_node -> next = NULL;
	new_node -> value = 1;

	append_list(new_node, 2);
	append_list(new_node, 3);
	
	Node* new_head = NULL;
	find_sentinal(new_node, &new_head, 3);

	mu_check(new_head -> value == 1);
	mu_check(new_head -> next -> value == 2);
	mu_check(new_head -> next -> next -> value == 3);

	free_list(new_head);
	//────────────────────
	mu_end();
}

static int _test_list_find_sentinal_3() {
	mu_start();
	//────────────────────
	Node* new_node = malloc(sizeof(*new_node));
	new_node -> next = NULL;
	new_node -> value = 8;

	append_list(new_node, 1);
	append_list(new_node, 3);
	
	Node* new_head = NULL;
	find_sentinal(new_node, &new_head, 3);

	mu_check(new_head -> value == 1);
	mu_check(new_head -> next -> value == 3);
	mu_check(new_head -> next -> next -> value == 8);

	free_list(new_head);
	//────────────────────
	mu_end();
}

static int _test_list_find_sentinal_4() {
	mu_start();
	//────────────────────
	Node* new_node = malloc(sizeof(*new_node));
	new_node -> next = NULL;
	new_node -> value = 8;

	append_list(new_node, 1);
	append_list(new_node, 3);
	append_list(new_node, 6);
	
	Node* new_head = NULL;
	find_sentinal(new_node, &new_head, 4);

	mu_check(new_head -> value == 1);
	mu_check(new_head -> next -> value == 3);
	mu_check(new_head -> next -> next -> value == 6);
	mu_check(new_head -> next -> next -> next -> value == 8);

	free_list(new_head);
	//────────────────────
	mu_end();
}

static int _test_list_find_sentinal_5() {
	mu_start();
	//────────────────────
	Node* new_node = malloc(sizeof(*new_node));
	new_node -> next = NULL;
	new_node -> value = 2;

	append_list(new_node, 9);
	append_list(new_node, 0);
	append_list(new_node, 1);
	
	Node* new_head = NULL;
	find_sentinal(new_node, &new_head, 4);

	mu_check(new_head -> value == 2);
	mu_check(new_head -> next -> value == 0);
	mu_check(new_head -> next -> next -> value == 1);
	mu_check(new_head -> next -> next -> next -> value == 9);

	free_list(new_head);
	//────────────────────
	mu_end();
}

static int _test_list_find_sentinal_6() {
	mu_start();
	//────────────────────
	Node* new_node = malloc(sizeof(*new_node));
	new_node -> next = NULL;
	new_node -> value = 3;

	append_list(new_node, 1);
	append_list(new_node, 3);
	append_list(new_node, 4);
	append_list(new_node, 7);
	append_list(new_node, 8);
	append_list(new_node, -1);
	append_list(new_node, 5);
	
	Node* new_head = NULL;
	find_sentinal(new_node, &new_head, 7);

	mu_check(new_head -> value == 1);
	mu_check(new_head -> next -> next -> next -> next -> next -> next -> value == 8);

	free_list(new_head);
	//────────────────────
	mu_end();
}

static int _test_bubble_sort_list() {
	mu_start();
	//────────────────────
	Node* new_node = malloc(sizeof(*new_node));
	new_node -> value = 8;
	new_node -> next = NULL;

	append_list(new_node, 3);
	append_list(new_node, 1);

	Node* new_head = NULL;
	find_sentinal(new_node, &new_head, 3);
	long sentinal = new_head -> next -> next -> value;

	mu_check(sentinal == 8);
	free_list(new_head);
	
	//────────────────────
	mu_end();
}

static int _test_sort_list_size2() {
	mu_start();
	
	Node* new_node = malloc(sizeof(*new_node));
	new_node -> next = NULL;
	new_node -> value = 2;

	append_list(new_node, 0);

	Node* new_head = NULL;

	sort_list_size2(new_node, &new_head);
	
	mu_check(new_head -> value == 0);
	mu_check(new_head -> next -> value == 2);

	free_list(new_head);
	mu_end();
}

static int _test_exponent() {
	mu_start();
	//────────────────────
	long test1 = exponent(2,0);
	mu_check(test1 == 1);

	long test2 = exponent(2,2);
	mu_check(test2 == 4);

	long test3 = exponent(3,5);
	mu_check(test3 == 243);

	long test4 = exponent(2,1);
	mu_check(test4 == 2);
	
	//────────────────────
	mu_end();
}

static int _test_logg() {
	mu_start();
	//────────────────────
	long test1 = logg(2,8);
	mu_check(test1 == 4);

	long test2 = logg(2,7);
	mu_check(test2 == 3);

	long test3 = logg(2,9);
	mu_check(test3 == 4);

	long test4 = logg(2,3);
	mu_check(test4 == 2);
	
	//────────────────────
	mu_end();
}

static int _test_tree_height() {
	mu_start();
	//────────────────────
	long t1 = tree_height(1);
	mu_check(t1 == 1);

	long t2 = tree_height(25);
	mu_check(t2 == 5);

	long t3 = tree_height(3);
	mu_check(t3 == 2);

	long t4 = tree_height(4);
	mu_check(t4 == 3);
	
	//────────────────────
	mu_end();
}

static int _test_gen_seq() {
	mu_start();
	//────────────────────
		
	int estimate = exponent(logg(2,97),2);
	long* test_seq1 = Generate_2p3q_Seq(97, &estimate);
	mu_check(estimate == 20);
	
	printf("\n");
	for(int i = 0; i < estimate; i++)
	{
		printf("%ld -> ", *(test_seq1 + i));
	}
	printf("\n\n");

	free(test_seq1);
	
	//────────────────────
	mu_end();
}

static int _test_array_shell() {
	mu_start();
	//────────────────────
	long test1[7] = {1,-1,2,3,-2,10,-10};
	long size = 7; 

	int estimate1 = exponent(logg(2,9),2);
	long* test_seq1 = Generate_2p3q_Seq(9, &estimate1);
	free(test_seq1);

	Array_Shellsort(test1, size, test_seq1);
	mu_check(*(test1) == -10);
	mu_check(*(test1 + 1) == -2);
	mu_check(*(test1 + 2) == -1);
	mu_check(*(test1 + 3) == 1);
	mu_check(*(test1 + 4) == 2);
	mu_check(*(test1 + 5) == 3);
	mu_check(*(test1 + 6) == 10);
		
	//────────────────────
	mu_end();
}

int main(int argc, char* argv[]) {
	
	mu_run(_test_array_sort);
	mu_run(_test_list_find_sentinal);
	mu_run(_test_list_find_sentinal_2);
	mu_run(_test_list_find_sentinal_3);
	mu_run(_test_list_find_sentinal_4);
	mu_run(_test_list_find_sentinal_5);
	mu_run(_test_list_find_sentinal_6);
	mu_run(_test_sort_list_size2);
	mu_run(_test_bubble_sort_list);
	mu_run(_test_exponent);
	mu_run(_test_logg);
	mu_run(_test_tree_height);
	mu_run(_test_gen_seq);
	mu_run(_test_array_shell);


	return EXIT_SUCCESS;
}
/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */

