#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define bucket_size 100
int main()
{
  int stored = 0; // how much input is stored currently
  int output, input, number_of_inputs;
  printf("Enter the output rate and number of inputs: ");
  scanf("%d %d", &output, &number_of_inputs);
  while (number_of_inputs>=0)
    {
       input = (rand() % (20-1)) + 1 ;// random number between 1 and 100
       int remaining_space = bucket_size - stored;
       if(input < (remaining_space))
       {
         stored += input;
         printf("The bucket has %d packets out of %d\n", stored, bucket_size);
         sleep(1);
       }
      else
       {
         int overflowed = input - (remaining_space);
         stored = bucket_size;
         printf("The bucket has %d packets out of %d\n", stored, bucket_size);
       }

      stored -= output;
      if (stored<0)
      {
        stored = 0;
      }
      number_of_inputs--;
    }
  return 0;
}
