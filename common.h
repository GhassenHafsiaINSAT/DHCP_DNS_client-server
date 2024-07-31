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

// standard HTTP port
#define SERVER_PORT 80

#define CLIENT_PORT 18000

// buffer length
#define MAXLINE 4096

#define SA struct sockaddr


//define a macro for error handling

#define HANDLE_ERROR(msg)  do { \
    fprintf(stderr, "Error: %s\n", msg); \
    exit(EXIT_FAILURE); \
} while (0)