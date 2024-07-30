CC=gcc
CFLAGS=-c -Wall


all: client

client: tcpclient.o
	$(CC)  tcpclient.o -o client


tcpclient.o: tcpclient.c
	$(CC) $(CFLAGS) tcpclient.c



clean: 
	rm -r	client tcpclient.o
