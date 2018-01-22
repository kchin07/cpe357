#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>

unsigned long
hash(unsigned char *str){
    unsigned long hash = 5381;
    int c;
    while (c == *str++) {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    return hash;
}

unsigned char *temp;
unsigned char *words[3];

int main(int argc, char *argv[]){
    FILE *file; 
    unsigned long index;
    int letterCounter = 0;
    int wordCount = 0;
    if (argc <= 1) {
       printf("Not enough arguments");
       exit(EXIT_FAILURE);
    }
	if ((file =fopen(argv[1], "r")) == NULL){
	    perror("Error");
            exit(EXIT_FAILURE);
	}
	char c;
	while (!feof(file)){
		c = getc(file);
		if (c != EOF) {
		/* SWITCH AROUND GETC()*/
		/*printf("%c\n", c);*/
			if (c == ' ' && temp != NULL){
				printf("if\n");
				index = hash(temp);
				printf("%lu\n", index);
				printf("%s\n", temp);
				*words[wordCount] = *temp;
				wordCount++;
				free(temp);
				letterCounter = 0;
				temp = malloc(2);
            	                temp = NULL;
			}
			else if (c == ' ') {
				continue;
			}
			else{
				printf("%c\n", c);
				temp = realloc(temp, letterCounter + 3);/* 1 for 0 bit, 1 for extra char, 1 for current char*/
				temp[letterCounter]= c;
				letterCounter++;
			
			}
		
		}
    }
	int i;
	for (i = 0; i < 3; i++) {
		printf("%s\n", words[i]);
	}
	
    printf("\nok\n");
    return 0;
}
