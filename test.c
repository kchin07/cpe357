#include <stdio.h>
#include <stdlib.h>
#include "linked.h"

//struct node hashnode;

int main() {
   hashnode* list;
   char* val = "he";
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
