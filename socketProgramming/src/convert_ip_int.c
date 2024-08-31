#include "common.h"

unsigned int ip_to_int(const char *ip) {
    struct in_addr addr;
    if (inet_pton(AF_INET, ip, &addr) == 1)
        return ntohl(addr.s_addr);
    else 
    {
        err_sys("while converting the ip address"); 
        return; 
    }   
}

void int_to_ip(unsigned int ip, char *buffer) {
    struct in_addr addr;
    addr.s_addr = htonl(ip);
    if (inet_ntop(AF_INET, &addr, buffer, INET_ADDRSTRLEN) != 1)
    {
        err_sys("while converting the ip address");
        return;  
    }
}
