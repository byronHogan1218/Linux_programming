#include <sys/types.h>
#include <sys/wait.h>
#include<stdlib.h>
#include<stdio.h>
#include <unistd.h>
#include<iostream>
#include<string.h>

using namespace std;
int main(){
pid_t pid;
pid_t pid2;

pid= fork();
if (pid==0){//child
pid2=fork();
if( pid2==0){
cout<<"my child"<<endl;
}else{
cout<<"The middle";
wait(NULL);
}
}
else
wait(NULL);
return 0;
}
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
int count=0;
pid_t pid;
pid_t pid2;
//while(cmd != "quit"){
count++;
if (count > 100)//temporary thing to stop an infinite loop from occuring,needs wait commands to stop this from happening
//	break;
cin.ignore(256, '\n');
getline(cin,cmd);
//cin.ignore(256, '\n');
getline(cin,cmd2);
if (cmd2=="quit")
	return 0;//this quits the program if quit is entered for the second command
if (cmd=="quit")
	return 0;
pid=fork();
if (pid==-1){
	perror("fork");
	exit(1);
}

if (pid==0){//Child for original process
	//The pipe is created here
	int p[2];
	if(pipe(p)<0)
		exit(1);
cout<<"before second fork"<<endl;
	pid2=fork();
cout <<pid2;
cout<<"after second fork"<<endl;
	if(pid2==-1){
		perror("fork");
		cout<"Is there an error?";
		exit(1);
	}

	if (pid2==0){//this is a child of the second process,put cmd1 here
cout<<"Child procces pid :" <<pid2;
		char *myargv[6];
                char buffer[1024];
                strncpy(buffer,cmd.c_str(),1024);//should token string here
                myargv[0] =buffer;
                myargv[1]= NULL;

                close (p[1]);//closes the unused write end of pipe
		dup2(p[0],0);
		while (read(p[0], buffer, 1) > 0)
                   write(STDOUT_FILENO, buffer, 1);
		write (STDOUT_FILENO, "\n",1);
		//close (p[0]);
		int j= execvp(cmd.c_str(),myargv);
                cout<<"This is the child's child aka it didnt exec"<<endl;

	
	}else{//this is the parent of the second process,put cmd2 here
cout<<"Parent pid:" <<pid2;
		char *myargv[6];
		char buffer[1024];
		strncpy(buffer,cmd2.c_str(),1024);
		myargv[0] =buffer;
		myargv[1]= NULL;

		close(p[0]);          /* Close unused read end */
		dup2(p[1],1);
               write(p[1], myargv, strlen(myargv[1]));//removing the [1] from mid
//               close(p[1]);          /* Reader will see EOF */
               wait(NULL);                /* Wait for child */
		cout <<"Do i get here";
		int j= execvp(cmd2.c_str(),myargv);
		cout<<"i ma the middle aka it didnt exec\n";
	}
}
else{//Parent of original process
	wait(NULL);
}
//}
return 0;
}
