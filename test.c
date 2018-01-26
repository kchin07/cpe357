#include <stdio.h>
#include <stdlib.h>
#include "linked.h"

//struct node hashnode;
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
   cur = list;
   while(cur) {
      printf("%s\n", cur->word);
      printf("%d\n", strcmp(cword, cur->word));
      if (!strcmp(cword, cur->word)) {
         return  cur;
      }
      cur = cur->next;
   }
   return NULL;
}


int main() {
   hashnode* list;
   char* val = "hello";
   hashnode* first = new_node(val, 3);
   char* val2 = "world";
   hashnode* second = new_node(val2, 4);
   list = append(first, second);
   hashnode* found = search(list, "world");
   //printf("%s\n", found->word);
   if (strcmp(second->word, found->word) == 0) {
      printf("looks good");
   }
   else {
      printf("not good");
   }
   return 0;
}
