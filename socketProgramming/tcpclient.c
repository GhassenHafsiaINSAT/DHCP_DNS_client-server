#include "common.h"

int main(int argc, char **argv){

    //local variables
    int sockfd, n; 
    int sendbytes; 
    struct sockaddr_in servaddr; 
    char sendline[MAXLINE]; 
    char recvline[MAXLINE]; 

    //Create a socket
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0))< 0){ // 0 == tcp by default
        HANDLE_ERROR("while creating the socket"); 
    }
    /*  using bzero is to zero a block of memory, 
        to ensure that a structure starts with clean status*/
    bzero(&servaddr, sizeof(servaddr)); 
    servaddr.sin_family = AF_INET; 
    servaddr.sin_port = htons(SERVER_PORT); 

    // establish a connection to a server specified by the address provided in servaddr
    if(connect(sockfd,(struct sockaddr *) &servaddr, sizeof(servaddr)) <0 )
    {
        HANDLE_ERROR("while connecting to the server"); 
    }

    sprintf(sendline, "GET / HTTP/1.1\r\nHost: localhost:18000\r\nConnection: close\r\n\r\n"); 
    sendbytes = strlen(sendline); 

    if (write(sockfd, sendline, sendbytes) != sendbytes){
        HANDLE_ERROR("while writing to the socket"); 
    }

    // recieve the response
    memset(recvline,0,MAXLINE); 

    while ((n=read(sockfd, recvline,MAXLINE - 1)) > 0)
    {
        printf("%s", recvline); 
    }
    if (n<0)    HANDLE_ERROR("while reading"); 

    exit(0); 
}  