# Compiler and flags
CC = gcc
CFLAGS = -Wall -Iinclude

# Object files for server and client
OBJ_SERVER = server.o str_echo.o writen.o readline.o
OBJ_CLIENT = client.o str_cli.o readline.o writen.o

# Executables
EXEC_SERVER = server
EXEC_CLIENT = client

# Default target
all: $(EXEC_SERVER) $(EXEC_CLIENT)

# Link the server executable
$(EXEC_SERVER): $(OBJ_SERVER)
	$(CC) -o $(EXEC_SERVER) $(OBJ_SERVER)

# Link the client executable
$(EXEC_CLIENT): $(OBJ_CLIENT)
	$(CC) -o $(EXEC_CLIENT) $(OBJ_CLIENT)

# Compile server.o from server.c
server.o: src/server.c include/common.h include/str_echo.h include/writen.h
	$(CC) $(CFLAGS) -c src/server.c -o server.o

# Compile str_echo.o from str_echo.c
str_echo.o: src/str_echo.c include/common.h include/str_echo.h include/writen.h include/readline.h
	$(CC) $(CFLAGS) -c src/str_echo.c -o str_echo.o

# Compile writen.o from writen.c
writen.o: src/writen.c include/common.h include/writen.h
	$(CC) $(CFLAGS) -c src/writen.c -o writen.o

# Compile client.o from client.c
client.o: src/client.c include/common.h include/str_cli.h include/readline.h include/writen.h
	$(CC) $(CFLAGS) -c src/client.c -o client.o

# Compile str_cli.o from str_cli.c
str_cli.o: src/str_cli.c include/common.h include/str_cli.h include/readline.h include/writen.h
	$(CC) $(CFLAGS) -c src/str_cli.c -o str_cli.o

# Compile readline.o from readline.c
readline.o: src/readline.c include/common.h include/readline.h
	$(CC) $(CFLAGS) -c src/readline.c -o readline.o

# Clean up generated files
clean:
	rm -f $(OBJ_SERVER) $(OBJ_CLIENT) $(EXEC_SERVER) $(EXEC_CLIENT)
