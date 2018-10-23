/*
Programmed by:BYron Hogan
Class: CSCI330
zid:Z1825194
assignment:assignment 3
Purpose:To define the methods of the dog class
*/
#include<locale>
#include<math.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include <unistd.h>
#include"dog.h"
#include<iostream>

using namespace std;


//this method shifts all alpha characters creating a ceaser cipher 
void dog::cipher(char buffer[] ,int& shift,int max){
char temp;
int j=0;
int i;
for(i=0;i <shift;++i){//performs the cipher one step at a time
	j=0;
	while(j<max){//where the shifting actually occurs
		temp=buffer[j];
		if(isalpha(temp)){
			temp= temp+1;
			if (temp =='{'){//cylce only through the alphabet
				temp='a';
			}
			if (temp=='[')//cycle only through the alphabet
				temp='A';
			buffer[j]=temp;
		}
		++j;//updates inner loop
	}
}
}

void dog::rotate(char buffer[],int&shift,int max){
char temp;
int j=0;
int i;
for(i=0;i <shift;++i){//performs the rotation one step at a time
        j=0;
        while(j<max){//where the rotating actually occurs
                temp=buffer[j];
                temp= temp+1;
                buffer[j]=temp;
                ++j;//updates inner loop
	}
}
}

void dog::hexa(char buffer[],int bufferSize,int max){
	int i;
	int temp;
	int hex;
	char holder[2];
	

	for (i=0;i <max;++i){
		temp=buffer[i];
		convertToHex(temp,holder);//converts decimal to hexadecimal
		cout<<holder[1]<<" " <<holder[2];
	}
	cout<<endl;

             for(int j=0;j<40;++j)//flushes the old data being held 
                buffer[j]='\0';

}

//converts a decimal number to a hexadecimal number
void dog::convertToHex(int decimalNumber,char hex[]){
    int remainder,quotient;
    int i=1;
    int j,temp;
    char hexadecimalNumber[100];

    quotient = decimalNumber;
    while(quotient!=0)//loops until the number is at 0
    {
      temp = quotient % 16;
      //converts integer into a character
      if( temp < 10){
           temp =temp + 48;
      }
      else{
         temp = temp + 55;
      }
      hexadecimalNumber[i++]= temp;
      quotient = quotient / 16;
    }

    for(j=i-1;j>0;j--){
      hex[j]=hexadecimalNumber[j];
    }

}
