#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 12347
#define BUFFER_SIZE 256

void isPrime(int num)
{
  if(num == 1)
  {
    printf("Not Prime");
    return;
  }
  for(int i=2;i<num;i++)
    {
      if(num%i==0)
      {
        printf("Not Prime");
        return;
      }
    }
  printf("Prime");
  return;
}

int main()
{
  char BUFFER[BUFFER_SIZE];
  int num;
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
  
  recvfrom(sockfd, &num, sizeof(num), 0, NULL, NULL);
  printf("Number recived from the server: %d\n\n", num);
  printf("The number is ");
  isPrime(num);
  
  close(sockfd);
  return 0;
}
