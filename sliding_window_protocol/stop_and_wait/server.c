#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>

#define port 12348
#define buff_size 256

int main()
{
  int frame[2];
  frame[0] = 1;
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd == -1)
  {
    perror("socket");
    exit(1);
  }
  struct sockaddr_in server_address, client_address;

  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(port);
  server_address.sin_addr.s_addr = INADDR_ANY;

  // forcefully setting the port number
  int opt = 1;
  setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

  int bindcheck = bind(sockfd, (struct sockaddr*) &server_address, sizeof(server_address));
  if (bindcheck == -1)
  {
    perror("Bind");
    exit(1);
  }

  listen(sockfd, 5);

  socklen_t client_address_size = sizeof(client_address);
  int connfd = accept(sockfd, (struct sockaddr*) &client_address, &client_address_size);

  if (connfd == -1)
  {
    perror("Connection");
    exit(1);
  }

  while(frame[1]>0)
    {
      int recvcheck = recv(connfd,frame, sizeof(frame), 0);
      printf("\nFrame[%d] recieved\n", frame[0]);
      sleep(1);
      if (recvcheck == -1)
      {
        perror("recv");
        exit(1);
      }

      printf("\nAcknowledgment for Frame[%d] sent\n", frame[0]);
      frame[1] -= 1;
      send(connfd, frame, sizeof(frame), 0);
    }

  close(sockfd);
  close(connfd);

  return 0;
}
