#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "sequence.h"

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

static long tree_height(int n)
{
	long height = 0;

	while(exponent(2, height) <= n)
	{
		height++;
	}
	
	return height;
}

static void array_sort(long* array, int num_elems)
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

long *Generate_2p3q_Seq(int n, int *seq_size) // FIX EXP AND LOG APPROX FOR SIZE OF ARRAY
{
    long* seq;

    if(n == 0 || n == 1)
    {
        *seq_size = 0;
        seq = malloc(sizeof(*seq * *seq_size));
        return seq; 
    }

	*seq_size = exponent(logg(2,n),2); // PASS BY ADDRESS
	seq = malloc(sizeof(*seq) * (*seq_size));		
	if(seq != NULL)
	{
		long height = tree_height(n);
		int elem_num = 0;

		for(int tree_idx = 0; tree_idx <= height; tree_idx++)
		{
			long left = exponent(2, tree_idx);
			for(int exp_idx = tree_idx; exp_idx >= 0; exp_idx--)
			{
				if(left < n)
				{
					*(seq + elem_num++) = left;
				}
				left = 3 * (left / 2);
			}
		}	
		*seq_size = elem_num;
		seq = realloc(seq,sizeof(*seq) * elem_num);
		array_sort(seq, elem_num);
	}
	else
	{
		*seq_size = 0;
	}
	return seq;
}

/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
