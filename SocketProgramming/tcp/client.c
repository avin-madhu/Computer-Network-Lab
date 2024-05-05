#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 2001
#define BUFFER_SIZE 256

int main()
{
  int sockfd;
  struct sockaddr_in server_address;
  char BUFFER[BUFFER_SIZE];

  sockfd = socket(AF_INET, SOCK_STREAM, 0);

  bzero(&server_address, sizeof(server_address));
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(PORT);
  server_address.sin_addr.s_addr = INADDR_ANY;

  connect(sockfd, (struct sockaddr*)&server_address, sizeof(server_address))!=0;
  

  while(1)
    {
      printf("client: ");
      fgets(BUFFER, BUFFER_SIZE, stdin);
      write(sockfd, BUFFER, BUFFER_SIZE);


      bzero(BUFFER, BUFFER_SIZE);
      read(sockfd, BUFFER, BUFFER_SIZE);
      printf("Server: %s", BUFFER);
        
    }

  close(sockfd);
  return 0;
}
