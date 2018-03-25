#include "mygrep.h"

/**
 * This function interprets grep patterns
 * @return 0 if successful, -1 otherwise
 **/
int mypattern(char * pattern, char * patfile){
	if (pattern[0]=='\0'){
		if (patfile[0]=='\0'){
			printf("Invalid usage\n");
			return -1;}

		FILE *file = fopen(patfile, "r");

		if(file !=NULL) {
			pattern = (char *)malloc(sizeof(char)*640);
			fgets(pattern, 640, file);			
			fclose(file);}}

	int pos = 0;
	int i = 0;
	int temp;
	char c;
	char **pattern_grid = (char **) malloc(sizeof(char *));
	pattern_grid[i] = (char *) malloc(sizeof(char)*255);
	set(pattern_grid[i++],'.');
	while(pattern[pos]){
		c = pattern[pos];
		switch(c){
			case '[':
				temp = range(&(pattern[pos]),pattern_grid[i-1]);
				if(temp!=-1)
					pos += temp;
				else{
					printf("Invalid syntax: %s\n",pattern);
					pos = -2;
				}
				break;
			case '\\':
				if(pattern[++pos]){
					char oct[4];
					if(isDigit(pattern[pos])&&isDigit(pattern[pos+1])&&isDigit(pattern[pos+2])){
						oct[0] = '\\';
						oct[1] = pattern[pos++];
						oct[2] = pattern[pos++];
						oct[3] = pattern[pos];
						pattern_grid[i-1][otoc(oct)] = '1';
					}else
						pattern_grid[i-1][pattern[pos]] = '1';
				}else{
					printf("Invalid syntax: %s\n",pattern);
					pos = -2;
				}
				break;
			default:
				pattern_grid[i-1][pattern[pos]] = '1';
				break;}
		++pos;
		if(pattern[pos]){
			char **newgrid = (char **)realloc(pattern_grid,(i+1)*sizeof(char *));
			pattern_grid = newgrid;
			pattern_grid[i] = (char *) malloc(sizeof(char)*255);
			set(pattern_grid[i++],'.');
		}
	}
	return myfilter(pattern_grid, i);
}
/**
 * NAME:
 * 		mypattern - 
 *
 * SYNOPSIS:
 *		./mypattern
 *
 * DESCRIPTION:
 *
 *  	-
 **/