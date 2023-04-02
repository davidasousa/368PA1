#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "shell_array.h"
#include "sequence.h"

long *Array_Load_From_File(char *filename, int *size)
{
	FILE* fp = fopen(filename, "r");
	int bytes = 0;

	if(fp == NULL)
	{
		size = 0;
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
		*size = bytes / 8;
	}

	long* values = malloc(sizeof(*values) * (*size));
	fread(values, sizeof(long), *size, fp);
	fclose(fp);

	return values;
}

int Array_Save_To_File(char *filename, long *array, int size) // IF ARRAY IS NULL OR SIZE IS 0 THAN CREATE AN EMPTY FILE
{
	FILE *fp = fopen(filename, "w");
	if(array == NULL || size == 0 || fp == NULL)
	{
		fclose(fp);
        return 0;
	}
    int tot_written = fwrite(array, sizeof(*array), size, fp);

	fclose(fp);
	return tot_written;
}


void Array_Shellsort(long *array, int size, long *n_comp)
{
    // Size is the total number of elements being sorted
    // n_comp is a running total of all of the comparisons
    // array is the array of elements

    // First Get The Sequence

    int seq_size;
    long* seq = Generate_2p3q_Seq(size, &seq_size);

    for(int k = seq_size - 1; k > -1; k--)
    {
        long k_val = seq[k];
        for(int j = k_val; j < size; j++)
        {
            long temp_r = *(array + j);
            int i = j;
            while(i >= k_val && *(array + i - k_val) > temp_r)
            {
                array[i] = array[i - k_val];
                i = i - k_val;
                *n_comp += 1;
            }
            *(array + i) = temp_r;
        }
    }
    free(seq);
}
