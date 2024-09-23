#include "DHCP.h"

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