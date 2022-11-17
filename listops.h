#ifndef _LISTOPS_H_
#define _LISTOPS_H_

#include <stdio.h>
#include <stdlib.h>

#include "data.h"

typedef struct node node_t;

struct node {
	footpath_t *footpath;
	node_t *next;
};

typedef struct {
	node_t *head;
	node_t *foot;
} list_t;


//make an empty linked list with head and foot set to NULL
list_t *makeEmptyList(void);

//add all footpath data to the tail of the linked list
void buildLinkedList(FILE *inFile, list_t *list);

void searchFootpath(FILE *outFile, list_t *list, char *address);

int getDataNum(list_t *list);

void sortArray(list_t *list, node_t *sorted_array[], int data_num);

void arrayBubbleSort(node_t *sorted_array[], int data_num);

void searchCloestGrade1in(FILE *outFile, node_t *sorted_array[],int data_num, double grade1in);

void freeList(list_t *list);

#endif


