#include <stdio.h>
#include <time.h>



typedef struct 
{
    // Tracks if the IP is currently assigned to a device or not
    // Links the IP  to a specific device 
    
    char ip_address[16]; 
    int is_assinged;        // 1 if assigned 0 else
    char device_id[50];     // device ti which the ip address is assigned 

} IPAddress;


typedef struct 

{
    // Represents the whole set of IP addresses managed by the server

    IPAddress *pool;    // pointer to an array of IP address structure 
    int pool_size;      // number of IP addresses in the pool 

} IPAddressPool;


typedef struct 
{   
    // when client requests an IP address, the server checks if the client already has active lease
    // if it has it reuse the existing ip, if not, it assigns a new one
    
    char mac_address[18]; 
    char ip_address[16]; 
    time_t lease_start; 
    time_t lease_end; 
};

// Initializing the IP pool, with defined range of addresses and mark all IPs as available initially
void init_pool(IPAddressPool *pool, const char *start_ip, const char *end_ip); 


// Check the IP pool for an available IP and assing it temporarily
int checkout_ip(IPAddressPool *pool, const char *device_id, char *assigned_ip); 
    // return assigned ip variable 

// marks the ip address as available 
int releasing_ip(IPAddressPool *pool, const char *device_id); 

