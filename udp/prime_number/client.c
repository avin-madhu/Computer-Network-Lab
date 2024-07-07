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
  int num;
  int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  if(sockfd == -1)
  {
    perror("Socket");
  }
  struct sockaddr_in client_address;
  memset(&client_address, 0, sizeof(client_address));
  client_address.sin_family = AF_INET;
  client_address.sin_port = htons(PORT);
  client_address.sin_addr.s_addr = INADDR_ANY;

  printf("Enter the number: ");
  scanf("%d", &num);

  sendto(sockfd, &num, sizeof(num), 0, (struct sockaddr*) &client_address, sizeof(client_address));
  
  close(sockfd);
  return 0;
}
