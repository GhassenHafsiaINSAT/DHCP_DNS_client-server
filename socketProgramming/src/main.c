#include "common.h"

int main() {
    struct IPAddressPool pool;
    init_pool(&pool, "192.168.1.10", "192.168.1.19");

    char ip[INET_ADDRSTRLEN];
    const char *device_id = "device123";

    if (checkout_ip(&pool, device_id, ip)) {
        printf("Checked out IP: %s for device %s\n", ip, device_id);
    } else {
        printf("No IP available\n");
    }

    if (release_ip(&pool, device_id)) {
        printf("Released IP for device %s\n", device_id);
    } else {
        printf("Failed to release IP for device %s\n", device_id);
    }

    return 0;
}
