#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

static void array_sort(int* array, int num_elems)
{
	for(int temp_idx = 1; temp_idx < num_elems; temp_idx++)
	{
		long temp = *(array + temp_idx);
		int comp_idx = temp_idx;
		while(comp_idx > 0 && *(array + comp_idx - 1) > temp)
		{
			*(array + comp_idx) = *(array + comp_idx - 1);
			comp_idx = comp_idx - 1;
		}
		*(array + comp_idx) = temp;
	}
}

/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
