///////////////////////////////////////////////////////////////////////
/*
	File :assign2.cpp
	Created by: Byron Hogan
	ID number:  Z1825194
	Due date: 9-29-17

	Purpose:To open and list all of what is in a file

*/
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include<iostream>
#include<stdio.h>
using namespace std;
int main(int argc,char* argv[]){
int fd;
int i=1;
string s;
ssize_t howMany,writen;
char buffer[40];
while(i<argc){//this will loop through all the command line parameters
	fd = open (argv[i],O_RDWR);//opens the fie of the command line parameter being read
	if (fd == -1){//Determines if the file opened
		perror("opening file");
		++i;
	}
	else{//Continue code here if file was opened
	for(int j=0;j<40;++j)//flushes/intializes the old data being held in buffer
		buffer[j]='\0';
	howMany=read(fd, buffer,20);//priming read
	while(howMany!= 0){//loops until the end of the file is reached
		if (howMany==-1){//stops the loop if read incorrectly
			perror("reading file 1");
			exit(1);
		}else{//put outputing file code here
			while(writen=write(1,buffer,strlen(buffer))!=-0){
				for(int j=0;j<40;++j)//flushes/intializes the old data being held in bu$
					 buffer[j]='\0';
			}
		}
	 if (howMany!= 0)//update the loop...gets the next set of data being read from the file
                howMany=read(fd, buffer,20);
	}

	int close(int fd);
	++i;//update the outer loop to move on to the next command line parameter
	}

}
return 0;
}
