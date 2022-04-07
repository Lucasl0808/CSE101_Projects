#include "List.h"
#include <string.h>

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
	int lineCount;
	char line[MAX_LEN];
	//maybe call fgets in a loop and read in each line, every time incrementing line count.
	while(fgets(line, MAX_LEN, in) != NULL){
		lineCount += 1;
		
	}
}
