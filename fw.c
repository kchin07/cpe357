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
char **words;

int main(int argc, char *argv[]){
    FILE *file; 
    unsigned long index;
	words = (char**)malloc(4*sizeof(char));
    int letterCounter = 0;
    int wordCount = 0;
	int sizeOfWord = 10;
	temp = (char*)malloc(1*sizeof(char));

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
			if ((c == ' ' || c == '\n')&& letterCounter != 0){
				/*printf("if\n");*/
				/*index = hash(temp);
				printf("%lu\n", index);
				printf("%s\n", temp);*/
				printf("%d\n", wordCount);
				words[wordCount] = temp;
				wordCount++;
				letterCounter = 0;
				temp = (char*)malloc(1*sizeof(char));
			}
			else if (c == ' '|| c=='\n') {
				continue;
			}
			else{
				/*printf("%c\n", c);*/
				letterCounter++;
				printf("lc: %d :%d\n", letterCounter,c);
				temp = (char*)realloc(temp, (letterCounter+1)*sizeof(char));/* 1 for 0 bit, 1 for extra char, 1 for current char*/
				temp[letterCounter-1]= c;
			
			}
			
		}
    }
	printf("out\n");
	int i;
	for (i = 0; i < 4; i++) {
		printf("%s\n", words[i]);
	}
	
    printf("\nok\n");
    return 0;
}
