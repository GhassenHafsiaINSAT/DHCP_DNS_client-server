#include "common.h"

int main(int argc, char **argv) {
    int sockfd;
    struct sockaddr_in servaddr;

// checks if the program is run with exactly 3 arguments: The program name, IP address, and a command
    if (argc != 3)

// If the number of arguments is not exactly 3, it will print usage message and exit
        err_quit("usage: client <IPaddress> <COMMAND>");

// Create a socket 
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        err_sys("socket error");

// Zeroing and setting up server address structure 
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERVER_PORT); 

// converts the ip address from string format to binary form 
    if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) < 0)
        err_quit("inet_pton error for");

// The client attempts to establish a connection with the server 
    if (connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0)
        err_sys("connect error");

// Storing MAC address and command
    char command[10];
    strcpy(command, argv[2]); 
    char mac_address[18];
    strcpy(mac_address, argv[3]);

// Sending MAC address and command to the server 
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

// Closing socket and exiting 
    close(sockfd); 
    exit(0);
}

