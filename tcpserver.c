#include <sys/socket.h>  // basic socket definition
#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdarg.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <netdb.h>
#include <stdlib.h>

#define SERVER_PORT 18000 

#define BUFFER_SIZE 4096

#define SA struct sockaddr


int main(int argc, char **argv){

    int                     listenfd, connfd, n; 
    struct sockaddr_in      servaddr; 
    unit8_t                 buff[MAXLINE+1];
    unit8_t                 recvline[MAXLINE]; 

    if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    HANDLE_ERROR("socket error");

    bzero(&servaddr,sizeof(servaddr)); 
    servaddr.sin_family = AF_INET; 
    servaddr.sin_port = htons(SERVER_PORT); 
    servaddr.sin_addr.s_addr = htons(INADDR_ANY); 


    if ((bind(listenfd, (SA *) &servaddr, sizeof(servaddr))) <0)
        HANDLE_ERROR("bind error"); 

    if ((listen(listenfd, 10)) <0) 
        HANDLE_ERROR("listen error"); 

    for ( ; ; ) {
        struct sockaddr_in addr; 
        socklen_t addr_len; 

        printf("waiting for a connection on port %d\n", SERVER_PORT); 
        fflush(stdout); 
        connfd = accept(listenfd, (SA *) NULL, NULL);
        // zero out the recieve buffer to make sure it ends ip null
        memset(recvline, 0, MAXLINE); 
        // read the client message
        while((n=read(connfd, recvline, MAXLINE-1) ) >0)
        {
            fprintf(stdout, "\n%s\n", recvline);

            if (recvline[n-1] == 'n'){
                break;  
            }
            memset((recvline, 0, MAXLINE)); 
        }

        if(n<0) HANDLE_ERROR("read error"); 


        //send a response
        snprintf((char*)buff, sizeof(buff), "HTTP/1.0 200 OK \r\n\rHELLO"); 

        write(connfd, (char*)buff, strlen((char*)buff)); 
        close(connfd); 
    }
}
//localhost on my brower
