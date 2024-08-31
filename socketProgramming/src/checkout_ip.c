#include "common.h"

int checkout_ip(struct IPAddressPool *pool, const char *device_id, char *out_ip) {
    for(unsigned int i=0; i<POOL_SIZE; i++){
        unsigned int current_ip = pool->ip_start + i;
        if (!pool->leased[i] && current_ip <= pool->ip_end) {
            pool->leased[i] = 1; 
            strncpy(pool->device_ids[i], device_id, DEVICE_ID_LEN); 
            pool->device_ids[i][DEVICE_ID_LEN - 1] = '\0'; 
            int_to_ip(current_ip, out_ip);
            return 1; 
        }
    }
    return 0; 
}
