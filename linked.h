#include <string.h>

#ifndef LISTH

#define LISTH

struct node {
   char* word;
   int occurrences;
   struct node* next;
};
 typedef struct node hashnode;


hashnode* new_node(char* data, int num) {
   hashnode* new;
   new = malloc(sizeof(hashnode));
   if (!new) {
      perror("new_node");
      exit(EXIT_FAILURE);
   }
   new -> word = data;
   new -> occurrences = num;
   new -> next = NULL;
   return new;
}

hashnode* append(hashnode* one, hashnode* two) {
   hashnode* end;
   if (one != NULL) {
      end = one;
      printf("%s", end->word);
      for (; end->next; end = end->next) {
         /* do nothing */
      }
      end->next = two;
   }
   else {
      one = two;
   }
   return one;
}

hashnode* search(hashnode* list, char* cword) {
   hashnode* cur;
   for (cur = list; cur -> next; cur = cur -> next) {
      if (strcmp(cword, cur -> word) == 0) {
         return  cur;
      }
   }
   return NULL;
}
#endif
