#include "common.h"

void init_pool(struct IPAddressPool *pool, const char *start, const char *end) {
    strcpy(pool->ip_start, start);
    strcpy(pool->ip_end, end);
    memset(pool->leased, 0, sizeof(pool->leased)); 
    memset(pool->device_ids, 0, sizeof(pool->device_ids)); 
}



