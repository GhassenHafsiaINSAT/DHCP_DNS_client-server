# TCP Client/Server 

- Our client/server example is an echo server that performs the following steps: 
    - The client reads a line of text from its standard input and writes the line to the server
    - The server reads the line from its network input and echoes the line back to the client 
    - The client reads the echoes line and prints it on its standard output  

- In this example, we will bind server's well-known port, it should be greater than 1023 (avoid reserved port), greater than 5000 (avoid conflicts with ephermeral ports), less than 49152...
- We will use the wildcard `INADDR_ANY`, it tells the system to acceptd a connection destined for any local interface
- The server blocks in the call to accept, waiting for a client connection to complete
- For each client, fork() spawns a child, and the child handles the new client

- A `read` or `write` on a stream socket might
input or output fewer bytes than requested because buffer limits might be reached for the socket in the kernel.