#include "common.h"

int main(int argc, char **argv){

    /* file descriptors for the listening and connection sockets
       n number to store the number of bytes read from the connection*/
    int listenfd, connfd, n; 

    // a structure to hold the server address information
    struct sockaddr_in servaddr; 
    char buff[MAXLINE+1];
    char recvline[MAXLINE]; 

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
            memset(recvline, 0, MAXLINE); 
        }

        if(n<0) HANDLE_ERROR("read error"); 


        //send a response
        snprintf((char*)buff, sizeof(buff), "HTTP/1.0 200 OK \r\n\rHELLO"); 

        write(connfd, (char*)buff, strlen((char*)buff)); 
        close(connfd); 
    }
}
//localhost on my brower
