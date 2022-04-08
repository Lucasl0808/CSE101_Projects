#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "List.h"
#define MAX_LEN 300

int main(int argc, char *argv[]){
	if(argc != 3){
		fprintf(stderr, "Usage: %s <input file> <output file>\n", argv[0]);
		exit(1);
	}
	FILE *in, *out;
	in = fopen(argv[1], "r");
	if(in == NULL){
		printf("Unable to open file %s for reading\n", argv[1]);
		exit(1);
	}
	out = fopen(argv[2], "w");
	if(out == NULL){
		printf("Unable to open file %s for writing\n", argv[2]);
		exit(1);
	}
	int lineCount = 0;
	char line[MAX_LEN];
	while(fgets(line, MAX_LEN, in) != NULL){
		lineCount += 1;
	}
	char **strArray = malloc(sizeof(char *) * lineCount);
	//for(int i = 0; i < lineCount; i += 1){
	//	strArray[i] = malloc(sizeof(char) * MAX_LEN);
	//}
	
	//allocated array fseek to reread file
	fseek(in, 0, SEEK_SET);
	int x = 0;
	while(fgets(line, MAX_LEN, in) != NULL){
		char *temp = malloc(sizeof(char) * MAX_LEN);
		line[strlen(line) -1] = '\0';
		strcpy(temp, line);
		strArray[x] = temp;
		x += 1;
	}
	List L = newList();
	for(int i = 0; i < lineCount; i += 1){
		if(length(L) == 0){
			append(L, i);
		}
		else{
			if(strcmp(strArray[get(L)], strArray[i]) >= 0){
				prepend(L, i);
			}
			else{
				while(index(L) >= 0){
					if(strcmp(strArray[get(L)], strArray[i]) >= 0){
						insertBefore(L, i);
						break;
					}
					moveNext(L);
				}
				if(index(L) == -1){
					append(L, i);
				}
			}
		}
		moveFront(L);
	}
	int y;
	while(index(L) >= 0){
		y = get(L);
		fprintf(out, "%s\n", strArray[y]);
		moveNext(L);
	}
	for(int i = 0; i < lineCount; i += 1){
		free(strArray[i]);
	}
	free(strArray);
	freeList(&L);
	fclose(in);
	fclose(out);
	return 1;
}
