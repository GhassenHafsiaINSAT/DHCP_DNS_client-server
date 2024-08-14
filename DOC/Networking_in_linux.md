# Networking Fundamentals

## Table of Contents
1. [Introduction to Networking](#introduction-to-networking)
2. [OSI and TCP/IP Models](#osi-and-tcpip-models)
3. [Network Packets](#network-packets)
4. [Address Resolution Protocol (ARP)](#address-resolution-protocol-arp)
5. [Domain Name System (DNS)](#domain-name-system-dns)
6. [Encapsulation Process](#encapsulation-process)
7. [Application Layer Functions](#application-layer-functions)

## Introduction to Networking

- **Network Definition**: Computers communicating with each other to share data.

- **Networking to an embedded developer aims for two main purposes**:
    - Connect to a remote machine or to the interent, using an ethernet connection.  
    - Connect a host machine to the embedded target, using JTAG connection, serial console connection, ethernet connection.  

- **Internet Components**: Routers, switches, firewalls.
- **Ethernet**: Typically used for connecting devices to a network via switches.
- **Switch**: Connects multiple devices together to form a network and operates at Layer 2 of the OSI model using MAC addresses.
- **Router**: Connects two or more networks and operates at Layer 3 using IP addresses.
- **Firewall**: Protects your network by controlling incoming and outgoing network traffic.
- **Wireless Access Point**: Enables wireless connectivity for devices.
- **Hub**: Basic device that sends messages to all connected devices, considered 'dumb'.
- **Switch Functionality**: Knows the Layer 2 (MAC) address of each connected device; MAC addresses are unique and immutable.
- **Network Layers**:
  - **Layer 1 (Physical Layer)**: Physical aspects like electrical wires; includes hubs and repeaters.
  - **Layer 2 (Data Link Layer)**: Handles switches, bridges, and frames.
  - **Layer 3 (Network Layer)**: Deals with IP addresses and routers; routers connect networks.

## Network interface 

- The computer/board have one or more network interfaces, (ethernet NIC card, wifi port)
```sh
$ ifconfig                     // Show available interfaces
$ ifconfig -s                  // Show available interfaces with less details
$ ifconfig interface up/dwon   // Show a specific interface with the option to activate or desactivate
```
## The MAC address 

- The MAC address is also called the Hardware Address, set for each NIC card.
- Within each LAN, MAC address is used for communication inside the LAN, however the MAC address is no longer enough to communicate between the devices in different LANs, that's why we need network addressing using IP Addresses.

## IP address

- Any network interface on a machine in the network is identified by its IP address.
- The address IP, show you to reach the internet server, but it is not enough to choose a specific service (HTTP (web services), FTP service, telnet services...), that's why we need port number.
- IP address can  be allocated in two different ways:
    - Statically allocated, manually or startup code.  
    - Dynamically allocated, via a **DHCP server**.
```sh
$ if config <interface><IP Address>                  // set statically the ip address to an interface
$ if config <interface><IP Address>netmask<netmask>  
$ if config <interface>netmask<netmask>              // set statically the netmask to an interface
```
- **Special IP addresses**
  
  - 127.0.0.1 : local host, used for loop back address.
  - Any address ending with all ones (after the subnet mask), is a broadcast address within this subnet.
  - xxx.xxx.xxx.1 : the default gateway.

## Port number 

- port numbers identify services within the same IP address.
- Each connection will have both source port and destination port numbers.
- It is part of transport layer. 
- 0~65,535
    - 0~1,024 well known
    - 1,024~49,125 registered
    - 49,152~65,535 Dynamic/private

## Subnet

- To facilitate Routing, the machines are organized into small networks (subnets).
- Subnets share the upper part of IP address:
  - Subnet 1 : 132.201.1.x
  - Subnet 2 : 132.201.2.x 
  - Subnet 3 : 132.201.3.x 
- The part of IP address shared among the interfaces within the subnet, is expressed as the **subnet mask**.

## Address Resolution Protocol (ARP)
- It Translates IP addresses into MAC addresses to help devices locate each other on a local network.
- The machine should have a table that maps IP addresses to MAC addresses within its subnet, this table called ARP table.

## Domain Name System (DNS)
- DNS is used to map IP addresses into names.  

- Order of Lookup:
	- /etc/hosts: The system first checks this file for hostname-to-IP mappings. If a match is found, it uses that IP address.
	- DNS Servers (via /etc/resolv.conf): If the hostname is not found in /etc/hosts, the system queries the DNS servers listed in /etc/resolv.conf.

### DNS Query
- A DNS query is a demand for information sent from a user's computer to a DNS server, asking for the IP address associated with a domain name.


## Dynamic Host Configuration protocol (DHCP)
- DHCP is used to obtain an IP address when a host or device fisrt comes on the network.
- Here is how DHCP process works:
  	1. When a computer starts up, it sends a DHCP request out on the network.
  	2. The DHCP server responds with the IP address configuration for that device.
	3. That IP address is marked as reserved so that it's not assigned to some other device.

## OSI and TCP/IP Models

- **TCP/IP Model Layers**:
  
  - **Physical Layer**: Ethernet cables.
  - **Network Layer**: IP addresses and routers.
  - **Transport Layer**: TCP (reliable) and UDP (faster).
  - **Application Layer**: Protocols used in applications (e.g., web browsers).
- **OSI Model Layers**:
  
  - **Layer 7**: Application
  - **Layer 6**: Presentation
  - **Layer 5**: Session
  - **Layer 4**: Transport
  - **Layer 3**: Network
  - **Layer 2**: Data Link
  - **Layer 1**: Physical

## Utility Appications

- **Ping** is the most basic network test tool, checking network connectivity or the round trip delay to the destination.
- It sends ICMP packet across the network and notifies you whether there is a response.
```sh
$ ping www.google.com
PING www.google.com (142.250.180.132) 56(84) bytes of data.
64 bytes from mil04s43-in-f4.1e100.net (142.250.180.132): icmp_seq=1 ttl=115 time=33.5 ms
64 bytes from mil04s43-in-f4.1e100.net (142.250.180.132): icmp_seq=2 ttl=115 time=33.7 ms
64 bytes from mil04s43-in-f4.1e100.net (142.250.180.132): icmp_seq=3 ttl=115 time=33.5 ms
```
- Time to live TTL: field in the packet

- **traceroute** : probes the network between the local system and a destination, gathering information about each IP router in the path.
```sh
traceroute www.facebook.com
```

## Collecting Network Statistics and Counters 
- When performing network troubleshooting, its always good to gather some statistics.
```sh
$ netstat 	// Show us the active processes that have the network interface open

Active Internet connections (w/o servers)
Proto Recv-Q Send-Q Local Address           Foreign Address         State      
tcp        0      0 ghassen-VivoBook-:56790 mrs08s19-in-f22.1:https TIME_WAIT  
tcp        0      0 ghassen-VivoBook-:55436 mil04s29-in-f14.1:https ESTABLISHED
tcp        0      0 ghassen-VivoBook-:55160 lb-140-82-114-26-:https ESTABLISHED
tcp        0      0 ghassen-VivoBook-:56798 mrs08s19-in-f22.1:https TIME_WAIT  
tcp        0      0 ghassen-VivoBook-:42538 mrs08s19-in-f4.1e:https TIME_WAIT 
```


### Network Interface Bounding
- It is useful when you need more bandwisth than a single interface can provide.  

- To bound multiple Ethernet interfaces into a single network interface.  
```sh
sudo ip link add bond0 type bond mode 802.3ad
sudo ip link set eth0 master bond0
sudo ip link set eth1 master bond0
sudo ip link set eth2 master bond0
```
![image](https://github.com/GhassenHafsiaINSAT/HackerRank-The_Linux_Shell/assets/110825502/ed9b7868-84a4-4070-8002-b9555e24d00b)

## General structure

- The user accesses a remote machine for different purposes: copying files, accessing terminal in the remote machine, accessing the gui of the remote machine
    - The user runs a client application on his local machine
    - The remote machine will be running a server application
    - The server application will be running on a Daemon process waiting for a connection from the client side

## Remote Access of Machine 
### telnet protocol
```sh
$ telnet <destination address>
```
- telnet enable the user at the client side to access a remote machine by opening terminal on it.  
- A server application must be running on the destination machine to accept client connections.   

### Transporting files (ftp protocol) 
```sh
$ ftp <remote machine address>

get myfile.txt        # get files from remote machine
mget *.exe            # get multiple files from remote machine
put myfile.txt        # send file to remote machine
bye                   # exit session 
```
- ftp enables the client to move files from/to remote machine

Both telnet and FTP do not use a secured connection, information travel between local and remot machine in clear text.  

### SSH protocol 
```sh
$ ssh <destination address>
```
- same as telnet protocol except for that the connection will be secured.

### Secure file copy 
```sh
$ scp <remote server>: <remote filename>
$ scp <local filename><user>:.
## Understanding Linux Internetworking
```
## wget 
```sh
wget <url of the file>
```
- donwloading file from the internet from command line, useful in scripts.


## Bridging 
- When you want to pass traffic between two networrk interfaces, you can create a **bridge**
```sh
sudo ip link add br0 type bridge	// Creating bridge named br0
sudo ip link set eth0 master br0	// Adding the interface to the bridge
sudo ip link set eth1 master br0
```

![image](https://github.com/GhassenHafsiaINSAT/HackerRank-The_Linux_Shell/assets/110825502/0aa4a074-96df-48eb-8431-c301bf1c297a)


## Network Packets
### What is a Packet?

- Data sent over computers is segmented into packets (small segments of a larger message).
  
- These packets are combined by the device that receives them.
- **Datagram**: An alternative term for "packet".

### Why Use Packets?
- Allows multiple connections and multiple exchanges of data at the same time.

### What is a Packet Header?

- A packet header contains information about the packet, such as origin and destination IP addresses.
  
- A packet consists of two portions: the Header and the Payload.
- The payload carries a small piece of the data.

### Packet Sniffing
- The practice of capturing and analyzing packets of data as they travel over a computer network.

### Networking Protocol
- A protocol is a standardized way of formatting data so that any computer can interpret the data.
- Most packets traversing the internet will include a Transmission Control Protocol (TCP) header and an Internet Protocol (IP) header.

### Network Traffic
- Network traffic refers to the packets passing through a network.
- It indicates the amount of data moving across a computer network at any given time.



## Encapsulation Process
- **Definition**: Adding a header to your data as it moves down the network stack.
  
- **Steps**:
  - **Application Layer**: Data.
  - **Transport Layer**: Data + header (TCP/UDP) = Segment.
  - **Network Layer**: Data + header + IP address = Packet (handled by routers).
  - **Data Link Layer**: Data + header + IP address + MAC address = Frame (handled by switches).

## Application Layer Functions
- **Functions**:
  
  - Determining whether adequate resources exist for communication.
  - Managing communication between applications.
  - Directing data to the correct program.
