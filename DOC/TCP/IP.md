## TUN/TAP

- TUN (network tunnel) and TAP (network TAP) are kernel virtual network devices.

- TUN simulates network layer device and operates in layer 3 carrying IP packets.

- TAP simulates link layer device and operates in second layer 2 carrying ethernet packets.  

- TUN is used with routing

- TAP is used to create a user space network bridge.  

- To intercept low-level network traffic from the linux kernel, we will use TAP device.

- you can create TUN/TAP device using `ip tuntap`: 
```sh
udo ip tuntap add dev tun0 mode tun

# Creating a TAP device
sudo ip tuntap add dev tap0 mode tap

# Bring up the device
sudo ip link set tun0 up
sudo ip link set tap0 up
```

- **Tunneling** is where packet is wrapped inside the playload of another packet

## struct ifreq

- To work with network interfaces, we use `struct ifreq`, defined in `<net/if.h>` header file

```c
           struct ifreq {
               char ifr_name[IFNAMSIZ]; /* Interface name */
               union {
                   struct sockaddr ifr_addr;        // store IP address
                   struct sockaddr ifr_dstaddr;     // store network mask
                   struct sockaddr ifr_broadaddr;   // store broadcast address
                   struct sockaddr ifr_netmask;     // store destination address
                   struct sockaddr ifr_hwaddr;      // store MAC address
                   short           ifr_flags;
                   int             ifr_ifindex;
                   int             ifr_metric;
                   int             ifr_mtu;
                   struct ifmap    ifr_map;
                   char            ifr_slave[IFNAMSIZ];
                   char            ifr_newname[IFNAMSIZ];
                   char           *ifr_data;
               };
           };
```

## ioctl

- ioctl (input/output control) is a system call in Unix-like based systems, including linux, provides a way control operations on devices, such as file descriptors, network interfaces