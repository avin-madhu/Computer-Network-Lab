#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#define PORT 12347
#define BUFFER_SIZE 256

int main()
{
  char BUFFER[BUFFER_SIZE];
  int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  if(sockfd == -1)
  {
    perror("Socket");
  }
  struct sockaddr_in server_address, client_address;
  memset(&server_address, 0, sizeof(server_address));
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(PORT);
  server_address.sin_addr.s_addr = INADDR_ANY;

  // bind the socket address and port address
  int bindcheck = bind(sockfd, (struct sockaddr*) &server_address, sizeof(server_address));
  if(bindcheck == -1)
  {
    perror("Bind");
  }
  socklen_t addr_size = sizeof(server_address);
  while(1)
    {
      int recvcheck = recvfrom(sockfd,BUFFER, BUFFER_SIZE, 0, (struct sockaddr*) &client_address, &addr_size);
      if(recvcheck == -1)
      {
        perror("Recv");
      }
      printf("Client: %s", BUFFER);

      printf("Server: ");
      fgets(BUFFER, BUFFER_SIZE, stdin);
      sendto(sockfd,BUFFER, BUFFER_SIZE, 0, (struct sockaddr*) &client_address, sizeof(client_address));
    }
  close(sockfd);
  return 0;
}
