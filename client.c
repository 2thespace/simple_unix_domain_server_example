#include <stdio.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

void connect_client(char ** hostname) {
  char * host;
  host = *hostname;
  struct socket;

  // create filedescripot of socket
  // arg1 - socket family (man socket(2))
  // arg2 - socket type (man socket(2)
  int socketfd = socket(AF_UNIX, SOCK_STREAM , 0);
  if(socketfd < 0) {
    printf("Error of creating socket fd errNumber = %d", errno);
    return;
  }


  // setup server`s address
  struct sockaddr_un  server_addr;
  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sun_family = AF_UNIX;
  strncpy(server_addr.sun_path, *hostname, strlen(*hostname));

  // try connect to server
  // connect to host
  // man socket(7)
  if(connect(socketfd, (struct sockaddr*)&server_addr, sizeof(server_addr) ) < 0) {
      printf("Error of connection to host errNumber = %d", errno);
      close(socketfd);
      return;
  }

  // send message
  while(1) {
    char message[256];
    scanf("%s", message);
    send(socketfd, message, sizeof(message), 0);
    if(strcmp(message, "DONE") == 0) {
        break;
    }
  }
}

int main(int argc, char ** argv) {
  char * hostname = "/tmp/unix_socket";
  connect_client(&hostname);
  return 0;
}
