# TCP Client/Server 

- Our client/server example is an echo server that performs the following steps: 
    - The client reads a line of text from its standard input and writes the line to the server
    - The server reads the line from its network input and echoes the line back to the client 
    - The client reads the echoes line and prints it on its standard output  

- In this example, we will bind server's well-known port, it should be greater than 1023 (avoid reserved port), greater than 5000 (avoid conflicts with ephermeral ports), less than 49152...

- We will use the wildcard `INADDR_ANY`, it tells the system to acceptd a connection destined for any local interface

- For each client, fork() spawns a child, and the child handles the new client

- A `read` or `write` on a stream socket might input or output fewer bytes than requested because buffer limits might be reached for the socket in the kernel.

## Normal Startup 

- When the server starts, it calls blocks in the call to `socket`, `bind`, `listen` and `accept`. Blocking in the call to `accept` (waiting for the client to send its request).

- When starting the client, it calls `socket`, `connect`, cuasing TCP's three-way handshake to take place. When the three-way handshake completes, `connect` returns in the client and `accept` returns in the server. The connection is established.  

- The client then calls `str_cli`, which will block in the call to `fgets`, waiting for a line to be typed.  

- When `accept` returns in the server, it calls `fork` and the child calls `str_echo`. `fork` then calls `readline`, and blocks waiting for a line to be sent form the client.  

- The server parent, on the other hand, calls `accept` again and blocks waiting for next client connection.

## Normal Termination

- When typing `^D` (=EOF character), `fgets` returns a null pointer so `str_cli` returns to the client, and client terminates by calling exit.  

- When the client is closed by the kernel, it sends a FIN to the server, to which the server responds with an ACK.

- When the server TCP recieves the FIN, the server child is blocked in a call to readline, the readline returns then 0, which causes the `str_echo` to return to the server child main.  

- The server child terminates by calling exit, and sends FIN to the client, and the client sends and ACK. At this point, the connection is completely terminated

## POSIX Signal Handling

- A signal is a notification to a process that an event has occured, often called *software interrupts*.  

- Signals can be sent: 
    - By one process to another process (or to itself)
    - By the kernel to a process

- Whenver a process terminates, the kernel sends `SIGCHLD` to the parent of terminating process. 

- Every signal has a *disposition*, this action is set by calling `sigaction` function, we got three choices then: 
    - Catching the signal with `signal handler` fucntion, singals like `SIGKILL` and `SIGSTOP` cannot be caught.  
    - Ignoring signals by setting its disposition to `SIG_IGN`, but `SIGKILL` and `SIGSTOP` cannot be ignored.  
    - Setting the *default* disposition for the signal by setting its disposition to `SIG_DFL`. 