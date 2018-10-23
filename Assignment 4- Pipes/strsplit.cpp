#include <unistd.h>
#include <iostream>
#include <string.h>
using namespace std;

int main(){
ssize_t nread;
char* myargv[6];
char buffer[1025];
char string[]="This is a string";
//nread=read(1,buffer,1024);
//cout <<"bytes read are: "<<nread<<endl;
int i=0;
//while (i<nread){
char* first=strtok(string," ");
char* second=strtok(NULL," ");
char* third=strtok(NULL," ");
char* fourth=strtok(NULL," ");
char* fifth=strtok(NULL," ");
char *sixth=strtok(NULL," ");

char* holder;
strcpy (holder, first);
strcat (holder, second);
strcat (holder, third);
strcat (holder, fourth);
strcat (holder, fifth);
strcat (holder, sixth);
cout <<holder<<endl<<"That was holder"<<endl;
//cout << myargv;
//cout <<*myargv<<endl;

return 0;
}
