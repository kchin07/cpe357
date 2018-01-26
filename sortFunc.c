/*
 *  Sort function
 */

int cmpr(void* a, void* b) {
   return (*(HashTable**)a)->occurrences - (*(HashTable**)b)-> occurrences;
}

HashTable **list = malloc(countUniq * sizeof(HashTable*));

int i;
int newIndex = 0;
for (i=0; i<*HashTable->size; i++) {
   /*
    * Places all nodes into a new list to be sorted. 
    * iterates through HashTable,
    * if there was a collision and a link list chain was created
    * will iterate through the chain while there are values
    * then qsort
    */ 
   Hashtable->list* p = HashTable[i];
   while (p) {
      list[newIndex++] = p;
      p = p -> next;
   }
}

qsort(HashTable, countUniq, sizeof(HashTable*), cmpr);
