#include "DHCP.h"


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