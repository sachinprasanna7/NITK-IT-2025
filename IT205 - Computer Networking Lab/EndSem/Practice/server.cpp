 #include <stdlib.h>
 #include <stdio.h>

 #include <sys/types.h>
 #include <sys/socket.h>
 #include <unistd.h>

 #include <netinet/in.h>

int main()
{
    char server_response[256]="You have reached the server";

    //create the server socket
    int server_socket;
    server_socket=socket(AF_INET,SOCK_STREAM,0);

    //define the server address
    struct sockaddr_in server_address;

    server_address.sin_family=AF_INET;
    server_address.sin_port=htons(9002);
    server_address.sin_addr.s_addr = INADDR_ANY;

    //bind the socket to our specified IP and port
    bind(server_socket,(struct sockaddr*) &server_address, sizeof(server_address));

   listen(server_socket,5);

   int client_socket;
   client_socket=accept(server_socket, NULL, NULL);

   send(client_socket,server_response, sizeof(server_response),0);

   //close the socket
   close(server_socket);

   return 0;
}

// #include <stdio.h>

// #include <unistd.h>
// #include <string.h>
// #include <sys/socket.h>
// #include <netinet/in.h>
// #include <sys/types.h>
// #define SERV_PORT 5576
// int main(int argc, char **argv)
// {
//     int i, j;
//     ssize_t n;
//     FILE *fp;
//     char s[80], f[80];
//     struct sockaddr_in servaddr, cliaddr;
//     int server_socket, client_socket, clilen;

//     // creating the server socket.
//     server_socket = socket(AF_INET, SOCK_STREAM, 0);
//     // clear the servaddr.
//     bzero(&servaddr, sizeof(servaddr));

//     // creating the servaddr family.
//     servaddr.sin_family = AF_INET;
//     servaddr.sin_port = htons(SERV_PORT);
//     servaddr.sin_addr.s_addr = INADDR_ANY;

//     // Bind the socket to the address.
//     bind(server_socket, (struct sockaddr *)&servaddr, sizeof(servaddr));

//     // listen for any incoming connections
//     listen(server_socket, 3);
//     clilen = sizeof(cliaddr);

//     // accept function.
//     client_socket = accept(server_socket, (struct sockaddr *)&cliaddr, &clilen);
//     printf("\n client connected");
    
//     read(client_socket, f, 80);
//     fp = fopen(f, "r");
//     printf("\n name of the file: %s", f);
//     printf("\n");
//     while (fgets(s, 80, fp) != NULL)
//     {
//         printf("%s", s);
//         write(client_socket, s, sizeof(s));
//     }

//     close(server_socket);
//     fclose(fp);

// } // close main