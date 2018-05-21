#include <stdio.h>
#include <string.h>
#include <mpi/mpi.h>
#include <time.h>
#include <stdlib.h>

void merge(int c[], int nc, int a[], int na, int b[], int nb);

void print(int x[], int nx);

void sort(int x[], int nx);

int main(void)

{
  
int *a = NULL, *b = NULL, *c = NULL;
  
int comm_sz;
  
int my_rank;
  
time_t t;
  
int i, na, nb, nc;  

MPI_Init(NULL, NULL);
  
MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

srand((unsigned) time(&t));
  
na = 70;
  
nb = 80;
  
nc = na + nb;

if(my_rank == 1){   

a = (int *) malloc(na * sizeof(int));
    
for (i = 0; i < na; i++)
        
a[i] = rand()%100;
        
sort(a, na);
        
print(a, na);
        
MPI_Send(a, na, MPI_INT, 0, 0, MPI_COMM_WORLD);  

}  

if(my_rank == 2){
    
b = (int *) malloc(nb * sizeof(int));
    
for (i = 0; i < nb; i++)
        
b[i] = rand()%100;
    	
sort(b, nb);
    	
print(b, nb);
    	
MPI_Send(b, nb, MPI_INT, 0, 0, MPI_COMM_WORLD);

}  

if(my_rank == 0){

a = (int *) malloc(na * sizeof(int));
    
b = (int *) malloc(nb * sizeof(int));
    
c = (int *) malloc(nc * sizeof(int));

MPI_Recv(a, na, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    MPI_Recv(b, nb, MPI_INT, 2, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    merge(c, nc, a, na, b, nb);
    
print(c, nc); 

}    

MPI_Finalize();
   
return 0;

}

int findIndexOfSmallest(int a[], int from, int to)
{
    
int indexOfSmallest = from;
    
for(int i = from; i < to; i++)
      
if(a[i] < a[indexOfSmallest])
        
indexOfSmallest = i;
    
return indexOfSmallest;

}

void sort(int x[], int nx)
{
    
for(int i = 0; i < nx ; i++){
      
int indexOfSmallest = findIndexOfSmallest(x, i, nx);
      
int t = x[i];
      
x[i] = x[indexOfSmallest];
      
x[indexOfSmallest] = t;
    
}

}

void merge(int c[], int nc, int a[], int na, int b[], int nb){
  
int aIndex = 0, bIndex = 0, cIndex = 0;
    
while(aIndex < na && bIndex < nb)
      
if(a[aIndex] < b[bIndex])
        
c[cIndex++] = a[aIndex++];
      
else
        
c[cIndex++] = b[bIndex++];

    
while(aIndex < na)
      
c[cIndex++] = a[aIndex++];

    
while(bIndex < nb)
      
c[cIndex++] = b[bIndex++];

}

void print(int x[], int nx){
  
for(int i = 0; i < nx; i++)
   
printf("%d, ", x[i]);
  
printf("\n************************\n");

}