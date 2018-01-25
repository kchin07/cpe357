#include <stdio.h>
#include <stdlib.h>
#include "linked.h"

int main() {
   node* list;
   char* val = "hello";
   node first = *new_node(val, 3);
   char* val2 = "world";
   node second = *new_node(val2, 4);
   list = append((node*)first, (node*)second);
   node* found = search(list, "world");
   if (strcmp(((node)second)->word, ((node)found)->word) == 0) {
      printf("looks good");
   }
   else {
      printf("not good");
   }
   return 0;
}
