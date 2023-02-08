#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>



int main(int argc, char *argv[])
{
    int serSoc = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in serveraddress, clientaddress;
    serveraddress.sin_family = AF_INET;
    serveraddress.sin_port = htons(9001);

    bind(serSoc, (struct sockaddr *) &serveraddress, sizeof(serveraddress));

    listen(serSoc, 2);
    
    int cliSoc;

    accept(cliSoc, (struct sockaddr *) &clientaddress, sizeof(clientaddress));

    return 0;
}

