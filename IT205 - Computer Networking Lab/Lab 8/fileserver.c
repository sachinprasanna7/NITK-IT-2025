//server for file transfer:fileserver.cc

#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<sys/types.h>
#define SERV_PORT 5576
int main(int argc,char **argv)
{
int i,j,count=0;
ssize_t n;
FILE *fp;
char f[80],res1[5];
char res[50]="The number of characters in the file is ";
struct sockaddr_in servaddr,cliaddr;
int listenfd,connfd,clilen;
listenfd=socket(AF_INET,SOCK_STREAM,0);
bzero(&servaddr,sizeof(servaddr));
servaddr.sin_family=AF_INET;
servaddr.sin_port=htons(SERV_PORT);
bind(listenfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
listen(listenfd,1);
clilen=sizeof(cliaddr);
connfd=accept(listenfd,(struct sockaddr*)&cliaddr,&clilen);
printf("\n Clinet is connected");

read(connfd,f,80);

printf("\nThe name of the file sent is: %s\n",f);

read(connfd,f,500);

for(int i=0;i<strlen(f);i++)
{
if(f[i]!=' ')
count++;
}

sprintf(res1,"%d",count);
strcat(res,res1);
printf("%s\n",res);


write(connfd,res,sizeof(res));

close(listenfd);

}

