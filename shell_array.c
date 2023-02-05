#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

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
	size_t readings = fread(values, 8, *size, fp);
	fclose(fp);

	return values;
}

int Array_Save_To_File(char *filename, long *array, int size)
{
	FILE *fp = fopen(filename, "w");
	if(array == NULL || size == 0)
	{
		fclose(fp);
	}
	fwrite(array, 8, size, fp);
	fclose(fp);
	return size;
}

void Array_Shellsort(long *array, int size, long *n_comp)
{
	int num_ks = exponent(logg(2,size),2);
	n_comp = Generate_2p3q_Seq(size, &num_ks);

	for(int k_idx = num_ks - 1;  k_idx >= 0; k_idx--)
	{
		for(int j = k_idx; j < size; j++)
		{
			long temp_r = *(array + j);
			int i = j;
			while(i >= k_idx && *(array + i - k_idx) > temp_r) // CONSIDER Break To SAve Time
			{
				*(array + i) = *(array + i - k_idx);
				i = i - k_idx;	
			}
			*(array + i) = temp_r;	
		}
	}
	free(n_comp);
}
