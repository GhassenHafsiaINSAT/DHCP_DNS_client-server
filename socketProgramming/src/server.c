#include "common.h"

int main(int argc, char **argv){

    int listenfd, connfd; 
    pid_t childpid; 
    socklen_t clilen;
    struct sockaddr_in servaddr, cliaddr; 

    listenfd = socket(AF_INET, SOCK_STREAM, 0); 

    bzero(&servaddr, sizeof(servaddr)); 

    servaddr.sin_family = AF_INET; 
    servaddr.sin_port = htons(DHCP_SERVER_PORT); 
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 

    if (bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0)
        err_sys("bind error"); 

    listen(listenfd, LISTENQ); 

    for ( ; ; ){
        printf("listening on port 67 %% DHCP SERVER PORT\n"); 
        clilen = sizeof(cliaddr); 
        
        connfd = accept(listenfd, (struct sockaddr *) &cliaddr, &clilen); 
        
        if ((childpid = fork()) == 0){
            close(listenfd); 
            str_echo(connfd); 
            exit(0); 
        }

        close (connfd); 

    }

}