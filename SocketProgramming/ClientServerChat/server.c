#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 2001
#define BUFFER_SIZE 256

void error(const char *msg)
{
  perror(msg);
  exit(1);
}

int main()
{

  struct sockaddr_in server_address, client_address;
  char BUFFER[BUFFER_SIZE];
  // make a socket
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);

  // initialize the server address
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(PORT);
  server_address.sin_addr.s_addr = INADDR_ANY;

  // bind 
  int binres = bind(sockfd, (struct sockaddr*) 
  &server_address, sizeof(server_address));

  // listen 
  listen(sockfd, 5)!=0
    
  socklen_t addr_size = sizeof(client_address);
  int connfd = accept(sockfd, (struct sockaddr*) &client_address, &addr_size);

  while(1)
    {
      // recieve message from the client
      bzero(BUFFER, BUFFER_SIZE);
      read(connfd, BUFFER, sizeof(BUFFER));
      printf("Client: %s", BUFFER);

      // send message to the client 
      printf("Server: ");
      fgets(BUFFER, sizeof(BUFFER), stdin);
      write(connfd, BUFFER, strlen(BUFFER));

      if(strncmp(BUFFER, "exit", 4)==0)
      {
        break;
      }
    }

  close(sockfd);

  return 0;
}
