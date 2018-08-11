/* COMP20003
 * Yelp Database
 * Author: <Justin Bugeja> <jbugeja> <758397>
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include "dictionary.h"

//Main program
int main(int argc, char *argv[]) {
	char *filename, *filekeysname;
	FILE *file, *filekeys;
	char buffer1[NAME_SIZE+1] = {0}, buffer2[DATA_SIZE+4] = {0}, c;
	dict_t *dict;
	int i=0, j=0, buffer=1;
	
	//Return error if no dictionary or key search files
	if (argc != 3){
		printf("ERROR\n");
		exit(EXIT_FAILURE);
	}
	filename = argv[1];
	//Return error if dictionary file cannot be opened
	if ( (file = fopen(filename, "r")) == NULL ) {
		printf("ERROR\n\n");
		exit(EXIT_FAILURE);
	}
	
	//Create the dictionary and return error if not created
	printf("Creating dictionary...\n");
	if ((dict = createDict()) == NULL) {
		printf("ERROR in creating dictionary\n\n");
		exit(EXIT_FAILURE);
	}
	printf("Empty dictionary created\n");
	
	
	//Read in from a file
	while ((c = fgetc(file)) != EOF) {
		if (c == DELIMINATOR) {
			//Switch buffer
			buffer = 2;
			i = 0;
			//Clear buffer
			memset(buffer2, 0, sizeof(buffer2));
			continue;
			/* Continue so character isn't read into buffer*/
		}
		if (buffer == 1) {
			buffer1[i] = c;
			i++;
		} else if (buffer == 2) {
			buffer2[j] = c;
			j++;
		}
		if (c == NEW_LINE) {
			//Switch buffer
			buffer = 1;
			//Insert record into dictionary
			insert(dict, createRec(buffer1, buffer2));
			j = 0;
			//Clear buffer
			memset(buffer1, 0, sizeof(buffer1));
		}	
    }
	fclose(file);
	
	printf("Successfully filled dictionary\n");
	
	filekeysname = argv[2];
	//Open the keys file
	if ( (filekeys = fopen(filekeysname, "r")) == NULL ) {
		printf("ERROR\n\n");
		exit(EXIT_FAILURE);
	}
	//If output file if already created then remove it
	if( access( OUTPUTFILE, F_OK ) != -1 ) {
    	if (remove( "output.txt" )==-1) {
    		printf("ERROR\n\n");
    		exit(EXIT_FAILURE);
    	} else {
    		printf("~Previous output file deleted\n");
    	}
    }
    //Read keys file
	while ((c = fgetc(filekeys)) != EOF) {
		if (c == NEW_LINE) {
			//Search for the key in the dictionary
			search(buffer1, dict);
			i = 0;
			//Clear the buffer to read next key
			memset(buffer1, 0, sizeof(buffer1));
			continue;
		}
		buffer1[i++] = c;
	}
	fclose(filekeys);
	
	//Free tree from memory
	free_tree(dict->head);
	free(dict);
	
	return 0;
}