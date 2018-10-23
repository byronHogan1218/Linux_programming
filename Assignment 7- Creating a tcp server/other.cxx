// TCP example 12-4-17

#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {

  // socket
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

  // bind
  if (bind(sock, (struct sockaddr *) &myaddr, sizeof(myaddr))) {
    perror("bind");
    exit(2);
  }

  // listen
  if (listen(sock, 64) == -1) {
    perror("listen");
    exit(1);
  }

  int newsock;
  socklen_t clientlen = sizeof(sockaddr_in);

  char buffer[1024];
  while (1) {
    // accept
    newsock = accept(sock, (struct sockaddr *) &theiraddr, &clientlen);
    // close(newsock);
    // close(sock);
    // exit(0);

    // read
    ssize_t nread = read(newsock, buffer, 1024);

    cout << "read: " << buffer << endl;

    // write
    write(newsock, buffer, nread);

    //handle the connections


    //close

  }

  // close original socket that is listening
}
