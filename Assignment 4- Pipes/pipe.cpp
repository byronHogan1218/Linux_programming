/*
Programmed by byron hogan
zid   z1825194
program 4
purpose:To mimic the pipe shell command
KNOWN ERRORS:This program does not token out the string being passed into exec
This program's pipe function does not work
Entering something that is not a command causes an infinite loop
This program was submitted knowing these errors because I ran out of time to try and figure them out
*/
#include <sys/types.h>
#include <sys/wait.h>
#include<stdlib.h>
#include<stdio.h>
#include <unistd.h>
#include<iostream>
#include<string.h>
using namespace std;

int main(){
string cmd="0";
string cmd2="0";
pid_t pid;
pid_t pid2;
while(cmd != "quit"){
//cin.ignore(256, '\n');//ignores the new line from the user,not sure if neccessary yet
getline(cin,cmd);
//cin.ignore(256, '\n');
getline(cin,cmd2);
if (cmd2=="quit")
	return 0;//quits the program if quit is entered 
if (cmd=="quit")
	return 0;//quits the program if quit is entered
pid=fork();//the first fork,the parent should keep the loop going,child should fork again
if (pid==-1){
	perror("fork");
	exit(1);
}

if (pid==0){//Child for original process,fork again for the commands
	//The pipe is created here
	int p[2];
	if(pipe(p)<0)
		exit(1);
	pid2=fork();
	if(pid2==-1){
		perror("fork");
		cout<"Is there an error?";
		exit(1);
	}

	if (pid2==0){//this is a child of the second process,put cmd1 here
//ERROR CHECKING CODE
//cerr<<"Child procces pidddddddddddddddddd :" <<pid2;
		char *myargv[6];
                char buffer[1024];
//Gets code into a fromat that exec can take
                strncpy(buffer,cmd.c_str(),1024);//should token string around here
                myargv[0] =buffer;
                myargv[1]= NULL;

                close (p[1]);//closes the unused write end of pipe
		dup2(p[0],0);//routes std input to the read side of the pipe
		while (read(p[0], buffer, 1) > 0)
                   write(STDOUT_FILENO, buffer, 1);
		write (STDOUT_FILENO, "\n",1);
		close (p[0]);
		int j= execvp(cmd.c_str(),myargv);
//ERROR CHECKING CODE HERE
                cerr<<"This is the child's child aka it didnt exec"<<endl;

	
	}else{//this is the parent of the second process,put cmd2 here
//ERROR CHECKING CODE HERE
//cerr<<"Parent pid:" <<pid2;
		char *myargv[6];
		char buffer[1024];
		strncpy(buffer,cmd2.c_str(),1024);
		myargv[0] =buffer;
		myargv[1]= NULL;

		close(p[0]);       //close unused read end 
		dup2(p[1],1);      //routes std output to the pipe output
               write(p[1], myargv, strlen(myargv[1]));//removing the [1] from mid
               close(p[1]);    //The pipe read will send EOF
               wait(NULL);     // Wait for child 
		int j= execvp(cmd2.c_str(),myargv);
//ERROR CHECKING CODE HERE
		cerr<<"The middle didnt exec\n";
	}


}
else{//Parent of original process
	wait(NULL);//Wait for child to finish
}
}//the while loop bracket
return 0;
}
