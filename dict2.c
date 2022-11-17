#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

#include "listops.h"
#include "data.h"

//definitions of constants
#define INFILE 2
#define OUTFILE 3
#define ARGUMENTS 3
#define FIGURE_NUM 4

//function prototypes
void readGrade1in(FILE *outFile, node_t *sorted_array[], int data_num);
void printSortedArray(FILE *outFile, node_t *sorted_array[], int data_num);
int main(int argc, char *argv[]){
    
	if(argc < ARGUMENTS + 1){
		fprintf(stderr, "Usage: %s input_file_name output_file_name\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	//open input file and output file 
	FILE *inFile = fopen(argv[INFILE], "r");
	FILE *outFile = fopen(argv[OUTFILE], "w");
	assert(inFile && outFile);
	
	
	// make a linked list
	list_t *list = makeEmptyList();
	assert(list->head == NULL);

	// store data into the linked list
	buildLinkedList(inFile, list);
	fclose(inFile);
	assert(list->head != NULL);
	
	//create a sorted array of pointers to each node based on the grade1in attribute;
	int data_num = getDataNum(list);
	node_t *sorted_array[data_num];
	sortArray(list, sorted_array, data_num);
	

	//read grade1in value(s) from queryfile and find the record with the closest grade1in value
	readGrade1in(outFile, sorted_array, data_num); 
	fclose(outFile);

	//free memories allocated for the linked list
	freeList(list);	

}

//read grade1in from queryfile and find the record with the closest grade1in value
void readGrade1in(FILE *outFile, node_t *sorted_array[], int data_num){
	double grade1in;
	char converted_grade1in[MAX_FIGURES];
	int figures_num; 
	
	while(scanf("%lf\n", &grade1in) == 1){	

		//convert read grade1in into string and process it in order to print out
		//the value without trailing zeros after the decimal point
		figures_num = snprintf(converted_grade1in, MAX_FIGURES, "%lf", grade1in);	
		stringProcess(converted_grade1in, figures_num);

		fprintf(outFile, "%s\n", converted_grade1in);			
		searchCloestGrade1in(outFile, sorted_array, data_num, grade1in);
	}
}




