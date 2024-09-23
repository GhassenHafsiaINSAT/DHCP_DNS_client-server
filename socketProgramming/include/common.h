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


void str_echo(int sockfd); 

Sigfunc* signal(int signo, Sigfunc *func); 

ssize_t readline (int fd, void *vptr, size_t maxlen); 

ssize_t writen(int fd, const void *vptr, size_t n); 

ssize_t readn(int fields, void *buff, size_t nbytes); 

void sig_chld(int signo);

void str_cli(FILE *fp, int sockfd); 

#endif // COMMON_H