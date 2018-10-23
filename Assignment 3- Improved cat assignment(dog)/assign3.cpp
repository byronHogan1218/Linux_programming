///////////////////////////////////////////////////////////////////////
/*
	File :assign2.cpp
	Created by: Byron Hogan
	ID number:  Z1825194
	Due date: 9-29-17

	Purpose:To open and list all of what is in a file

*/
#include"dog.h"
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
int fd,opt;
int bufferSize=40;
int readSize=20;
int shift=0;
bool bflag=false,nflag=false,cflag=false,rflag=false,xflag=false;
char optstring[] = "b:n:c:r:x";
while((opt= getopt(argc,argv,optstring))!=-1){//determines if any optional parameters were used
	switch (opt){
	case 'b':
		bflag=true;
		bufferSize=atoi(optarg);
		break;
        case 'n':
                nflag=true;
		readSize=atoi(optarg);
		break;
        case 'c':
                cflag=true;
		shift= atoi(optarg);
		break;
        case 'r':
                rflag=true;
		shift=atoi(optarg);
		break;
        case 'x':
                xflag=true;
                break;
	default:
		break;
	}
}
if (cflag==true &&rflag==true){
cout<<"Both -r and -c cannot both be specified"<<endl;
exit(1);
}
const int READSIZE=readSize;
const int BUFFERSIZE=bufferSize;

int size;
dog cipherObject;
ssize_t howMany;
char buffer[BUFFERSIZE];

//all optind were i's which were intilialized to 1
while(optind<argc){//this will loop through all the command line parameters
	fd = open (argv[optind],O_RDWR);//opens the fie of the command line parameter being read
	if (fd == -1){//Determines if the file opened
		perror("opening file");
		++optind;
	}
	else{//Continue code here if file was opened
	for(int j=0;j<40;++j)//intializes the  data being held in buffer
		buffer[j]='\0';
	howMany=read(fd, buffer, READSIZE);//priming read
	size=howMany;
	while(howMany!= 0){//loops until the end of the file is reached
		if (howMany==-1){//stops the loop if read incorrectly
			perror("reading file 1");
			exit(1);
		}else{//put outputing file code here
			if (cflag==true){//code for ceaser cipher
				cipherObject.cipher(buffer,shift,size);
			}
			if (rflag==true){//code for binary rotation
				cipherObject.rotate(buffer,shift,size);
			}
                       if (xflag==true){//code for hexadecimal flag
                                dog hexBuf;
                                hexBuf.hexa(buffer,BUFFERSIZE,size);
                        }
			if (xflag==false){
			howMany=write(1,buffer,strlen(buffer));
			for(int j=0;j<40;++j)//flushes the old data being held in buffer
				buffer[j]='\0';
			}
		}
	if (howMany!= 0){//update the loop...gets the next set of data being read from the file
	        howMany=read(fd, buffer,READSIZE);
		size=howMany;
	}
	if (nflag==true)
		break;
	}

	int close(int fd);
	if (nflag==true)
		break;
	++optind;//update the outer loop to move on to the next command line parameter
	}

}

return 0;
}
