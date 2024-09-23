#include <stdio.h>
#include <time.h>
#include "common.h"


#define MAX_CLIENT 20 
#define MAX_POOL 20

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


unsigned int ip_to_int(const char *ip); 

void int_to_ip(unsigned int ip, char *buffer); 

// Initializing the IP pool, with defined range of addresses and mark all IPs as available initially
void init_pool(IPAddressPool *pool, const char *start_ip, const char *end_ip); 


// Check the IP pool for an available IP and assing it temporarily
int checkout_ip(IPAddressPool *pool, char *mac_address, char *assigned_ip); 

// marks the ip address as available 
int releasing_ip(IPAddressPool *pool, char *mac_address); 

