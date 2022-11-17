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
void readAddress(FILE *outFile, list_t *list);

int main(int argc, char *argv[]){
    
	if(argc < ARGUMENTS + 1){
		fprintf(stderr, "Usage: %s input_file_name output_file_name\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	//open input file and out file 
	FILE *inFile = fopen(argv[INFILE], "r");
	FILE *outFile = fopen(argv[OUTFILE], "w");
	assert(inFile && outFile);
	
	// make a linked list
	list_t *list = makeEmptyList();
	assert(list->head == NULL);
	
	// store data from the input file into the linked list
	buildLinkedList(inFile, list);
	fclose(inFile);

	//read the address(es) from stdin and print the matching records to the output file
	readAddress(outFile, list);
	fclose(outFile);

	//free memories allocated for the linked list
	freeList(list);		
}

//read the address(es) from stdin and print out the matching records to the out file 
//by calling searchFootpath method
void
readAddress(FILE *outFile, list_t *list){
	char address[MAX_CHAR + 1];
	while(scanf("%[^\n]\n", address) == 1){	
		fprintf(outFile, "%s\n", address);			
		searchFootpath(outFile, list, address);
	}
}




