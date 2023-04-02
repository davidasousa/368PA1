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

int List_Save_To_File(char* filename, Node* list)
{
    int writes = 0;
    FILE* fp = fopen(filename, "w");
    if(fp == NULL)
    {
        return -1;
    }
    while(list != NULL)
    {
        long num = list -> value;
        fwrite(&num, sizeof(long), 1, fp);
        list = list -> next;
        writes++;
    }
    fclose(fp);
    return writes;
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
    
    Node* left_prev = NULL;
    Node* left = list;
    Node* right_prev = list;
    Node* right = list;
    Node* head = list;

    Node* last_unsorted_node = NULL;

    for(int k_idx = seq_size; k_idx > 0; k_idx--)
    {
        long k = seq[k_idx - 1]; 

        if(k == 1)
        { 
            right = head -> next;
            left = head;
            left_prev = NULL;

            while(right != NULL)
            {
                if(right == last_unsorted_node)
                    break;

                *n_comp = *n_comp + 1;
                if(left -> value > right -> value)
                {
                    last_unsorted_node = right;
                    Node* right_next = right -> next;
                    if(left_prev == NULL)
                    {
                        right -> next = left;
                        left -> next = right_next;
                    }
                    else
                    {
                        left_prev -> next = right;
                        right -> next = left;
                        left -> next = right_next;
                    }
                }        
                left_prev = left;
                left = right;
                right = right -> next;
            }
        }
        else
        {

            int swap_count = 1;
            while(swap_count != 0)
            {
                swap_count = 0;

                left_prev = NULL;
                right_prev = head;

                for(int find_idx = 0; find_idx < k - 1; find_idx++)
                    right_prev = right_prev -> next;
                                                                 
                left = head;
                right = right_prev -> next;

                while(right != NULL)
                {
                    if(right == last_unsorted_node)
                        break;

                    *n_comp = *n_comp + 1;
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

                        last_unsorted_node = left;
                    }
                    right_prev = right;
                    right = right -> next;
                    left_prev = left;
                    left = left -> next;
                }
                if(k * 3 <= seq[seq_size - 1])
                    break;
            } 
        }
    }
    free(seq);
    return head;
}

/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
