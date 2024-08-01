#include "common.h"


int main(int argc, char** argv){
    int status; 
    struct addrinfo hints, *servinfo; 

    memset(&hints, 0, sizeof(hints)); 
    hints.ai_family = AF_UNSPEC; // don't care IPv4 or IPv6
    hints.ai_socktype = SOCK_STREAM; 
    hints.ai_flags = AI_PASSIVE; //assign the address of my local host to the socket structures

    status = getaddrinfo(NULL, "3490", &hints, &servinfo); 

    freeaddrinfo(servinfo); 

}