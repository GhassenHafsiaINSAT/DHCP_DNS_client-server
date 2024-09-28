#include "common.h"

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
