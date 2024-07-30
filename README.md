# Network Programming

## What is socket?
- A socket is a way to speak to other programs, using standard Unix file descriptors.

- When Unix programs do any ort of I/O, they do by reading or writing file descriptor.

- A file descriptor is simply an integer associated with an open file, it can be also a network connection, FIFO, a pipe, a terminal.

- You can commincate through the socket using `read()` and `write()`, but `send()` and `recv()` offer much grater control over your data transmission.

## Two types of sockets
- **Stream sockets**:

  - Are referred to as `SOCK_STREAM`, are reliable two-way connected communication streams.
  - `telnet` and `ssh` applications use stream sockets.
  - They achieve high level of data transmission quality by using TCP, it makes sure that data arrives sequentially and error-free.

- **Datagram sockets**:

   - Are referred to as `SOCK_DGRAM`, are not reliable, if you send a datagram, it may arrive, may arrive out of order. If it arrives, the daat inside the packet will be error-free.
  - They use UDP, so they are really fast.
  - They are connectionless, they dont have to maintain an open connectinon, you have to build the packet with IP header on it and send it out.
  - multiplayer games and streaming audio, video use datagram sockets, where dropping few packets is not the end of world.    

## IP addresses

- The address `::1` is a loopback address, it means that the machine is running on now, in IPv4, the loopback address is `127.0.0.1` .

## Port numbers
- Stream sockets and datagram sockets use besides IP addresses, port numbers, a 16-bit number and like the local address for the connection.
- Different services on the internet have different well-known port numbers:
  - HTTP is port 80
  - telnet is port 23
  - SMTP is port 25...
- You can find all these ports under the `/etc/services`
- Port under 1024 are considered special and usually require a special OS prvileges to use

## Byte order
- **Byte Order Basics**:
  - In the internet world, to represent a two-byte hex number, say `b34f`, you'll store it in two sequential bytes `b3` followed by `4f`, this number is stored  with the big end first, it's called Big-endian.

  - Computers with intel or intel-compatible processor, store the bytes reversed, so b34f would be stored in memory as the sequential bytes 4f followed by b3. This storage method is called Little-Endian.

- **Network and Host Byte Order**:

    - Network Byte Order: Always Big-Endian. Used for data transmission over networks.
    - Host Byte Order: Varies by machine. For example Intel (80x86) uses Little-Endian.

- **Why Conversion Matters?**:

  - When sending data over a network, you need to convert numbers to Network Byte Order to ensure consistent interpretation by all devices.

- **Conversion Functions**:

    - htons(): Host to Network Short (2 bytes)
    - htonl(): Host to Network Long (4 bytes)
    - ntohs(): Network to Host Short (2 bytes)
    - ntohl(): Network to Host Long (4 bytes)
 
## Structs
- The structure is used to prep the socket address structures for subsequent use and hostname and service name lookups.

- **Socket Descriptor**: Just an `int`.

### Structs for IP Addresses:
1. **struct addrinfo**:
```c
struct addrinfo {
int                 ai_flags;          // AI_PASSIVE, AI_CANONNAME, etc.
int                 ai_family;         // AF_INET (IPv4), AF_INET6 (IPv6), AF_UNSPEC (any)
int                 ai_socktype;       // SOCK_STREAM, SOCK_DGRAM
int                 ai_protocol;       // use 0 for "any"
size_t              ai_addrlen;        // size of ai_addr in bytes
struct sockaddr     *ai_addr;          // struct sockaddr_in or _in6
char                *ai_canonname;     // full canonical hostname

struct addrinfo *ai_next;              // linked list, next node

};
```
   - Used to set up socket addresses.
   - Contains fields like `ai_family`, `ai_socktype`, `ai_protocol`, etc.
   - Call `getaddrinfo()` to fill this struct with necessary data, it returns a pointer to a new linked list.

2. **struct sockaddr**:

```c
struct sockaddr {
unsigned short    sa_family;        // address family, AF_xxx
char              sa_data[14];      // 14 bytes of protocol address
};
```
   - Holds generic socket address information.
   - Contains `sa_family` (address family) and `sa_data` (address and port info).

3. **struct sockaddr_in** (for IPv4):
```c
// (IPv4 only--see struct sockaddr_in6 for IPv6)
struct sockaddr_in {
short int              sin_family;      //  Address family, AF_INET
unsigned short int     sin_port;        //  Port number
struct in_addr         sin_addr;        //  Internet address
unsigned char          sin_zero[8];     //  Same size as struct sockaddr
};
```

   - Specialized version of `struct sockaddr` for IPv4.
   - Contains `sin_family` (AF_INET), `sin_port` (port number), `sin_addr` (IP address), and padding.

4. **struct in_addr**:
```c
// (IPv4 only--see struct in6_addr for IPv6)
// Internet address (a structure for historical reasons)
struct in_addr {
uint32_t s_addr; // that's a 32-bit int (4 bytes)
};
```
   - Contains a single field `s_addr`, which is the IPv4 address.

### Structs for IPv6:
1. **struct sockaddr_in6**:
```c
// (IPv6 only--see struct sockaddr_in and struct in_addr for IPv4)
struct sockaddr_in6 {
u_int16_t         sin6_family;    // address family, AF_INET6
u_int16_t         sin6_port;      // port number, Network Byte Order
u_int32_t         sin6_flowinfo;  // IPv6 flow information
struct in6_addr   sin6_addr;      // IPv address
u_int32_t         sin6_scope_id;  // Scope ID 

};
```

   - Similar to `struct sockaddr_in` but for IPv6.
   - Contains `sin6_family`, `sin6_port`, `sin6_flowinfo`, `sin6_addr` (IPv6 address), and `sin6_scope_id`.

2. **struct in6_addr**:
```c
struct in6_addr {
unsigned char s6_addr[16]; // IPv6 address
};
```
   - Contains a field `s6_addr`, which is the IPv6 address.

### General Purpose Struct:
- **struct sockaddr_storage**:
```c
struct sockaddr_storage {
sa_family_t ss_family;       // address family
// all this is padding, implementation specific, ignore it:
char       __ss_pad1[_SS_PAD1SIZE];
int64_t    __ss_align;
char       __ss_pad2[_SS_PAD2SIZE];
};
```
   - Large enough to hold both IPv4 and IPv6 addresses.
   - Use `ss_family` to check if it's AF_INET (IPv4) or AF_INET6 (IPv6) before casting to the appropriate struct.

### Usage Tips:
- Use `getaddrinfo()` to get the necessary address info in a `struct addrinfo`.
- Use `struct sockaddr_in` for IPv4 addresses.
- Use `struct sockaddr_in6` for IPv6 addresses.
- Always convert port numbers to Network Byte Order using `htons()`.
