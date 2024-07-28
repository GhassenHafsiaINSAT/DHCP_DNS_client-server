## What is socket?
- A socket is aa way to speak to other programs, using standard Unix file descriptors.
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
