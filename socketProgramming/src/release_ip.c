#include "common.h"

int release_ip(struct IPAddressPool *pool, const char *device_id) {
    for (unsigned int i = 0; i < POOL_SIZE; i++)
    {
        if(strcmp(pool->device_ids[i], device_id) == 0){
            unsigned int current_ip = pool->ip_start + i; 
            if (pool->leased[i]){
                    pool->leased[i] = 0; 
                    memset(pool->device_ids[i], 0, DEVICE_ID_LEN); 
                    return 1; 
            }
        }
    }
    return 0;
}