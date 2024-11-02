CC=gcc
CCFlags=-Wall

TARGETS = client server

all: $(TARGETS)

client:
	$(CC) $(CFLAGS) -o client client.o

server:
	$(CC) $(CFLAGS) -o server server.o

client.o: client.c
	$(CC) $(CCFlags) -c  client.c

server.o: server.c
	$(CC) $(CCFlags) -c  server.c

clean:
	rm -rf $(TARGETS) *.o 
