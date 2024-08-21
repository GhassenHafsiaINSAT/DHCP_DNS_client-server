#include "str_echo.h"

void str_echo(int sockfd){

    int arg1, arg2; 
    ssize_t n; 
    char buff[MAXLINE]; 

for ( ; ; ){    
    if ((n = readline(sockfd, buff, MAXLINE)) == 0)
        return; 
   
    if (sscanf(buff,"%d%d", &arg1, &arg2) == 2) 
        sprintf(buff, "%d\n", arg1 + arg2); 
   
    else 
        snprintf(buff, sizeof(buff), "input error\n");
   
    n = strlen(buff); 
    writen(sockfd,  buff, n); 
    }

}