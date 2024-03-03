#include <iostream> 
#include <cstdlib> 
#include <ctime> 
  
const int matrixSize = 10; 
  
void generateMatrix(int matrix[matrixSize][matrixSize]) { 
    for (int i = 0; i < matrixSize; ++i) { 
        for (int j = 0; j < matrixSize; ++j) { 
            matrix[i][j] = rand() % 99 + 1;  // Losowanie liczby z zakresu 1-99 
        } 
    } 
} 
  
int calculateDiagonalSum(int matrix[matrixSize][matrixSize]) { 
    int sum = 0; 
    for (int i = 0; i < matrixSize; ++i) { 
        sum += matrix[i][i]; 
    } 
    return sum; 
} 
  
int main() { 
    srand(time(0));   
  
    int matrix[matrixSize][matrixSize]; 
    int iterations = 0; 
    int diagonalSum = 0; 
  
    do { 
        generateMatrix(matrix); 
        diagonalSum = calculateDiagonalSum(matrix); 
        ++iterations; 
    } while (diagonalSum >250); 
  
     
    std::cout << "Wygenerowana tablica:" << std::endl; 
    for (int i = 0; i < matrixSize; ++i) { 
        for (int j = 0; j < matrixSize; ++j) { 
            std::cout << matrix[i][j] << "\t"; 
        } 
        std::cout << std::endl; 
    } 
  
    std::cout << "\nSuma wyrazów na przekątnej: " << diagonalSum << std::endl; 
    std::cout << "Liczba losowań: " << iterations << std::endl; 
  
    return 0; 

}