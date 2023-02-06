#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include "sequence.h"
#include "shell_array.h"
#include "shell_list.h"

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

static void free_list(Node* head)
{
	if(head -> next != NULL)
	{
		free_list(head -> next);
	}
	free(head);
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

int main(int argc, char* argv[]) {

	if(argc > 3)
	{
		if(strcmp(argv[1],"-a") == 0) // ARRAY HAS BEEN CHOSEN
		{
			char* input_file = argv[2];
			char* output_file = argv[3];
			
			int size = 0;
			long* seq = 0;

			long* array_file = Array_Load_From_File(input_file, &size);
			int num_ks = exponent(logg(2,size),2);

			seq = Generate_2p3q_Seq(size, &num_ks);
			Array_Shellsort(array_file, size, seq);

			int num_longs = Array_Save_To_File(output_file, array_file, size); // Valgrind Seg Fault Here

			free(array_file);
			free(seq);

			printf("%d\n", num_longs);
		}
		if(strcmp(argv[1],"-l") == 0) // ARRAY HAS BEEN CHOSEN
		{
			char* input_file = argv[2];
			char* output_file = argv[3];

			Node* list_file = List_Load_From_File(input_file);	
			int size = list_size(list_file);
			
			long num_ks = 0;
			Node* head = List_Shellsort(list_file, &num_ks);

			int elems = List_Save_To_File(output_file, head);
				
			free_list(head);

			printf("%d\n", elems);
			
		}
	}
			
	
	return EXIT_SUCCESS;
}
/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
