/* COMP20003
 * Yelp Database
 * Author: <Justin Bugeja> <jbugeja> <758397>
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include "dictionary.h"

//Creates the dictionary struct node and returns its address
dict_t *createDict() {
	dict_t *pd = malloc(sizeof(dict_t));
	assert(pd);
	pd->head = NULL;
	return pd;
}


//Create a seperate record for the data
record_t *createRec(char *name, char *data) {
	
	record_t *pr = malloc(sizeof(record_t));
	pr->left = NULL;
	pr->right = NULL;
	pr->name = strdup(name);
	pr->data = strdup(data);
	
	return pr;
}

/* Change the address of the first record to point at the 
second record */
void changeAddress(record_t **p1, record_t *p2) {
 *p1 = p2;
}

//Reads in a record and places it in the dictionary
void insert( dict_t *pd, record_t *x) {
	//Checks if first element
	int compare;
	if(pd->head == NULL) {
		changeAddress(&pd->head, x);
		
	} else {
		
		record_t *pr = pd->head;
		
		//While not at the end of the dictionary
		while (1) {
			compare = strcmp(x->name, pr->name);
			if (compare > 0) {
				if(pr->right == NULL) {
					changeAddress(&pr->right, x);
					return;
				}
				//Point to next node
				pr = pr->right;
			//If left or equal
			} else if (compare <= 0){
				if(pr->left == NULL) {
					changeAddress(&pr->left, x);;
					return;
				}
				//Point to next node
				pr = pr->left;
			}
		}
	}
}

//Searches the dictionary for a given key
void search(char *name, dict_t *pd) {
	int compare, cmp = 0, found = 0;
	
	if(pd->head == NULL) {
		printf("no tree found");
		exit(EXIT_FAILURE);
		
	} else {
		
		//Point to the head of the tree
		record_t *pr = pd->head;
		
		//While not at the end of the tree
		while (1) {
			compare = strcmp(name, pr->name);
			cmp++;
			//If right
			if (compare > 0) {
				if(pr->right == NULL) {
					break;
				}
				//Point to next node
				pr = pr->right;
				//If left or equal
			} else if(compare < 0) {
				if (pr->left == NULL) {
					break;
				}
				//Point to next node
				pr = pr->left;
				//If found
			} else if(compare == 0) {
				printToFile(pr, cmp); 
				found++;
				if (pr->left == NULL) {
					break;
				}
				//Point to next node
				pr = pr->left;
			} else {
				printf("error in strcmp\n");
			}
		}
	} 
	//If the record wasn't found print not found
	if (!found) {
		printNotFound(name);
	}
	printf("%s --> %d\n", name, cmp);
}

//Print not found to file
void printNotFound(char *name) {
	FILE *fp;
	fp=fopen(OUTPUTFILE,"ab");
	fprintf(fp, "%s --> NOTFOUND\n\n", name);
	fclose(fp);
}

//Print the key and data to file
void printToFile(record_t *pr, int cmp) {
	FILE *fp;
	fp=fopen(OUTPUTFILE,"ab");
	fprintf(fp, "%s --> %s\n", pr->name, pr->data);
	fclose(fp);
}
	
//Output the key and number of comparisons
void printKey(record_t *node, int cmp) {
	printf("%s --> %d\n", node->name, cmp);
}

//Free the allocated memory
void free_tree(record_t *node) {
	if (node == NULL) {
		return;
	}
	//Post-order traversal
	free_tree(node->left);
	free_tree(node->right);
	
	//Free node elements then free node
	free(node->name);
	free(node->data);
	free(node);
}