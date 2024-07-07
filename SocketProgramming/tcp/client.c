#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#define PORT 12345
#define BUFFER_SIZE 256

int main()
{
  char BUFFER[BUFFER_SIZE]; // for storing messages between client and server.
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if(sockfd == -1)
  {
    perror("Socket");
  }
  struct sockaddr_in client_address;
  memset(&client_address, 0, sizeof(client_address));
  client_address.sin_family = AF_INET;
  client_address.sin_port = htons(PORT);
  client_address.sin_addr.s_addr = INADDR_ANY;

  //accepts the connection from the client
  int conn = connect(sockfd, (struct sockaddr*) &client_address, sizeof(client_address));
  if(conn == -1)
  {
    perror("conn");
  }
  while(1)
    {
      printf("Client: ");
      fgets(BUFFER, BUFFER_SIZE, stdin);
      send(sockfd,BUFFER, BUFFER_SIZE, 0);
      
      int recvcheck = recv(sockfd,BUFFER, BUFFER_SIZE, 0);
      if(recvcheck == -1)
      {
        perror("Recv");
      }
      printf("Server: %s", BUFFER);
    }
  close(sockfd);
  return 0;
}
