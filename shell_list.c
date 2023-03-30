#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "shell_list.h"
#include "sequence.h"

static Node* insert_to_list(Node* head_node, Node** prev_node, Node* new_node)
{
    if(head_node == NULL)
    {
        head_node = new_node;
        *prev_node = head_node;
    }
    else
    {
        (*prev_node) -> next = new_node;
        (*prev_node) = new_node;
    }
    return head_node;
}

Node* List_Load_From_File(char* filename)
{
    FILE* fp = fopen(filename, "r");
    if(fp == NULL)
        return NULL;

    long num;
    Node* head_node = NULL;
    Node* prev_node = NULL;

    while(!feof(fp))
    {
        if(fread(&num, sizeof(num), 1, fp))
        {
            Node* new_node = malloc(sizeof(*new_node));
            *new_node = (Node){.value = num, .next = NULL}; 
            head_node = insert_to_list(head_node, &prev_node, new_node);
        }
    }
    fclose(fp);
    return head_node;
}

Node* List_Shellsort(Node* list, long* n_comp)
{
    // Getting The Size Of The List
    int size = 0;
    Node* temp_head = list;
    while(temp_head != NULL)
    {
        temp_head = temp_head -> next;
        size++;
    }

    //Getting The Sequence

    int seq_size;
    long* seq = Generate_2p3q_Seq(size, &seq_size);

    //Sorting
    
    // Sorting One Shell Works
    
    int k = 3;


    // Starting Values
    
    //Node* right_prev_start = list;
    Node* left_prev = NULL;
    Node* left = list;
    Node* right_prev = list;
    Node* right = right_prev -> next;

    Node* head = list;

    // want to check if no swaps happend

    int swap_count = 1;
    while(swap_count != 0)
    {
        swap_count = 0;

        left_prev = NULL;
        right_prev = head;

        for(int find_idx = 0; find_idx < k - 1; find_idx++)
            right_prev = right_prev -> next; // Finding The First Previous Node To Right
                                                         
        left = head;
        right = right_prev -> next;

        while(right != NULL)
        {
            // Swapping 
            
            if(left -> value > right -> value)
            {
                swap_count++;
                Node* left_next = left -> next;
                Node* right_next = right -> next;

                if(left_prev == NULL)
                {
                    right -> next = left_next;
                    right_prev -> next = left;
                    left -> next = right_next;

                    head = right;
                }
                else 
                {
                    left_prev -> next = right;
                    right -> next = left_next;

                    right_prev -> next = left;
                    left -> next = right_next;
                }
                Node* temp = right;
                right = left;
                left = temp;
            }
            
            // Iterating Right And Left One Time 
            /*            
            left_prev = right_prev;
            for(int find_idx = 0; find_idx < k; find_idx++)
                right_prev = right_prev -> next;
            right = right_prev -> next;
            left = left_prev -> next; 
            */

            // figure out how to sort all shell in teh same loop

            right_prev = right;
            right = right -> next;
            left_prev = left;
            left = left -> next;
        }
    }


    free(seq);
    return head;
}

/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
