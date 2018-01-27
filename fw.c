#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <ctype.h>
#include "linked.h"
#define HASHSIZE 5381

int wordCount;

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
      //printf("%s", end->word);
      for (; end->next; end = end->next) {
         /* do nothing */
      }
      end->next = two;
   }
   else {
      one = two;
   }
   //printf("\nappend: %s\n", one->word);
   return one;
}

hashnode* search(hashnode* list, char* cword) {
   hashnode* cur;
   cur = list;
   while(cur) {
      //printf("\n%s\n", cur->word);
      //printf("%d\n", strcmp(cword, cur->word));
      if (!strcmp(cword, cur->word)) {
         return  cur;
      }
      cur = cur->next;
   }
   return NULL;
}

int cmproccurr(void* a, void* b) {
   
   int occur = (*(hashnode**)a)->occurrences - (*(hashnode**)b)->occurrences;
   if (occur == 0) {
      return cmplex(a, b);
   }
   return occur;
}

int cmplex(void* a, void* b) {
   char* one = (*(hashnode**)a)->word;
   char* two = (*(hashnode**)b)->word;
   return strcmp(one, two)*(-1);
}

long hash(char *str){
   int hash = 0;
   int c;
   while (c = *str++) {
      hash = abs(hash*3) + c; /* hash * 33 + c */
   }
   return hash%HASHSIZE;
}

struct hash_table{
   int size;
   struct node** node_list;
};

typedef struct hash_table HashTable;

HashTable* ht_create(int size){
   HashTable* ht = NULL;
   int i;
	
   if (size < 1){
      return NULL;
   }
   if ((ht = malloc(sizeof(HashTable))) == NULL){
      return NULL;
   }
   if((ht->node_list=malloc(sizeof(HashTable))) == NULL){
      return NULL;
   }
   for (i = 0; i < size; i++){
      ht->node_list[i]= NULL;
   }
   ht->size = size;
   return ht;
}

HashTable* ht_read_file(HashTable* ht, FILE* file){
   long index;/*unused*/
   char* temp;
   char** words;
   int letterCounter;
   wordCount = 0;
   char c;
   hashnode* cur;
   int multiplier;
   letterCounter = 0;
   wordCount = 0;
   multiplier = 1;
   temp = (char*)malloc(80*sizeof(char));
   words = (char**)malloc(4*sizeof(char));

   while (!feof(file)){
      c = getc(file);
      c = tolower(c);
      if (c != EOF) {
            /*
             * if the character is white space or a new line and 
             * characters have been read in already, put the word
             * in the hashtable
             */
         if (!isalpha(c)&& letterCounter != 0){
            index = hash(temp);/*gets the index to hash into the word array*/
            //printf("%s, hash:%lu\n", temp, index);
                /*-------------------------------------------------------------------------*/
                /*need to change the wordCount to the index that you get from the hashcode*/
            //printf("\nchecking node\n");
            //printf("index: %d\n", index);
            if (ht->node_list[index] == NULL) {
               //printf("in if\n");
               hashnode* new = new_node(temp, 1);
               //printf("making new node | word: %s\n", new->word);
               ht->node_list[index] = new; /*indexs the word into the word array*/
               //printf("\ndidn't get in list\n");
               wordCount++;
            }
            else {
               //printf("chain node\n");
               cur = ht->node_list[index];
               hashnode* found = search(cur, temp);
               if(found == NULL) {
                  hashnode* new = new_node(temp, 1);
                  //printf("\nappend_node_word: %s\n", temp);
                  cur = append(cur, new);
                  wordCount++;
               }
               else {
                  //printf("incrementing\n");
                  found->occurrences += 1;
               }
                /*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/
            }
            letterCounter = 0; /*restarts the character counter*/
            multiplier = 1;
            temp = (char*)malloc(80*sizeof(char)); /*reallocate more mem for a new word to build*/
         }
            /*if the character is white space or new line, skip and don't add to string*/
         else if (c == ' '|| c=='\n') {
            continue;
         }
            /*add the character to the string that's being built*/
         else{
            letterCounter++; /*increments character counter*/
                /*
 *                  * reallocates more memory for the new word if it's 
 *                                   * bigger than the current word size
 *                                                    */
            if (letterCounter > 80 * multiplier){
               multiplier += 1;
               temp = (char*)realloc(temp, 80 * multiplier * sizeof(char));
            }
            temp = (char*)realloc(temp, (letterCounter+1)*sizeof(char));
            temp[letterCounter-1]= (char)c;
         }
      }
   }
   //index = hash("hello");
   //hashnode* hello = search(ht->node_list[index], "hello");
   //printf("%d occurrences\n", hello->occurrences);
   return ht;
}

int main(int argc, char *argv[]){
   FILE* file; 
   int fileCounter;
   int printFreq;
   int printFreqNum;
   int lastArg;
   int sLastArg;
   int hasn;
   int isdig;
	
   printFreq = 0;
   /*checks for file inputs*/
   if (argc < 2) {
      //printf("process file\n");
   }
   /*TO DO: process file*/
   HashTable* MainTable;
   long index;/*unused*/
   char* temp;
   char** words;
   int letterCounter;
   char c;
   int multiplier;
   letterCounter = 0;
   //wordCount = 0;
   multiplier = 1;
   temp = (char*)malloc(10*sizeof(char));
   words = (char**)malloc(4*sizeof(char));	
     
   MainTable = ht_create(HASHSIZE);

   printFreq = 0;
   /*checks for file inputs*/
   if (argc < 2) {
      file = stdin;/*??????????????????????*/
      if(file == NULL){
         perror("Error1");
	 exit(EXIT_FAILURE);
      }
      else{
         //printf("process file\n");
	 /*TO DO: process file*/
      }
   }
   //printf("about to read\n");
   ht_read_file(MainTable, file);
   //printf("read file\n");
   /*else if ((file =fopen(argv[1], "r")) == NULL){
      perror("Error");
      exit(EXIT_FAILURE);
   }
   else{*/
      /*checks last and second to last arguments for -n <num>*/
      /*lastArg = strcmp(argv[argc-1], "-n");
      sLastArg = strcmp(argv[argc-2], "-n");
      hasn = lastArg * sLastArg;
      if(!hasn){ 
         isdig = isdigit(*argv[argc-1]);
         printFreq = 1;
         if(isdig){
            printFreqNum = atoi(argv[argc-1]);
         }
         else{
	    printFreqNum = 10;
         }
      }*/
      /*iterates through all the files in commandline*/
      /*for(fileCounter = 1; fileCounter < argc; fileCounter++){
         file = fopen(argv[fileCounter], "r");
	 if(file != NULL){
	  */ /*TO DO process file*/
	/* }
	 else{
	    perror("Error");
	 }
      }
   }	*/
   /* TO DO: sort*/	
   /*if(printFreq == 1){
      printf("print %d words", printFreqNum);
    */  /*TO DO: print n number of words*/
   //}
   //
   //printf("word count: %d\n", wordCount);
   hashnode** numsort = malloc(wordCount*sizeof(hashnode));
   int i;
   int newIndex = 0;
   for (i=0; i < HASHSIZE; i++) {
      //printf("get node\n");
      //printf("word: %s\n", MainTable->node_list[i]);
      if (MainTable->node_list[i] != NULL) {
         hashnode* cur = MainTable->node_list[i];
         //printf("sorting cur:  %s\n", cur->word);
         while(cur) {
            numsort[newIndex] = cur;
            cur = cur->next;
            newIndex++;
         }
      }
   }

   qsort(numsort, wordCount, sizeof(numsort[0]), cmproccurr);
   //qsort(numsort, wordCount,  
   int j;
   for (j=wordCount-1; j>= 0; j--) {
      printf("Occurrences: %d | %s\n", numsort[j]->occurrences, numsort[j]->word);
   }
   return 0;
}
