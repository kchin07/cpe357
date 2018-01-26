#include <string.h>

#ifndef LISTH

#define LISTH

struct node {
   char* word;
   int occurrences;
   struct node* next;
};
typedef struct node hashnode;
extern hashnode* new_node(char* data, int num);
extern hashnode* append(hashnode* one, hashnode* two);
extern hashnode* search(hashnode* list, char* cword);

#endif
