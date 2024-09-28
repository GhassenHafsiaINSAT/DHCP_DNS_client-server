#include "common.h"


void int_to_ip(unsigned int ip, char *buffer) {
    struct in_addr addr;
    addr.s_addr = htonl(ip);
    if (inet_ntop(AF_INET, &addr, buffer, INET_ADDRSTRLEN) != 1)
    {
        err_sys("while converting the ip address");
        return;  
    }
}