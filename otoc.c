#include "mygrep.h"

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