#include "common.h"

void str_cli(FILE *fp, int sockfd){

/*
    - The fucntion reads user input, sends it the server,
    waits for a response, and prints it out 
    - It handles the case where the server closes the connection unexpectedly
*/


    char sendline[MAXLINE], recvline[MAXLINE]; 

    while(fgets(sendline, MAXLINE, fp) != NULL){
        writen(sockfd, sendline, strlen(sendline)); 

        if (readline(sockfd, recvline, MAXLINE) == 0)
            err_quit("str_cli: server terminated prematurely"); 

        fputs(recvline, stdout); 

    }
}