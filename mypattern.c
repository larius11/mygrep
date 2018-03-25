#include <stdio.h>
#include <stdlib.h>

int myfilter(char **pattern_grid, int sz);

/**
 * This function checks if a character is a digit
 * @return 0 if not a digit, 1 otherwise
 **/
int isDigit(const char c){
	if((c<48)||(c>57))
		return 0;
	return 1;	
}

/**
 * This function turns an octal number given as a string
 * into a single char
 * @return a char representation of str
 **/
char otoc(char *str){
	char ans = 0;
	if(str[3]<'8')
		ans+= (str[3]-48);
	else
		return -1;
	if(str[2]<'8')
		ans+= (str[2]-48)*8;
	else
		return -1;
	if(str[1]<'4')
		ans+= (str[1]-48)*64;
	else
		return -1;
	return ans;
}

/**
 * This function interprets a range for a regexp
 * @return the number of bytes checked on given string
 **/
int range(char *str, char* grid_row){
	int count = 1;
	char c1, c2;

	char inverse = 0;
	char buff[255];
	int i = 0;

	while(str[count]){
		char oct1[4];
		c1 = str[count++];
		if((c1=='^')&&(count==2)){
			inverse = 1;
		}else if((c1==']')&&(count>2)){
			--count;
			break;
		}else if(c1=='\\'){
			//Check for octal number
			if(isDigit(str[count])&&isDigit(str[count+1])&&isDigit(str[count+2])){
				oct1[0] = c1;
				oct1[1] = str[count++];
				oct1[2] = str[count++];
				oct1[3] = str[count++];
				c1 = otoc(oct1);
			}
		}
		c2 = str[count];
		//Check if pattern asks for a range
		if(c2=='-'){
			c2 = str[++count];
			++count;
			char oct2[4];
			if(c2=='\\'){
				//Check for octal number
				if(isDigit(str[count])&&isDigit(str[count+1])&&isDigit(str[count+2])){
					oct2[0] = c2;
					oct2[1] = str[count++];
					oct2[2] = str[count++];
					oct2[3] = str[count++];
					c2 = otoc(oct2);
				}
			}	
			if(c2<c1)
				return -1;
			while(c1<=c2)
				buff[i++]=c1++;						
		}else{
			if(!((c1=='^')&&(count==2)))
				buff[i++]=c1;
		}}
	if(str[count]!=']')
		return -1;
	if(!inverse){
		int j = 0;
		while(j<i)
			grid_row[buff[j++]] = '1';		
	}else{
		for(unsigned char ii = 0; ii<255; ++ii){
			int temp = 1;
			for (int j = 0; j < i; ++j){
				if(ii==buff[j]){
					temp = 0;}}
			if(temp)
				grid_row[ii] = '1';
		}
	}
	return count;
}

void set(char* str, char c){
	int i = 0;
	while(i<255){
		str[i++] = c;
	}
}

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