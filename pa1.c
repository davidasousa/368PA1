#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include <limits.h>
#include "sequence.h"
#include "shell_array.h"
#include "shell_list.h"

static void free_list(Node* head) // Iteratively
{
    Node* curr = head;

    while(curr != NULL)
    {
        Node* temp = curr;
        curr = curr -> next;
        free(temp);
    }
}

int main(int argc, char* argv[]) {

	if(argc == 4)
	{
		if(strcmp(argv[1],"-a") == 0) // ARRAY HAS BEEN CHOSEN
		{
			char* input_file = argv[2];
			char* output_file = argv[3];
			
			int size = 0;
			long comp = 0;

			long* array = Array_Load_From_File(input_file, &size);
			if(array == NULL)
				return EXIT_FAILURE;

			Array_Shellsort(array, size, &comp);

			int num_longs = Array_Save_To_File(output_file, array, size);
            if(num_longs != size)
            {
                free(array);
                return EXIT_FAILURE;
            }

            fprintf(stdout, "%ld\n", comp);

			free(array);
            return EXIT_SUCCESS;

		}
		if(strcmp(argv[1],"-l") == 0) // ARRAY HAS BEEN CHOSEN
		{
            char* input_file = argv[2];
            char* output_file = argv[3];

            Node* list = List_Load_From_File(input_file);
            if(list == NULL)
                return EXIT_FAILURE;

            long comp = 0;
            list = List_Shellsort(list, &comp);

            int num_longs = List_Save_To_File(output_file, list);
            if(num_longs == -1)
            {
                free_list(list);
                return EXIT_FAILURE;
            }

            fprintf(stdout, "%ld\n", comp);
            free_list(list);
            return EXIT_SUCCESS;
		}
	}
			
	
	return EXIT_FAILURE;
}
/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
