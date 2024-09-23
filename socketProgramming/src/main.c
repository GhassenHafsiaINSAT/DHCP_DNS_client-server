#include "common.h"


// The program manages a pool of IP addresses, allowing devices to request en release IP addresses dynamically
int main() {

    // initialize ip address pool, this structure contains a range of IP addresses, tracking which are available and whoch are checked out 
    struct IPAddressPool pool;
    init_pool(&pool, "192.168.1.10", "192.168.1.19");

    char ip[INET_ADDRSTRLEN];
    const char *device_id = "device123";
    // Checkout process, when a device requests an IP address,
    // the program searches for an available IP in the pool, 
    //if it finds one, it assigns that IP address to the device,
    // storing it in ip variable and then prints a confirmation message
    
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
