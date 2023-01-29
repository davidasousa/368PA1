#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

long *Array_Load_From_File(char *filename, int *size);

int Array_Save_To_File(char *filename, long *array, int size);

void Array_Shellsort(long *array, int size, long *n_comp)
{
	for(int a = size - 1;  a >= 0; a--)
	{
		for(int j = a; j < size; j++)
		{
			long temp_r = *(array + j);
			int i = j;
			while(i >= a && *(array + i - a) > temp_r)
			{
				*(array + i) = *(array + i - a);
				i = i - a;	
			}
			*(array + i) = temp_r;	
		}
	}
}

