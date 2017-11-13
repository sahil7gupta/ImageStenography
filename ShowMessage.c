/*
Purpose: Given an input image, which has a text hidden in it the program decrypts the text message.
Author: Sahil Gupta
Parameters: [input image filename]
Date: 08/04/2017
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "ImageOperation.h"

int i,j;
int* cImage;
int iWidth,iHeight;
char* bin_str;
char cArray[3][100];

void reveal_message(int i){
	char c=0;
	int j,k;
	for (k=0;k<i;k=k+8){
		c=0;
		for (j=0;j<8;j++){
			c=c+bin_str[k+j]*pow(2,7-j);
		}
		printf("%c",c );
	}
}


void main(int argc, char* argv[])
{
		if(argc!=2){
			printf("ERROR: Usage: HideMessage [input image filename]\n");
			return;
		}

		int count0=0;

		FILE *filePointer = NULL;
		filePointer = fopen(argv[1],"r");
			
		if (filePointer == NULL)
		{
			printf("cannot open file");
			
		}else
		{
			cImage=ReadImage(filePointer);
			
			bin_str=(char*)malloc(iHeight*iWidth*sizeof(char));

			for (i = 0; i< iHeight; i++){
				for (j = 0; j< iWidth; j++){
		
					bin_str [i*iWidth+j] = cImage[i*iWidth+j]&1;
					
					if (bin_str[i*iWidth+j]==1){
						count0=0;
					}
					else if (bin_str[i*iWidth+j]==0){
						count0++;
					}
					if(count0==8){
						printf("HIDDEN MESSAGE: ");
						reveal_message(i*iWidth+j);
						printf("\n");
						return;
					}
				}		
			}
		}
	
		fclose(filePointer);
}
