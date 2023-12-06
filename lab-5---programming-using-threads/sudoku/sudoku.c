#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define SIZE 9

// Sudoku board. Modify this to test your checker!
// 0 == empty cell; 1-9 is the filled in digit.
int board[SIZE][SIZE] = {
    {1,0,0,0,0,0,0,0,0},
    {0,2,0,0,0,0,0,0,0},
    {0,0,3,0,0,0,0,0,0},
    {0,0,0,4,0,0,0,0,0},
    {0,0,0,0,5,0,0,0,0},
    {0,0,0,0,0,6,0,0,0},
    {0,0,0,0,0,0,7,0,0},
    {0,0,0,0,0,0,0,8,0},
    {0,0,0,0,0,0,0,0,9},
};

bool row_check[SIZE];
bool col_check[SIZE];
bool box_check[SIZE];

void printBoard(int board[SIZE][SIZE]) {
    for(int i = 0; i<SIZE; i++) {
        for(int j = 0; j<SIZE; j++) {
            printf("%5d", board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Checks the given row for duplicate numbers, and updates the row_check
// value for that row appropriately. If no number is repeated in that row,
// row_check[row] will be set to true; otherwise, it will be false.
void* checkRow(void* args) {
    int appears[SIZE] = {0};
    int row = *((int *)args);
    row_check[row] = true;
    for (int i = 0; i < SIZE; i++){
        int current = board[row][i];
        if(appears[current - 1] == 1){
            row_check[row]=false;
            break; // break if duplicate found
        }
        appears[current - 1]++;
    }




}

// Checks the given col for duplicate numbers, and updates the col_check
// value for that col appropriately. If no number is repeated in that col,
// col_check[col] will be set to true; otherwise, it will be false.
void* checkCol(void* args) {
    int appears[SIZE]={0};
    int col = *((int *)args);
    col_check[col] = true;
    for (int i = 0; i < SIZE; i++){
        int current = board[i][col];
        if(++appears[current - 1] > 1){
            col_check[col]=false;
            break; // break if duplicate found
        }
    }
}

// Checks the given 3x3 box for duplicate numbers, and updates the box_check
// value for that box appropriately. If no number is repeated in that box,
// box_check[box] will be set to true; otherwise, it will be false.
void* checkBox(void* args) {
    int appears[SIZE]={0};
    int box = *((int *)args);
    box_check[box] = true;
    int startRow = (box / 3) * 3;
    int startCol = (box % 3) * 3;

   for (int i = startRow; i < startRow + 3; i++) {
        for (int j = startCol; j < startCol + 3; j++) {
            int currentNumber = board[i][j];
            if (++appears[currentNumber - 1] > 1) {
                box_check[box] = false;
                return NULL; // Exit the function if a duplicate is found
            }
        }
    }
    return NULL;



}

// Spawn a thread to fill each cell in each result matrix.
// How many threads will you spawn?
int main() { 
    // 1. Print the board.
    printf("Board:\n");
    printBoard(board);
    
    // 2. Create pthread_t objects for our threads.
    
    // 3. Create a thread for each cell of each matrix operation.
    
    // 4. Wait for all threads to finish.
     pthread_t rowThreads[SIZE];
    pthread_t colThreads[SIZE];
    pthread_t boxThreads[SIZE];
    int i = 0;

    for (i = 0; i < SIZE; i++)
    {
        int *a = malloc(sizeof(int));
        int *b = malloc(sizeof(int));
        int *c = malloc(sizeof(int));
        *a = i;
        *b = i;
        *c = i;
        pthread_create(&rowThreads[i], NULL, checkRow, a);
        pthread_create(&colThreads[i], NULL, checkCol, b);
        pthread_create(&boxThreads[i], NULL, checkBox, c);
    }
    for (i = 0; i < SIZE; i++)
    {
        pthread_join(rowThreads[i], NULL);
        pthread_join(colThreads[i], NULL);
        pthread_join(boxThreads[i], NULL);
    }
    // 5. Print the results.
    printf("Results:\n");
    bool all_rows_passed = true;
    printf("Rows:\n");
    for (int i = 0; i < SIZE; i++) {
        if (!row_check[i]) {
            printf("Row %i did not pass\n", i);
            all_rows_passed = false;
        }
    }
    if (all_rows_passed) {
        printf("All rows passed!\n");
    }
    
    bool all_cols_passed = true;
    printf("Cols:\n");
    for (int i = 0; i < SIZE; i++) {
        if (!col_check[i]) {
            printf("Col %i did not pass\n", i);
            all_cols_passed = false;
        }
    }
    if (all_cols_passed) {
        printf("All cols passed!\n");
    }
    
    bool all_boxes_passed = true;
    printf("Boxes:\n");
    for (int i = 0; i < SIZE; i++) {
        if (!box_check[i]) {
            printf("Box %i did not pass\n", i);
            all_boxes_passed = false;
        }
    }
    if (all_boxes_passed) {
        printf("All boxes passed!\n");
    }
    return 0;
}

