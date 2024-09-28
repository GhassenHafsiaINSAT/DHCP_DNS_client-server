#ifndef COMMON_H
#define COMMON_H

#include <sys/socket.h> 
#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>     
#include <unistd.h>
#include <arpa/inet.h>  
#include <stdarg.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <netdb.h>
#include <stdlib.h>
#include <stdint.h>
#include <netinet/in.h>
#include <errno.h>
#include <time.h>
#include <signal.h>

// Define the function pointer type for signal handlers
typedef void Sigfunc(int);

// DHCP Pool configurations 
#define MAX_CLIENT 20 
#define MAX_POOL 20

// Port
#define SERVER_PORT 9877
#define DHCP_SERVER_PORT 67
#define DHCP_CLIENT_PORT 68

// Buffer Length
#define MAXLINE 4096

// Queue length
#define LISTENQ 10

#define MAC_LEN 18
#define IP_LEN 16

// Define a macro for error handling
#define HANDLE_ERROR(msg)  do { \
    fprintf(stderr, "Error: %s\n", msg); \
    exit(EXIT_FAILURE); \
} while(0)


#define err_sys(msg) do { \
    fprintf(stderr, "Error: %s : %s\n", msg, strerror(errno)); \
    exit(EXIT_FAILURE); \
} while(0)


#define err_quit(msg) do{ \
    fprintf(stderr,"Error: %s\n", msg); \
    exit(EXIT_FAILURE); \
} while(0)

typedef struct 
{   
    // when client requests an IP address, the server checks if the client already has active lease
    // if it has it reuse the existing ip, if not, it assigns a new one
    
    char mac_address[MAC_LEN]; 
    char ip_address[IP_LEN]; 
    time_t lease_start; 
    time_t lease_end; 
} Client;

typedef struct 

{
    // Represents the whole set of IP addresses managed by the server

    char IP_address[MAX_POOL][INET_ADDRSTRLEN];    // pointer to an array of IP address structure 
    int pool_size;      // number of IP addresses in the pool 
    char allocated[MAX_POOL]; 
    Client clients[MAX_CLIENT]; 
    int client_count; 
} IPAddressPool;


void str_echo(int sockfd); 

Sigfunc* signal(int signo, Sigfunc *func); 

ssize_t readline (int fd, void *vptr, size_t maxlen); 

ssize_t writen(int fd, const void *vptr, size_t n); 

ssize_t readn(int fields, void *buff, size_t nbytes); 

void sig_chld(int signo);

void str_cli(FILE *fp, int sockfd); 

unsigned int ip_to_int(const char *ip); 

void int_to_ip(unsigned int ip, char *buffer); 

// Initializing the IP pool, with defined range of addresses and mark all IPs as available initially
void init_pool(IPAddressPool *pool, const char *start_ip, const char *end_ip); 


// Check the IP pool for an available IP and assing it temporarily
int checkout_ip(IPAddressPool *pool, char *mac_address, char *assigned_ip); 

// marks the ip address as available 
int releasing_ip(IPAddressPool *pool, char *mac_address); 

#endif // COMMON_H