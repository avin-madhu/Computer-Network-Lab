#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>
#define PORT 12346
#define BUFFER_SIZE 256

int main()
{
  char buffer[BUFFER_SIZE];
  struct sockaddr_in client_address;

  time_t t; // variable to hold current time
  time(&t); // put the current time in t
  char *hello = ctime(&t); // convert into human-readable way
  char *current_time = ctime(&t);
  printf("The current time is: %s\n", current_time);
  int sockfd = socket(AF_INET, SOCK_DGRAM, 0);

  memset(&client_address, 0, sizeof(client_address));
  client_address.sin_family = AF_INET;
  client_address.sin_addr.s_addr = INADDR_ANY;
  client_address.sin_port = htons(PORT);


  printf("\nTime at Client: %s\n", buffer);
  socklen_t address_length = sizeof(address_length);
  
  sendto(sockfd, hello, strlen(hello)+1, MSG_CONFIRM, (struct sockaddr*) &client_address, address_length);
  printf("\nThe time of server sent to server\n");
  int n = recvfrom(sockfd, buffer, sizeof(buffer), MSG_WAITALL, (struct sockaddr*) &client_address, &address_length);
  buffer[n] = '\0';
  printf("\nTime at Server: %s\n", buffer);
  close(sockfd);
  return 0;
}
