#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>

#define port 12340
#define buff_size 256

int main()
{
  char buff[buff_size];
  char filename[20];
  int newsockfd;
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  struct sockaddr_in server_address, client_address;

  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(port);
  server_address.sin_addr.s_addr = INADDR_ANY;

  if(bind(sockfd, (struct sockaddr*) &server_address, sizeof(server_address))==-1)
  {
    perror("bind");
  }
  if(listen(sockfd, 5)==-1)
  {
    perror("Listen");
  }
  socklen_t addr_size = sizeof(server_address);
  newsockfd = accept(sockfd, (struct sockaddr*) &server_address,&addr_size);

  printf("Enter the file name: ");
  scanf("%s", filename);
  send(newsockfd, filename, sizeof(filename), 0);
  
  while(1)
  {
    int recvcheck = recv(newsockfd, buff, sizeof(buff),0);
    if (recvcheck == -1)
    {
      perror("recv");
    }
    // the client closes the connection
    if (recvcheck == 0)
    {
      break;
    }
    printf("%s\n", buff);
  }
  close(sockfd);
  close(newsockfd);
}
