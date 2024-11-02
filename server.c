#include <stdio.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

void listen_server(char **hostname) {
    char * host;
    host = *hostname;
    struct socket;

    // create filedescripot of socket
    // arg1 - socket family (man socket(2))
    // arg2 - socket type (man socket(2)
    int socketFd = socket(AF_UNIX, SOCK_STREAM , 0);
    if(socketFd < 0) {
      printf("Error of creating socket fd %d", errno);
      return;
    }

    // setup server`s address
    struct sockaddr_un  server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sun_family = AF_UNIX;
    strncpy(server_addr.sun_path, *hostname, strlen(*hostname));

    // bind socket
    // man bind (2)
    if(bind(socketFd, (const struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) {
        printf("Error of bind host errNumber = %d", errno);
        close(socketFd);
        return;
    }

    // listen port
    // man listen(2)
    if (listen(socketFd, 8) < 0) {
        printf("Error of bind host errNumber = %d", errno);
    }

    printf("Server is creating");

    // accept mesage from client
    // man accept(2)
    struct sockaddr_un client_addr;
    int data_socket;
    data_socket = accept(socketFd, NULL, NULL);
    ssize_t             r, w;
    char buffer[256];

    while(1) {
        if(read(data_socket, buffer, 256) < 0) {
            printf("error in read");
        }
        if(!strncmp(buffer, "DONE", sizeof(buffer))) {
            break;
        }
        printf("\n-------\n%s\n", buffer);
    }
    close(socketFd);
    unlink(*hostname);

}

int main(int argc, char ** argv) {
    char * hostname = "/tmp/unix_socket";
  listen_server(&hostname);
  return 0;
}

