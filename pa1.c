#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include "sequence.h"
#include "shell_array.h"
#include "shell_list.h"
#include <limits.h>

static void free_list(Node* head)
{
	if(head -> next != NULL)
	{
		free_list(head -> next);
	}
	free(head);
}

int main(int argc, char* argv[]) {

	if(argc > 3)
	{
		if(strcmp(argv[1],"-a") == 0) // ARRAY HAS BEEN CHOSEN
		{
			char* input_file = argv[2];
			char* output_file = argv[3];
			
			int size = 0;
			long comp = 0;

			long* array_file = Array_Load_From_File(input_file, &size);
			if(array_file == NULL)
				return EXIT_FAILURE;

			Array_Shellsort(array_file, size, &comp);

			int num_longs = Array_Save_To_File(output_file, array_file, size); // Valgrind Seg Fault Here

			free(array_file);

			printf("%ld\n\n./pa1 -a %s %s\n", comp, input_file, output_file);
		}
		if(strcmp(argv[1],"-l") == 0) // ARRAY HAS BEEN CHOSEN
		{
			char* input_file = argv[2];
			char* output_file = argv[3];

			Node* list_file = List_Load_From_File(input_file);	
			
			long comp = 0;
			Node* head = List_Shellsort(list_file, &comp);

			int elems = List_Save_To_File(output_file, head);
				
			free_list(head);

			printf("%ld\n\n./pa1 -l %s %s\n", comp, input_file, output_file);	
		}
	}
			
	
	return EXIT_SUCCESS;
}
/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
