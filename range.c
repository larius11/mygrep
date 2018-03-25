#include "mygrep.h"

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