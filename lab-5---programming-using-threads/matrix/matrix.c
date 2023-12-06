#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define MAX 4
//#define MAX_THREADS 10
//const int MAX =4;

int matA[MAX][MAX]; 
int matB[MAX][MAX]; 

int matSumResult[MAX][MAX];
int matDiffResult[MAX][MAX]; 
int matProductResult[MAX][MAX]; 

   int size;

void fillMatrix(int msize,int matrix[msize][msize]) {
   
    for(int i = 0; i<msize; i++) {
        for(int j = 0; j<msize; j++) {
            matrix[i][j] = rand()%10+1;
        }
    }
}

void printMatrix(int msize, int matrix[msize][msize]) {
    for(int i = 0; i<msize; i++) {
        for(int j = 0; j<msize; j++) {
            printf("%5d", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Fetches the appropriate coordinates from the argument, and sets
// the cell of matSumResult at the coordinates to the sum of the
// values at the coordinates of matA and matB.
void* computeSum(void* args) { // pass in the number of the ith thread
    int* crdn = (int *) args;
    int row = crdn[0], col = crdn[1];
    matSumResult[row][col]=matA[row][col]+matB[row][col];
      
    return NULL;

}

// Fetches the appropriate coordinates from the argument, and sets
// the cell of matSumResult at the coordinates to the difference of the
// values at the coordinates of matA and matB.
void* computeDiff(void* args) { // pass in the number of the ith thread
    int* crdn = (int *) args;
    int row = crdn[0], col = crdn[1];
    matDiffResult[row][col]=matA[row][col]- matB[row][col];
      
    return NULL;
}

// Fetches the appropriate coordinates from the argument, and sets
// the cell of matSumResult at the coordinates to the inner product
// of matA and matB.
void* computeProduct(void* args) { // pass in the number of the ith thread
    int* crdn = (int *) args;
    int row = crdn[0], col = crdn[1];
    //matProductResult[row][col]=0;
    
    for(int k = 0; k<size;k++){
    matProductResult[row][col]= matA[row][col]* matB[row][col];

    }
   // matA[row][col]+matB[row][col];
      
    return NULL;
}

// Spawn a thread to fill each cell in each result matrix.
// How many threads will you spawn?
int main(int argc, char *argv[]) {
    srand(0); 
     // Do Not Remove. Just ignore and continue below.
    // 0. Get the matrix size from the command line and assign it to MAX
   // scanf("%d",&size);
if (argc != 2) {
        printf("Size: %s <matrix_size>\n", argv[0]);
        return 1;
    }
 size = atoi(argv[1]); // Get the matrix size from command line argument
    if (size > MAX) {
        printf("Invalid matrix size!\n");
        return 1;
    }
  //  int (*newMatA)[size][size] =malloc(sizeof *newMatA);
  //  int (*newMatB)[size][size] =malloc(sizeof *newMatB);

    //int newMatB[size][size];

   // int MAX = (int *) malloc(sizeof(int) * size);
    // 1. Fill the matrices (matA and matB) with random values.
   fillMatrix(size,matA);
      fillMatrix(size, matB);

    // 2. Print the initial matrices.
    printf("Matrix A:\n");
    printMatrix(size,matA);
    printf("Matrix B:\n");
    printMatrix(size,matB);
    
    // 3. Create pthread_t objects for our threads.
        pthread_t threads[size*size*size];
        int threadCount = 0;

    // 4. Create a thread for each cell of each matrix operation.
    // 
    // You'll need to pass in the coordinates of the cell you want the thread
    // to compute.
    // 
    // One way to do this is to malloc memory for the thread number i, populate the coordinates
    // into that space, and pass that address to the thread. The thread will use that number to calcuate 
    // its portion of the matrix. The thread will then have to free that space when it's done with what's in that memory.
    int i,j,k;
    for (i = 0; i < size; i++){
          for (j = 0; j < size; j++){
            int* coordinates = malloc(2*sizeof(int));
            coordinates[0]= i;
            coordinates[1]=j;
            pthread_create(&threads[threadCount++],NULL,computeSum,coordinates);
            pthread_create(&threads[threadCount++],NULL,computeDiff,coordinates);
            pthread_create(&threads[threadCount++],NULL,computeProduct,coordinates);

        //wait for all threads to finish and reset
            if(threadCount> size*size*size){
                for (k = 0; k < threadCount; k++){
                  pthread_join(threads[k],NULL);
                }   
                 threadCount=0;

            }
          }
          }
 for ( k = 0; k < threadCount; k++){
        pthread_join(threads[k], NULL);
 }


    // 5. Wait for all threads to finish.
    
    // 6. Print the results.
    printf("Results:\n");
    printf("Sum:\n");
    printMatrix(size,matSumResult);
    printf("Difference:\n");
    printMatrix(size,matDiffResult);
    printf("Product:\n");
    printMatrix(size,matProductResult);
    // free(matA);
   // free(matB);
      return 0;
 
  
}