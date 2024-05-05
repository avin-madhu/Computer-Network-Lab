#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

#define PORT 2003
#define BUFFER_SIZE 1024

int main()
{
  char BUFFER[BUFFER_SIZE];
  int sockfd = socket(AF_INET, SOCK_DGRAM, 0);

  struct sockaddr_in server_address;
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(PORT);
  server_address.sin_addr.s_addr = INADDR_ANY;

  socklen_t server_addr = sizeof(server_address);

  while(1)
    {
      printf("Client: ");
      fgets(BUFFER, BUFFER_SIZE, stdin);
      sendto(sockfd, BUFFER, BUFFER_SIZE, 0, (struct sockaddr*)&server_address, sizeof(server_address));

      int rec = recvfrom(sockfd, BUFFER, BUFFER_SIZE, 0, NULL, NULL);
      if (rec<0)
      {
        printf("error in recieving data");
      }
      printf("Server: %s", BUFFER);
    }

  return 0;
}
