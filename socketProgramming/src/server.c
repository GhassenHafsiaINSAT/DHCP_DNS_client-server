#include "common.h"
#include "DHCP.h"


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
    
    IPAddressPool pool;
    init_pool(&pool, "192.168.1.10", "192.168.1.30");  
    
    for ( ; ; ){
        printf("listening on port 67 %% DHCP SERVER PORT\n");     
        clilen = sizeof(cliaddr); 
        
        connfd = accept(listenfd, (struct sockaddr *) &cliaddr, &clilen); 
        
        if ((childpid = fork()) == 0){
            close(listenfd); 
            char buffer[128];
            if (read(connfd, buffer, sizeof(buffer)) < 0)
                err_sys("read error");

            char command[10], mac_address[18];
            sscanf(buffer, "%s %s", mac_address, command); 

            printf("Received Command: %s, MAC Address: %s\n", command, mac_address);

            if (strcmp(command, "CHECKOUT") == 0) {

                char assigned_ip[INET_ADDRSTRLEN];
                if (checkout_ip(&pool, mac_address, assigned_ip)) {
                    printf("Client %s assigned IP: %s\n", mac_address, assigned_ip);
                    if (write(connfd, assigned_ip, sizeof(assigned_ip)) < 0)
                        err_sys("write error");

                } else {
                    printf("No IP available for client %s\n", mac_address);
                    strcpy(assigned_ip, "0.0.0.0");
                    if (write(connfd, assigned_ip, sizeof(assigned_ip)) < 0)
                        err_sys("write error");
                }

            } else if (strcmp(command, "RELEASE") == 0) {
                
                if (releasing_ip(&pool, mac_address)) {
                    printf("Released IP for client %s\n", mac_address);
                
                    char response[] = "IP Released Successfully";
                    if (write(connfd, response, strlen(response)) < 0)
                        err_sys("write error");
                } else {
                    printf("Failed to release IP for client %s\n", mac_address);
                

                    char response[] = "IP Release Failed";
                    if (write(connfd, response, strlen(response)) < 0)
                        err_sys("write error");
                }
            }

            exit(0); 
        }

        close(connfd); 
    }
}