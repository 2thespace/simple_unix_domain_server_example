CC=gcc
CCFlags=-Wall -g

TARGETS = client server  

all: $(TARGETS)

client.o: client.c
	$(CC) $(CCFlags) -c client.c 

server.o: server.c
	$(CC) $(CCFlags) -c server.c 

client: client.o
	$(CC) $(CCFlags) -o client client.o

server: server.o
	$(CC) $(CCFlags) -o server server.o

clean:
	rm -rf $(TARGETS) *.o 
