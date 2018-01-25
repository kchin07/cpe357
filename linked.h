#include <string.h>

#ifndef LISTH

#define LISTH

typedef struct node* node;
struct node {
   char* word;
   int occurrences;
   struct node* next;
};

node* new_node(char* data, int num) {
   struct node* new;
   new = (struct node*)malloc(sizeof(struct node));
   if (!new) {
      perror("new_node");
      exit(EXIT_FAILURE);
   }
   new -> word = data;
   new -> occurrences = num;
   new -> next = NULL;
   return (node*)new;
}

node* append(node* one, node* two) {
   struct node* end;
   if (one != NULL) {
      end =(struct node*)one;
      printf("%s", end->word);
      for (; end->next; end = end->next) {
         /* do nothing */
      }
      end->next = (struct node*)two;
   }
   else {
      one = two;
   }
   return one;
}

node* search(node* list, char* cword) {
   struct node* cur;
   for (cur = (struct node*)list; cur -> next; cur = cur -> next) {
      if (strcmp(cword, cur -> word) == 0) {
         return  (node*)cur;
      }
   }
   return NULL;
}
#endif
