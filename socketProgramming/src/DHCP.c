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

void int_to_ip(unsigned int ip, char *buffer) {
    struct in_addr addr;
    addr.s_addr = htonl(ip);
    if (inet_ntop(AF_INET, &addr, buffer, INET_ADDRSTRLEN) != 1)
    {
        err_sys("while converting the ip address");
        return;  
    }
}


void init_pool(IPAddressPool *pool, const char *start_ip, const char *end_ip){
    
    int start = ip_to_int(start_ip); 
    int end = ip_to_int(end_ip); 

    if (end <= start){
        printf("Invalid IP address range. \n"); 
        return -1; 
    }

    pool->pool_size = end - start + 1; 
    for (int i = 0; i < pool->pool_size; i++){
        int_to_ip(start+i, pool->IP_address[i]);
    }
    memset(pool->allocated, 0, sizeof(pool->allocated));
}

int checkout_ip(IPAddressPool *pool, char *mac_address, char *assigned_ip){
    for(int i=0; i<pool->client_count; i++){
        
        if (strcmp(pool->clients[i].mac_address, mac_address) == 0){
            strcpy(assigned_ip, pool->clients[i].ip_address); 
            return  1;  
        }
    }
    
    if (pool->client_count > MAX_CLIENT){

        printf("%%Error when assigning ip address to new client: no extra client. \n"); 
        return 0; 
    }


    for (int i=0; i<pool->pool_size; i++){
        if (pool->allocated[i] == 0){
            strcpy(assigned_ip, pool->IP_address[i]); 
            pool->allocated[i] = 1; 

        strcpy(pool->clients[pool->client_count].mac_address, mac_address); 
        strcpy(pool->clients[pool->client_count].ip_address, assigned_ip); 
        pool->clients[pool->client_count].lease_start = time(NULL);        
        pool->client_count++ ;
        
        
        return 1;   
        
        }
    }
    return 0; 


}


int releasing_ip(IPAddressPool *pool, char *mac_address){
    for(int i=0; i<pool->client_count; i++){
        if (strcmp(pool->clients[i].mac_address, mac_address) == 0){
            for (int j=0; j<pool->pool_size; j++){
                if (strcmp(pool->clients[i].ip_address, pool->IP_address[j]) == 0){
                    pool->allocated[j] = 0;
                    memset(pool->clients[i].ip_address, 0, sizeof(INET_ADDRSTRLEN)); 
                    pool->clients[i].lease_start = 0; 
                    pool->clients[i].lease_end = 0; 
                }
            }
            for (int k = i; k < pool->client_count - 1; k++) {
                        pool->clients[k] = pool->clients[k + 1];
                    }
            pool->client_count--;
            return 1;  
        }
    }
    printf("Error while looking for this client with %s", mac_address); 
    return 0; 
}