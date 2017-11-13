/*
Purpose: Given a text message and an image, the text is stored in the last bit of each pixel.
Author: Sahil Gupta
Parameters: [input image filename] [“Message to hide”]
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

void ctob(char c,char* bin_str){
	for(int i=7;i>=0;i--){
		bin_str[i]=c/pow(2,i);
		c=c%(int)pow(2,i);
	}
}

void embed_it(int len){
	int k=8*len-1;

	for (i = 0; i< iHeight; i++){
		for (j = 0; j< iWidth; j++){
			if (k<-8){
				return;
			}						
			else if (k<0){
				cImage[i*iWidth+j]=(cImage[i*iWidth+j]>>1)<<1; k--;
			}
			else if(bin_str[k]==1){
				cImage[i*iWidth+j]=cImage[i*iWidth+j]|1; k--;
			}
			else {
				cImage[i*iWidth+j]=(cImage[i*iWidth+j]>>1)<<1;	k--;
			}		
		}
	}
}

void main(int argc, char* argv[]){

		if(argc!=3){
			printf("ERROR: Usage: HideMessage [input image filename] [“Message to hide”]\n");
			return;
		}

		int len=strlen(argv[2]);
		int k=8*len-1;

		

		bin_str=(char*)malloc(8*len*sizeof(char));
		for (i=0;i<len;i++,k=k-8){
			ctob(argv[2][i],bin_str+k-7);
		}
		
		
		FILE *filePointer = NULL,  *filePointerOut = NULL;
		
		
		filePointer = fopen(argv[1],"r");
		filePointerOut = fopen("hidden.pgm","w");
			
		if (filePointer == NULL)
		{
			printf("cannot open file");
			
		}else
		{
			cImage=ReadImage(filePointer);
			
			if(len>iWidth*iHeight/8){
				printf("ERROR: Message too long to store!\n");
				return;
			}
			
			embed_it(len);
			WriteImage(filePointerOut,cImage);
			printf("OUTPUT IMAGE: hidden.pgm has been created!\n");		
		}

		fclose(filePointer);
		fclose(filePointerOut);
	
}
