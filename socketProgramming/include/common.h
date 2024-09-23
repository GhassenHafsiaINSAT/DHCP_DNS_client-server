#ifndef COMMON_H
#define COMMON_H

#include <sys/socket.h> // basic socket definition
#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>     // String manipulation function
#include <unistd.h>
#include <arpa/inet.h>  // definition for internet operations like socket and bind
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

// Port
#define SERVER_PORT 9877
#define DHCP_SERVER_PORT 67
#define DHCP_CLIENT_PORT 68

// Buffer Length
#define MAXLINE 4096

// Queue length
#define LISTENQ 10

// Pool size 
#define POOL_SIZE 10

// device ip length
#define DEVICE_ID_LEN 16

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

char *ip;


struct IPAddressPool {
    char ip_start[INET_ADDRSTRLEN]; 
    char ip_end[INET_ADDRSTRLEN]; 
    int leased[POOL_SIZE]; 
    char device_ids[POOL_SIZE][DEVICE_ID_LEN]; 
};

void str_echo(int sockfd); 

Sigfunc* signal(int signo, Sigfunc *func); 

ssize_t readline (int fd, void *vptr, size_t maxlen); 

ssize_t writen(int fd, const void *vptr, size_t n); 

ssize_t readn(int fields, void *buff, size_t nbytes); 

void sig_chld(int signo);

void str_cli(FILE *fp, int sockfd); 

// initialize the IPAddressPool
void init_pool(struct IPAddressPool *pool, const char *start, const char *end); 

unsigned int ip_to_int(const char *ip); 

void int_to_ip(unsigned int ip, char *buffer); 

int checkout_ip(struct IPAddressPool *pool, const char *device_id, char *ip); 

int release_ip(struct IPAddressPool *pool, const char *ip); 

#endif // COMMON_H