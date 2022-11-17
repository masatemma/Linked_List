#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>

#include "listops.h"
#include "data.h"

//make an empty linked list with head and foot set to NULL
list_t 
*makeEmptyList(void){
    list_t *list;
    list = (list_t*)malloc(sizeof(*list));
    assert(list!=NULL);
    list->head = list->foot = NULL;
    return list;
}

//add all footpath data to the tail of the linked list
void
buildLinkedList(FILE *inFile, list_t *list){
    char line[MAX_LINE_LEN];
    assert(list!=NULL);
    assert(inFile != NULL);
    // takes the header line
    fscanf(inFile, "%[^\n] ", line);

    //reads footpath data and store them into linked list    
        footpath_t *newFootpath;
        node_t *newNode;
        while((newFootpath = readFootpath(inFile))){                                
            newNode = (node_t*)malloc(sizeof(*newNode));
            newNode->footpath = newFootpath;        
            newNode->next = NULL;
            
            if(list->foot == NULL){
                list->head = newNode;
                list->foot = newNode;  
            }
            else{
                list->foot->next = newNode;
                list->foot = newNode;    
            }           
        }   
        free(newFootpath);       
}

//search all footpath record with matching address
void 
searchFootpath(FILE *outFile, list_t *list, char *address){
   
    node_t *cur_head = list->head;
    footpath_t *cur_footpath;
    char cur_address[MAX_CHAR];
    int matched = 0;
    //search through the address for each footpath from the head of the linked list
    //and print out the matching recoard, else, print out NOTFOUND
    while(cur_head != NULL){
        cur_footpath = cur_head->footpath;
        strcpy(cur_address, cur_footpath->address);
        if(strcmp(cur_address, address) == 0){
            printToOutfile(outFile, cur_footpath);
            matched++;
        }
        cur_head = cur_head->next;
    }
    if(matched != 0){
        printf("%s --> %d\n", address, matched);
    }
    else{
        printf("%s --> NOTFOUND\n", address);
    }
    free(cur_head);  
}

//free memories allocated for the linked list
void freeList(list_t *list){
    node_t *new_head = list->head;
    node_t *prev_node;
    footpath_t *prev_footpath;
    while(new_head != NULL){
        prev_node = new_head;
        prev_footpath = new_head->footpath;
        new_head = new_head->next;
        free(prev_footpath->address);
        free(prev_footpath->clue_sa);
        free(prev_footpath->asset_type);
        free(prev_footpath->segside);
        free(prev_footpath);
        free(prev_node);        
    }
   
    //free(new_head);
    free(list);
    
}
//return the size of the linked list 
int 
getDataNum(list_t *list){
    int n=0;
    node_t *node = list->head;
    while(node != NULL){
        n++;
        node = node->next;
    }
    free(node);
    
    return n;
}


//assign pointer of each node into the sorted_array and call arrayBubbleSort
// to sort the array 
void 
sortArray(list_t *list, node_t *sorted_array[], int data_num){

    node_t *cur_node = list->head;
    
    for(int i=0; i<data_num; i++){
        sorted_array[i] = cur_node;
        cur_node = cur_node->next;
    }
    
    //call the method to sort the array of pointers to each node
    arrayBubbleSort(sorted_array, data_num);
    free(cur_node);
}

//sort the array based on the value of grade1in in ascending order using
//bubble sort algorithm 
void
arrayBubbleSort(node_t *sorted_array[], int data_num){
    node_t *temp;
    for(int i=0; i<data_num; i++){
        for(int j=0; j<data_num - 1; j++){
            if(sorted_array[j]->footpath->grade1in > 
                sorted_array[j+1]->footpath->grade1in){
                    temp = sorted_array[j];
                    sorted_array[j] = sorted_array[j+1];
                    sorted_array[j+1] = temp;
            }
        }
    }             
}

//using linear search to find the record with the closest grade1in value as 
//the input
void 
searchCloestGrade1in(FILE *outFile, node_t *sorted_array[],int data_num, double grade1in){
    double cloest_abs = fabs(sorted_array[0]->footpath->grade1in - grade1in);
    int cloest_index = 0;

    for(int i=1; i<data_num;i++){
        double new_abs = fabs(sorted_array[i]->footpath->grade1in - grade1in);
        if(cloest_abs > new_abs){
            cloest_abs = new_abs;
            cloest_index = i;
        }
        else if(cloest_abs < new_abs){
            break;
        }
    }

    char converted_grade1in[MAX_FIGURES];
   
    //convert read grade1in into string and process it in order to print out
    //the value without trailing zeros after the decimal point
    int figures_num = snprintf(converted_grade1in, MAX_FIGURES, "%lf", grade1in);
    stringProcess(converted_grade1in, figures_num);

    printToOutfile(outFile, sorted_array[cloest_index]->footpath);
    printf("%s --> %.1lf\n", converted_grade1in, sorted_array[cloest_index]->footpath->grade1in); 
}

