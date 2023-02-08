#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>



int main(){

  int cliSoc = socket(AF_INET, SOCK_STREAM, 0);

  struct sockaddr_in serveraddress;
  serveraddress.sin_family = AF_INET;
  serveraddress.sin_port = htons(9001);
  serveraddress.sin_addr.s_addr = inet_addr("127.0.0.1");
  
  connect(cliSoc, (struct sockaddr *) &serveraddress, sizeof(serveraddress));

  char filename[80];
  char rcvd [80];

  


  
  return 0;
}
