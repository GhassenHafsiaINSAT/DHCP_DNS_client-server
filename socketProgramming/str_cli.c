#include "str_cli.h"

void str_cli(FILE *fp, int sockfd){
    char sendline[MAXLINE], recvline[MAXLINE]; 

    while(fgets(sendline, MAXLINE, fp) != NULL){
        write,(sockfd, sendline, strlen(sendline)); 

        if (readline(sockfd, recvline, MAXLINE) == 0)
            err_quit("str_cli: server terminated prematurely"); 

        fputs(recvline, stdout); 

    }
}