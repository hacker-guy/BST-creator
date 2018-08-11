/* COMP20003
 * Yelp Database
 * Author: <Justin Bugeja> <jbugeja> <758397>
 */

#ifndef _DICTIONARY_H_
#define NAME_SIZE 64
#define DATA_SIZE 1465
#define NEW_LINE '\n'
#define DELIMINATOR ','
#define OUTPUTFILE "output.txt"
#define _DICTIONARY_H_

typedef struct record_t record_t;

//Record structure
struct record_t {
	char *name;
	char *data;
	record_t *right, *left, *nextkey;
};

//Points to the head of the tree
typedef struct {
	record_t *head;
} dict_t;



// all function prototypes
dict_t *createDict();
record_t *createRec(char *name, char *data);

void changeAddress(record_t **p1, record_t *p2);
void search(char *name, dict_t *pd);
void insert( dict_t *pd, record_t *x);

void printKey(record_t *node, int cmp);
void printToFile(record_t *pr, int cmp);
void printNotFound(char *name);

void free_tree(record_t *node);

#endif    