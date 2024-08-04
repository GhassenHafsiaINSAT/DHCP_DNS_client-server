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

## Domain Name server (DNS)
- When accessing a server, it is normally identified by a  domain name instead of IP address, more readable.  
  - DNS Translates domain names (e.g., www.example.com) into IP addresses (e.g., 192.0.2.1) to facilitate communication over the internet.

### DNS Query
- A DNS query is a demand for information sent from a user's computer to a DNS server, asking for the IP address associated with a domain name.

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
