#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <ctype.h>
#include "linked.h"
#define HASHSIZE 5381

int wordCount;/*global variable*/

/*creates a new hashnode with a word and frequency*/
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

/* appends hashnodes together*/
hashnode* append(hashnode* one, hashnode* two) {
   hashnode* end;
   if (one != NULL) {
      end = one;
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

/*searches the linked list for a particular word*/
hashnode* search(hashnode* list, char* cword) {
   hashnode* cur;
   cur = list;
   while(cur) {
      if (!strcmp(cword, cur->word)) {
         return  cur;
      }
      cur = cur->next;
   }
   return NULL;
}

/*sorting helper function*/
int cmplex(void* a, void* b) {
   char* one;
   char* two;
   one = (*(hashnode**)a)->word;
   two = (*(hashnode**)b)->word;
   return strcmp(one, two)*(-1);
}

/*comparator function to help sort the list of words*/
int cmproccurr(void* a, void* b) {
   int occur;
   occur = (*(hashnode**)a)->occurrences - (*(hashnode**)b)->occurrences;
   if (occur == 0) {
      return cmplex(a, b);
   }
   return occur;
}

/* get the index to hash to the hash table*/
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

/*creates a hash table*/
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
   long index;
   char* temp;
   int letterCounter;
   char c;
   hashnode* cur;
   int multiplier;
   letterCounter = 0;
   multiplier = 1;
   temp = (char*)malloc(80*sizeof(char));
   /*read in each character in the files*/
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
            if (ht->node_list[index] == NULL) {
               hashnode* new = new_node(temp, 1);
               /*indexs the word into the hash table*/
               ht->node_list[index] = new;
               wordCount++; /*adds 1 to total word count*/
            }
            else {/*collision handling*/
               cur = ht->node_list[index];
               hashnode* found = search(cur, temp);
               if(found == NULL) {
                  hashnode* new = new_node(temp, 1);
                  cur = append(cur, new);
                  wordCount++;
               }
               else {
                  found->occurrences += 1;
               }
            }
            letterCounter = 0; /*restarts the character counter*/
            multiplier = 1; /*restarts the multiplier*/
            /*reallocate more memory for a new word to build*/
            temp = (char*)malloc(80*sizeof(char));
         }
         /* if the character is white space or new line, skip and 
          * don't add to string
          * */
         else if (c == ' '|| c=='\n') {
            continue;
         }
            /*add the character to the string that's being built*/
         else{
            letterCounter++; /*increments character counter*/
            /*
             * reallocates more memory for the new word if it's 
             * bigger than the current word size
             */
            if (letterCounter > 80 * multiplier){
               multiplier += 1;
               temp = (char*)realloc(temp, 80 * multiplier * sizeof(char));
            }
            temp = (char*)realloc(temp, (letterCounter+1)*sizeof(char));
            /*adds character to string being built*/
            temp[letterCounter-1]= (char)c;
         }
      }
   }
   return ht;
}

int main(int argc, char *argv[]){
   FILE* file; 
   int fileCounter = 1;
   int printFreqNum;
   int isdig;
   int i;
   int newIndex;
   int j;
   int diff;
   wordCount = 0;
   HashTable* MainTable;

   newIndex = 0;
   printFreqNum = 10;
   MainTable = ht_create(HASHSIZE);

   /*checks for file inputs*/
   if (argc < 2) {
      file = stdin;/*??????????????????????*/
      if(file == NULL){
         perror("Error1");
	 exit(EXIT_FAILURE);
      }
      else{
         ht_read_file(MainTable, file);
      }
   }
   /* handles the case for the "-n" parameter and other commandline
    * argument cases
    */
   else{
      if(!strcmp(argv[1], "-n")){
         fileCounter = 2;
         if(argc<3){
            perror("Error2(No file found)");
            exit(EXIT_FAILURE);
         }
         isdig = isdigit(*argv[2]);
         if(isdig){
            printFreqNum = atoi(argv[2]);
            fileCounter = 3;  
            if(argc<4){
               perror("Error3(No file found)");
               exit(EXIT_FAILURE);
            }
         }
         else{
            perror("Not valid number, usage error");
            exit(EXIT_FAILURE);
         }
      }
      
      /*iterates through all the files in commandline*/
      for(fileCounter; fileCounter < argc; fileCounter++){
         file = fopen(argv[fileCounter], "r");
	 if(file != NULL){
            ht_read_file(MainTable, file);
	 }
	 else{
	    perror("Error4");
	 }
      }
   }
    /* Gets all the words/frequencies from the hash table and puts 
     * them into a list 
     */
    printf("%d\n", wordCount);	
    hashnode** numsort = malloc(wordCount*sizeof(hashnode));
   for (i=0; i < HASHSIZE; i++) {
      if (MainTable->node_list[i] != NULL) {
         hashnode* cur = MainTable->node_list[i];
         while(cur) {
            numsort[newIndex] = cur;
            cur = cur->next;
            newIndex++;
         }
      }
   }
  /*sorts list of words by frequency the lexicographically*/
   qsort(numsort, wordCount, sizeof(numsort[0]), cmproccurr); 
   
   /*prints desired top frequent words*/
   printf("The top %d words (out of %d) are:\n", printFreqNum, wordCount);
   diff = wordCount - printFreqNum;
   if(printFreqNum > wordCount){
      diff = 0;
   }
   for (j=wordCount-1; j>= diff; j--) {
      printf("    %d %s\n", numsort[j]->occurrences, numsort[j]->word);
   }
   free(numsort);
   return 0;
}
