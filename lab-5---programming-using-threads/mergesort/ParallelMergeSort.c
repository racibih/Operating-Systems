#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define SIZE 100

int array[SIZE];

void fillArrayWithRandomNumbers(int arr[SIZE]) {
int i;
    for( i =0; i<SIZE; i++) array[i] = rand()%100;
}

void printArray(int arr[SIZE]) {
  int i;
    for(i = 0; i<SIZE; i++) printf("%5d", arr[i]);
    printf("\n");
}

typedef struct StartEndIndexes {
    int start;
    int end;
} StartEndIndexes;

void merge(int a, int b, int c){
  int i = a, j = b + 1, k = 0;
    int temp[c - a + 1];

    while (i <= b && j <= c) {
        if (array[i] <= array[j]) {
            temp[k++] = array[i++];
        } else {
            temp[k++] = array[j++];
        }
    }

    while (i <= b) {
        temp[k++] = array[i++];
    }

    while (j <= c) {
        temp[k++] = array[j++];
    }

    for (i = a; i <= c; i++) {
        array[i] = temp[i - a];
    }


}
// Runs mergesort on the array segment described in the
// argument. Spawns two threads to mergesort each half
// of the array segment, and then merges the results.
void* mergeSort(void* args) {
    StartEndIndexes* sei = (StartEndIndexes*)args;
    int start = sei->start;
    int end = sei->end;

    if (start < end) {
        int mid = start + (end - start) / 2;

        StartEndIndexes sei1 = {start, mid};
        StartEndIndexes sei2 = {mid + 1, end};

        pthread_t thread1, thread2;

        pthread_create(&thread1, NULL, mergeSort, &sei1);
        pthread_create(&thread2, NULL, mergeSort, &sei2);

        pthread_join(thread1, NULL);
        pthread_join(thread2, NULL);

        merge(start, mid, end);
    }

    return NULL;
}

int main() {
    srand(time(0));
    StartEndIndexes sei = {0, SIZE -1};
  
    
    // 1. Fill array with random numbers.
    fillArrayWithRandomNumbers(array);
    
    // 2. Print the array.
    printf("Unsorted array: ");
    printArray(array);
    
    // 3. Create a 2 threads for merge sort.
 pthread_t mainThread;
    pthread_create(&mainThread, NULL, mergeSort, &sei);
    // 4. Wait for mergesort to finish.
      pthread_join(mainThread, NULL);





    // 5. Print the sorted array.
    printf("Sorted array:   ");
    printArray(array);

    return 0;
}
