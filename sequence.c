#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

static long exponent(long base, long power)
{
	long final = base;
	for(int exp_idx = power; exp_idx > 1; exp_idx--)
		final = final * base;
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

static long tree_height(long n)
{
	long tree_t = 0;
	while(exponent(2, tree_t)) // Finding Max Possible Height Of The Tree
	{
		tree_t++;	
	}
	return tree_t;
}

static int seq_alloc(int n)
{
	return exponent(logg(2, n), 2);
}

long *Generate_2p3q_Seq(int n, int *seq_size)
{
	long* seq = malloc(sizeof(*seq));	
	return seq;
}

/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
