#include <stdio.h>
int main()
{
  int n; // number of routers
  int source; //source router
  int cost[20][20]; // cost matrix
  int flag[20];// indicate wether we visited a node
  int distance[20];// distance of node from source
  int previous[20];// previous node of a node
  
  printf("\nEnter the number of routers: ");
  scanf("%d", &n);

  printf("\nEnter the cost matrix: \n\n");
  for(int i=0;i<n;i++)
    {
      for(int j=0;j<n;j++)
        {
          scanf("%d", &cost[i][j]);
          // setting a large value for negative cost (indicate there is no direct connection or path)
          if(cost[i][j] < 0)
          {
            cost[i][j] = 10000;
          }
        }
    }

  printf("Enter the source router: ");
  scanf("%d", &source);

  for(int i=0;i<n;i++)
    {
      flag[i] = 0;
      previous[i] = source;
      distance[i] = cost[source][i];
    }

  flag[source] = 1; // visit source router

  int min_distance;
  int min_node;
  for(int i=0; i<n-1; i++)
    {
      min_distance = 10000;
      for(int j=0;j<n;j++)
        {
          if(!flag[j] && distance[j]<min_distance)
          {
            min_node = j;
            min_distance = distance[j];
          }
        }

      flag[min_node] = 1; // visit the node with minimum distance from current node.

      for(int j=0;j<n;j++)
        {
          if(!flag[j] && (min_distance + cost[min_node][j]<distance[j]))
          {
            distance[j] = min_distance + cost[min_node][j];
            previous[j] = min_node;
          }
        }
    }
  int temp;
  // Printing the result
  for(int i=0 ; i<n ; i++)
    {
      printf("\n\n%d --> %d\nPath Taken: %d", source, i, i);
      temp = i;
      while(temp != source)
        {
          printf(" <-- %d", previous[temp]);
          temp = previous[temp];
        }
      printf("\n Shortest Path Cost: %d", distance[i]);
    }
  return 0;
}
