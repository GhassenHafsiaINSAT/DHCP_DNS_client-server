#include "common.h"

int main(int argc, char **argv){
    int listenfd, connfd; 
    pid_t childpid; 
    struct sockaddr_in servaddr, cliaddr; 
    time_t ticks; 
    char buff[MAXLINE]; 

    listenfd = socket(AF_INET, SOCK_STREAM, 0); 

    bzero(&servaddr, sizeof(servaddr)); 

    servaddr.sin_family = AF_INET; 
    servaddr.sin_port = htons(13); 
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 

    if (bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0)
        err_sys("bind error"); 

    listen(listenfd, LISTENQ); 

    for ( ; ; ){
        printf("listening on port 13\n"); 
        
        connfd = accept(listenfd, (struct sockaddr *) &cliaddr, sizeof(cliaddr)); 
        
        if ((childpid = fork()) == 0){
            close(listenfd); 
            str_echo(connfd); 
            exit(0); 
        }

        close (connfd); 

    }

}