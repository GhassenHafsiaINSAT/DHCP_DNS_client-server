# TCP Client/Server 

- Our **client/server** example is a **DHCP server** that performs the following steps: 
    - The client reads a MAC address from its standard input and writes the line to the server, requesting IP address 
    - The server reads the request from its network input and checks if there is available IP address   
    - The client reads the IP address and prints it on its standard output  

- In this example, we will bind server's well-known port, it should be greater than 1023 (avoid reserved port), greater than 5000 (avoid conflicts with ephermeral ports), less than 49152...

- We will use the wildcard `INADDR_ANY`, it tells the system to acceptd a connection destined for any local interface

- For each client, fork() spawns a child, and the child handles the new client

- A `read` or `write` on a stream socket might input or output fewer bytes than requested because buffer limits might be reached for the socket in the kernel.

## Normal Startup 

- When the server starts, it calls blocks in the call to `socket`, `bind`, `listen` and `accept`. Blocking in the call to `accept` (waiting for the client to send its request).

- When starting the client, it calls `socket`, `connect`, cuasing TCP's three-way handshake to take place. When the three-way handshake completes, `connect` returns in the client and `accept` returns in the server. The connection is established.  

- The client then calls `str_cli`, which will block in the call to `fgets`, waiting for a line to be typed.  

- When `accept` returns in the server, it calls `fork` and the child calls `str_echo` and blocks waiting for a line to be sent form the client.  

- The server parent, on the other hand, calls `accept` again and blocks waiting for next client connection.

## Normal Termination

- When typing `^D` (=EOF character), `fgets` returns a null pointer so `str_cli` returns to the client, and client terminates by calling exit.  

- When the client is closed by the kernel, it sends a FIN to the server, to which the server responds with an ACK.

- When the server TCP recieves the FIN, the server child is blocked in a call to readline, the readline returns then 0, which causes the `str_echo` to return to the server child main.  

- The server child terminates by calling exit, and sends FIN to the client, and the client sends and ACK. At this point, the connection is completely terminated

## DHCP Client 

1. **It checks if the program is run with exactly 3 arguments: The program name, IP address, and a command (CHECKOUT/RELEASE)**

```c
    if (argc != 3)
```

2. **Then we create a socket, using the IPv4 family `AF_INET` and the `SOCK_STREAM` for TCP.**  
```c
  if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
```

3. **Zeroing and setting up server address structure**
```c
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERVER_PORT); 
```

4. **It converts the ip address from string format to binary form because the network stack needs it in that form**
```c
    if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) < 0)
```

5. **The client attempts to establish a connection with the server** 

```c
    if (connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0)
```

6. **Storing MAC address and command**
```c
    char command[10];
    strcpy(command, argv[2]); 
    char mac_address[18];
    strcpy(mac_address, argv[3]);
```

7. **Sending MAC address and command to the server**

```c
    if (write(sockfd, mac_address, sizeof(mac_address)) < 0)
        err_sys("write error");
    if (write(sockfd, command, sizeof(command)) < 0)
        err_sys("write error");
```

8. **If the client sends CHECKOUT, it will waits back for a response (IP address)**
```c
    if (strcmp(command, "CHECKOUT") == 0) {
        char assigned_ip[INET_ADDRSTRLEN];
        if (read(sockfd, assigned_ip, sizeof(assigned_ip)) < 0)
            err_sys("read error");

        printf("Assigned IP: %s\n", assigned_ip);
    }
```

9. **Closing socket and exiting** 
```c
    close(sockfd); 
    exit(0);
}
```


