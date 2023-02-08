 #include <stdlib.h>
 #include <stdio.h>

 #include <sys/types.h>
 #include <sys/socket.h>
 #include <unistd.h>

 #include <netinet/in.h>

 int main()
 {
    //CREATE A SOCKET
    int network_socket;
    network_socket=socket(AF_INET,SOCK_STREAM,0);

    //SPECIFY AN ADDRESS TO CONNECT TO
    struct sockaddr_in server_address;
    server_address.sin_family =AF_INET;
    server_address.sin_port=htons(9002);
    server_address.sin_addr.s_addr=INADDR_ANY;

    int connection_status = connect(network_socket, (struct sockaddr*) &server_address, sizeof(server_address));
    //check for error with the connection;

    if(connection_status == -1)
    {
        printf("Error in connection");
    }

    char server_response[256];
    recv(network_socket, &server_response, sizeof(server_response),0);

    //print out the data that we get back
    printf("The server sent the data: %s",server_response);

    close(network_socket);

    return 0;
 }

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <arpa/inet.h>
#define SERV_PORT 5576
int main()
{
    int i, j;
    FILE *fp;
    ssize_t n;
    char filename[80], recvline[80];
    struct sockaddr_in servaddr;
    int network_socket;

    // creating a socket
    network_socket = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&servaddr, sizeof(servaddr));
    // Address family
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    servaddr.sin_addr.s_addr = INADDR_ANY;

    // connect
    connect(network_socket, (struct sockaddr *)&servaddr, sizeof(servaddr));

    printf("enter the file name");
    scanf("%s", filename);
    write(network_socket, filename, sizeof(filename));
    printf("\n data from server: \n");
    while (read(network_socket, recvline, 80) != 0)
    {
        fputs(recvline, stdout);   
    }

    // close the socket
    close(network_socket);
}