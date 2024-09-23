#include "common.h"

int main(int argc, char **argv) {
    int sockfd;
    struct sockaddr_in servaddr;

    if (argc != 2)
        err_quit("usage: client <IPaddress>");

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        err_sys("socket error");

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERVER_PORT); 

    if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) < 0)
        err_quit("inet_pton error for");

    if (connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0)
        err_sys("connect error");

    char command[10];
    strcpy(command, argv[2]); 
    char mac_address[18];
    strcpy(mac_address, argv[3]);

    
    if (write(sockfd, mac_address, sizeof(mac_address)) < 0)
        err_sys("write error");
    if (write(sockfd, command, sizeof(command)) < 0)
        err_sys("write error");



    if (strcmp(command, "CHECKOUT") == 0) {
        char assigned_ip[INET_ADDRSTRLEN];
        if (read(sockfd, assigned_ip, sizeof(assigned_ip)) < 0)
            err_sys("read error");

        printf("Assigned IP: %s\n", assigned_ip);
    }

    close(sockfd); 
    exit(0);
}

