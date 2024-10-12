#include <stdlib.h>
#include <stdio.h>
#define SIZE 5

int** addMatrices(int m1[SIZE][SIZE], int m2[SIZE][SIZE]){

    int** matrix = malloc(SIZE * sizeof(int*)); 
    for (int i = 0; i < SIZE; i++) { 
        matrix[i] = malloc(SIZE * sizeof(int)); 
    } 

    for (int i = 0; i < SIZE; i++){
        for (int k = 0; k < SIZE; k++){
            matrix[i][k] = m1[i][k] + m2[i][k];
        }
    }
    
    return matrix;
}

int** multiplyMatrices(int m1[SIZE][SIZE], int m2[SIZE][SIZE]){
    int** matrix = malloc(SIZE * sizeof(int*)); 
    for (int i = 0; i < SIZE; i++) { 
        matrix[i] = malloc(SIZE * sizeof(int)); 
    } 

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            matrix[i][j] = 0;

            for (int k = 0; k < SIZE; k++) {
                matrix[i][j] += m1[i][j] * m2[k][j];
            }
        }
    }

    return matrix;
}

int** transposeMatrix(int m[SIZE][SIZE]){
    int** matrix = malloc(SIZE * sizeof(int*)); 
    for (int i = 0; i < SIZE; i++) { 
        matrix[i] = malloc(SIZE * sizeof(int)); 
    } 

    for (int i = 0; i < SIZE; i++){
        for (int k = 0; k < SIZE; k++){
            matrix[i][k] = m[i][k];
        }
    }

    int temp;

    for (int i = 0; i < SIZE; i++){
        for (int j = i; j < SIZE; j++){
            temp = matrix[i][j];
            matrix[i][j] = matrix[j][i];
            matrix[j][i] = temp;
        }
    }

    return matrix;
}

void printMatrix(int** matrix){
    printf("\n");
    for (int i = 0; i < SIZE; i++){
        for (int k = 0; k < SIZE; k++){
            printf("%d ", matrix[i][k]);
        }
        printf("\n");
    }
    printf("\n");
}

int main(){
    int m1[SIZE][SIZE] = {
    {1, 2, 3, 4, 5},
    {6, 7, 8, 9, 10},
    {11, 12, 13, 14, 15},
    {16, 17, 18, 19, 20},
    {21, 22, 23, 24, 25}
    };

    int m2[SIZE][SIZE] = {
    {25, 24, 23, 22, 21},
    {20, 19, 18, 17, 16},
    {15, 14, 13, 12, 11},
    {10, 9, 8, 7, 6},
    {5, 4, 3, 2, 1}
    };

    int m1rows = sizeof(m1) / sizeof(m1[0]);
    int m1columns = sizeof(m1[0]) / sizeof(m1[0][0]);

    int m2rows = sizeof(m2) / sizeof(m2[0]);
    int m2columns = sizeof(m2[0]) / sizeof(m2[0][0]);

    if (m1rows == m2rows && m1columns == m2columns){
        int **m3 = addMatrices(m1, m2);
        printMatrix(m3);
    }

    if (m1columns == m2rows){
        int **m4 = multiplyMatrices(m1, m2);
        printMatrix(m4);
    }

    int **m5 = transposeMatrix(m1);

    printMatrix(m5);

    return 0;
}