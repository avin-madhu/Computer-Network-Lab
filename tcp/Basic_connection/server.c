#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 12345
#define BUFFER_SIZE 256

int main()
{
  char BUFFER[BUFFER_SIZE];
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
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

  // listen for the connection from the client
  listen(sockfd, 5);

  socklen_t addr_size = sizeof(client_address);

  //accepts the connection from the client
  int newsockfd = accept(sockfd, (struct sockaddr*) &client_address, &addr_size);

  while(1)
    {
      int recvcheck = recv(newsockfd,BUFFER, BUFFER_SIZE, 0);
      if(recvcheck == -1)
      {
        perror("Recv");
      }
      printf("Client: %s", BUFFER);

      printf("Server: ");
      fgets(BUFFER, BUFFER_SIZE, stdin);
      send(newsockfd,BUFFER, BUFFER_SIZE, 0);
    }
  close(sockfd);
  close(newsockfd);
  return 0;
}


/*
----------------
| Extra Notes  |
----------------

 # Perror() --> basically checks for any error and prints it out on to the 
   terminal with the given parameter string as prefix.

*/
