/*
Name: Byron Hogan
zid:  z1825194
Program: Assignment 7
Due date: 12-08-17
Purpose:To create a tcp server
*/
#include <dirent.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <iostream>

using namespace std;

//////////////////////////////////////////////////////////
//This function is used to make sure the last character is a null in
//a string from the client
void chomp(char *s) {
for (char *p = s + strlen(s)-1; // start at the end of string
		*p == '\r' || *p == '\n'; // while there is a trailing \r or \n
		p--) // check next character from back
	*p = '\0'; // change \r or \n to \0
}




int main(int argc, char *argv[]) {

  // Create the original,listening socket
  int sock = socket(AF_INET, SOCK_STREAM, 0);

  if (sock == -1) {
    perror("socket");
    exit(1);
  }

  struct sockaddr_in myaddr;
  struct sockaddr_in theiraddr;

  memset(&myaddr, 0, sizeof(myaddr));
  myaddr.sin_family = AF_INET;
  myaddr.sin_addr.s_addr = INADDR_ANY;
  myaddr.sin_port = htons(atoi(argv[1]));

  // Binds the socket to be able to listen on a specific port
  if (bind(sock, (struct sockaddr *) &myaddr, sizeof(myaddr))) {
    perror("bind");
    exit(2);
  }

  // Listens on the port that was set up for clients who are connecting
  if (listen(sock, 64) == -1) {
    perror("listen");
    exit(1);
  }

  //This is the socket that clients will communicate over
  int newSock;
  socklen_t clientlen = sizeof(sockaddr_in);
  char buffer[1024];
  while (1) {
	cout <<" LOOKING FOR NEW CONNECTION " << endl;

    // Accepts the connection of a client to the server
    newSock = accept(sock, (struct sockaddr *) &theiraddr, &clientlen);

   //This code handles the connection
/////////////////////////////////////////////////
   ssize_t pid;

   //Forks, the parent keeps listening while the child handles the client
   pid=fork();
   if (pid==-1){
	perror("fork");
	exit(1);
   }

   if (pid==0){//This is the child proccess
	int i=0;
	while (i<1024){//flushes the data in buffer,filling it with NULL
		buffer[i]=0;
		++i;
	}
	//Read the data being sent in from the client
	ssize_t nread;
	nread = read (newSock, buffer, 1024);
	buffer[nread] =0;
	char path[1026];
	chomp(buffer);
	i=0;
	while( i<1025){//Flushes the data in path,filling it with NULL
		path[i]=0;
		++i;
	}
	i=0;
	int j=0;
	bool foundGet=false;
		while((unsigned int)i<nread){//Loops to find the word GET
			if (buffer[i]=='G'){
				if(buffer[i+1]=='E'){
					if (buffer[i+2]=='T'){//The path name follows
						foundGet=true;
						i+=4;//adds three for GET and one for a space
						while (buffer[i]!=0){
							path[j]=buffer[i];
							++i;
							++j;
						}
						break;
					}
				}
			}
			++i;
		}
	if( foundGet==false){//Error checking:Makes sure the word GET was typed
		write(newSock, "Must begin with the word GET\n",29);
		close(newSock);
		continue;
	}
///////////////////////////////////////////////////////////////////
//The following code handles outputting of the files/directories

	//Makes sure that the path starts with a /
	if (path[0] != '/'){
		write(newSock,"The path must start with a /\n",30);
		close(newSock);
		continue;
	}
	//Makes sure that the path does not contain a ..
	for( i=0;i < strlen(path); ++i){
		if ( path[i] == '.' && path[i+1] == '.'){
			write(newSock, "The path cannot contain a ..\n",29);
			close(newSock);
			continue;
		}
	}
        if(dup2(newSock,1) <0 ){//Links the new sock to standard output
        	perror("socket out dup2");
        	exit(EXIT_FAILURE);
        }

	char command[3];
	i=0;
	while (i <3){//Flushes command,filling it with NULL
		command[i]=0;
		++i;
	}
	if (path[0]== '/' && strlen(path) == 1){//Handles the case of just the / being typed
		path[0] = '.';
		command[0] = 'l';
		command[1] = 's';
		command[2] = ' ';
	        char* systemParameter = new char[strlen(command)+strlen(path)+1];
		strcat(systemParameter,command);
		strcat(systemParameter,path);
		system (systemParameter);
	}
//	else{
	if(1){//useless if,remove if time and unindent everything by one
		i=0;
		char temp[1026];
		temp[0]='.';
		while (i < strlen(path)){//performs a shift
			temp [i+1]=path[i];
			++i;
		}
		int count=i;
		i=0;
		while (i <= count){//copies temp into path
			path[i]= temp[i];
			++i;
		}
		path[i+1]=0;//makes sure that the string ends correctly
		chomp(path);



		struct stat isFile;
		stat(path, &isFile);
		if ( isFile.st_mode & S_IFREG){//determines if it is not a directory
                	//THIS MUST BE A FILE
			/////////////////////
			command[0] = 'c';
                	command[1] = 'a';
                	command[2] = 't';
			command[3] = ' ';
                	char* systemParameter = new char[strlen(command)+strlen(path)+1];   //Combines the command with the path to run it
                	strcat(systemParameter,command);
                	strcat(systemParameter,path);
                	system (systemParameter);
		}
		else if(isFile.st_mode & S_IFDIR){//This is a directory
			const char* indexString;
			if ( path[strlen(path)-1] == '.'){//sets the indexString to the appropriate value (with a slash if the path is longer than just /)
				indexString = "index.html";
				path[0]='.';
				path[1]='/';
			}
			else
				indexString = "/index.html";
                        char* addIndex = new char[strlen(path)+strlen(indexString) + 1];
                        strcat(addIndex,path);
                        strcat(addIndex,indexString);
			i=1;
			bool isIndex = true;
			while(i< strlen(indexString)){//Determines if index.html is in the directory
				if ( indexString[strlen(indexString)-i] != addIndex[strlen(addIndex)-i] ){
					isIndex = false;
				}
				++i;
			}
			if ( isIndex ){//Handles is index.html was found in the directory(prints out the content of the file
				command[0]= 'c';
				command[1]= 'a';
				command[2]= 't';
				command[3]= ' ';
				char indexSystemParameter [1024];// Combines the command with the path and adds on the index.html to the path, then prints it
				strcat(indexSystemParameter, command);
				strcat(indexSystemParameter, path);
				strcat(indexSystemParameter, indexString);
				system (indexSystemParameter);
			}else{//Listes what is in the directory
				command[0]= 'l';
				command[1]= 's';
				command[2]= ' ';
				char* systemParameter = new char[strlen(command)+strlen(path)+1]; // Combines the command with the path to be run,lists it
				strcat(systemParameter,command);
                	        strcat(systemParameter,path);
        	                system (systemParameter);
			}
		}
	}

	close(1);
   }
   else{//parent process
	close(newSock);
   }

   close(newSock);
  }//This is the end of the forever server loop
  // close original socket that is listening
  close(sock);
}
