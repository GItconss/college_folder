#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main()
{
	FILE*obj=fopen("obj.txt","r");
	if(!obj)
	{
		printf(" file couldnt open...\n");
		return 1;
	}
	int locctr=0;
	char ch;
	while((ch=fgetc(obj))!=EOF)
	{
		if(ch=='H')
		{
			char pname[6];
			int start,length;
			
			fscanf(obj,"%s%X%X\n",pname,&start,&length);
			locctr=start;
			
			printf("\nHEADER RECORD\n");
			printf("Program name:%s\n",pname);
			printf("Program name:%X\n",start);
			printf("Program name:%X\n",length);
			
			
		}
		else if(ch=='T')
		{
			
			int start,length;
			fscanf(obj,"%X%X\n",&start,&length);
			locctr=start;
			
			for(int i=0;i<length;i++)
			{
			 char byte1=fgetc(obj);
				if(byte1== ' ' || byte1=='\n')
				{
					i--;
					continue;
				}
			char byte2=fgetc(obj);
			if (byte2 == EOF)
                    		break;
			printf("%X: %c%c\n",locctr++,byte1,byte2);
			}
			
		}
	}
	fclose(obj);
	return 0;
	
}
/*HEADER RECORD
Program name:COPY
Program name:1000
Program name:12
1000: 00
1001: 10
1002: 09
1003: 18
1004: 10
1005: 0C
1006: 0C
1007: 10
1008: 0F
1009: 00
100A: 00
100B: 05
100C: 00
100D: 00
100E: 03
*/
