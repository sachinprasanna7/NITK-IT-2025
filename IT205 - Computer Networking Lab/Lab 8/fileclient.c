//file transfer client program:fileclient.cc

#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<arpa/inet.h>
#define SERV_PORT 5576
int main()
{
int i,j,ind=0;
FILE *fp;
ssize_t n;
char filename[80],recvline[80],contnt[80];
struct sockaddr_in servaddr;
int sockfd;
sockfd=socket(AF_INET,SOCK_STREAM,0);
bzero(&servaddr,sizeof(servaddr));
servaddr.sin_family=AF_INET;
servaddr.sin_port=htons(SERV_PORT);

servaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
connect(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
printf("enter the file name :");
scanf("%s",filename);
write(sockfd,filename,sizeof(filename));

fp=fopen(filename,"r");
for(char c=getc(fp); c!=EOF;c=getc(fp))
{
contnt[ind]=c;
ind++;
}
write(sockfd,contnt,sizeof(contnt));

printf("Data from server:\n");

while(read(sockfd,recvline,80)!=0)
{
fputs(recvline,stdout);
}
printf("\n");
close(sockfd);
fclose(fp);
}

