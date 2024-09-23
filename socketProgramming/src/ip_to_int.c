#include "DHCP.h"

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