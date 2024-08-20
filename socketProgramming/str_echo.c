#include "str_echo.h"

void str_echo(int sockfd){

    ssize_t n; 
    char buff[MAXLINE]; 

    again: 
    while ((n = read(sockfd, buff, MAXLINE)) > 0)
        write(sockfd, buff, n); 
    
    if (n>0 && errno == EINTR)
        goto again; 
    else if(n<0)
        err_sys("str_echo: read error"); 

}