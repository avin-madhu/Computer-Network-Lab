#include <stdio.h>
int cost_matrix[20][20];
int n; // size of cost matrix
struct routers
{
   int distance[20];
   int adjnode[20];
}node[20];

void readCostMatrix()
{
  printf("\nEnter the cost Matrix: \n\n");

  for(int i = 0;i<n;i++)
    {
      for(int j=0;j<n;j++)
        {
          scanf("%d", &cost_matrix[i][j]);
          cost_matrix[i][i] = 0;
         // setting a large value to indicate that there is no direct connection 
          if(cost_matrix[i][j] < 0)
          {
            cost_matrix[i][j] = 10000;
          }
          node[i].distance[j] = cost_matrix[i][j];
          node[i].adjnode[j] = j;
        }
    }
}

void calc_routing_table()
{
 
  for(int i = 0;i<n;i++)
    {
      for(int j=0;j<n;j++)
        {
          for(int k=0;k<n;k++)
            {
              if (node[i].distance[j] > cost_matrix[i][k] + node[k].distance[j])
              {
                node[i].distance[j] = node[i].distance[k] + node[k].distance[j];
                node[i].adjnode[j] = k;
              }
            }
        }
    }
}

void print_routes()
{
  for(int i = 0;i<n;i++)
    {
      printf("\nRouter - %d\n\n", i+1);
      for(int j=0;j<n;j++)
        {
          printf("node - %d || via - %d || distance = %d\n", j+1, node[i].adjnode[j]+1, node[i].distance[j]);
        }
      printf("\n");
    }
}

int main()
{
  printf("\nEnter the number of nodes: ");
  scanf("%d", &n);
  readCostMatrix();
  calc_routing_table();
  print_routes();
  return 0;
}
