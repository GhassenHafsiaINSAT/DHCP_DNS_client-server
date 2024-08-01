## create a client

1. **Create socket**

```c 
int sockfd = socket(AF_INET, SOCK_STREAM, 0); 
```

- Creating a socket for communication, `AF_INET` specifies IPv4, `SOCK_STREAM` specifies TCP.  

2. **Initialize the server address structure** 
- the server address structure is used to define the address propreties of a server socket.  
    
    1. zeroing out the structure 
    
    ```c
    memset(&servaddr, 0, sizeof(servaddr)); 
    ```

    2. Setting the address family

    ```c
    servaddr.sin_family = AF_INET; 
    ```

    3. Setting the port number 

    ```c
    servaddr.sin_port = htons(SERVER_PORT); 
    ```

    4. Setting the IP address

    ```c
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
    ```
    - `INADDR_ANY` is a special address that binds the socket to all available network interfaces available on the machine.  

3. **Connect to the server**
- Establish a connection to the server 

```c
connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
```

4. Send data to server 
```c
char sendline[] = "Hello world!"; 
```

5. Read response from server 
```c
char recvline[MAXLINE]; 
int n; 
while((n=read(sockfd, recvline, MAXLINE-1)>0)){
    recvline[n] = 0; 
    printf("Recieved:  %s", recvline); 
}
```

6. **Close the socket**

```c
close(sockfd); 
```

## create a server

- he server creates two distinct types of sockets to handle incoming connections effectively.
    - The listening socket is used to listen for incoming connection requests from clients.
    - The connected socket is created when the server accepts a new connection from a client. This socket is dedicated to communication with that specific client.

1. **Create socket**

```c 
int listenfd = socket(AF_INET, SOCK_STREAM, 0); 
```

- Creating a socket for communication, `AF_INET` specifies IPv4, `SOCK_STREAM` specifies TCP.  

2. **Initialize the server address structure** 
- the server address structure is used to define the address propreties of a server socket.  
    
    1. zeroing out the structure 
    
    ```c
    memset(&servaddr, 0, sizeof(servaddr)); 
    ```

    2. Setting the address family

    ```c
    servaddr.sin_family = AF_INET; 
    ```

    3. Setting the port number 

    ```c
    servaddr.sin_port = htons(SERVER_PORT); 
    ```

    4. Setting the IP address

    ```c
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
    ```
    - `INADDR_ANY` is a special address that binds the socket to all available network interfaces available on the machine.  

3. **bind the socket**
-  bind the socket to the specified IP address and port number.   

```c
bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
```

4. **Listen for incoming connections**
```c
listen(listenfd,10); 

- `10`: This is the backlog parameter, which specifies the maximum number of pending connections that can be queued up before the server starts refusing new connection requests
```

5. **Accept a connection**
```c
int connfd; 
struct sockaddr_in clientaddr; 
socklen_t clientlen = sizeof(clientaddr);  
connfd = accept(listenfd, (struct sockadd *) &clientaddr, sizeof(clientaddr)); 
```

6. **Read data from client**
```c
char recvline[MAXLINE]; 
int n; 
while ((n = read(connfd, recvline, MAXLINE-1)) > 0)
    printf ("Response : %s", recvline); 

if (n<0) printf("error while reading"); 
```

7. **Send response to client**

```c
char sendline[] = "HTTP/1.0 200 OK\r\n\r\nHELLO"; 
write (connfd, sendline, strlen(sendline)); 
```

8. **close the socket**

```c
close(connfd); 
```

