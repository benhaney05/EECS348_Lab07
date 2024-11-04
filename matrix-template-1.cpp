/*
Ben Haney
EECS 348 Lab 07
Lab Section: Thursday 9am
*/


#include <iostream>
#include <cstdio>
using namespace std;

const int SIZE = 4; // Global variable for matrix size

class Matrix {
private:
  int data[SIZE][SIZE];  // 2D array for matrix data (using int for simplicity)

public:
  // 1. Read values from stdin into a matrix
  void readFromStdin(const string& filename, int start_row) {
    FILE* file = fopen(filename.c_str(), "r");
    int value, curr_row = 0, curr_col = 0;

    while (fscanf(file, "%d", &value) != EOF) {
      if (curr_row >= start_row && curr_row < start_row + SIZE) {
        data[curr_row - start_row][curr_col] = value;
        curr_col++;

        if (curr_col == SIZE) {
          curr_col = 0;
          curr_row++;
        }
      
      } else {
        curr_col++;
        if (curr_col == SIZE) {
          curr_col = 0;
          curr_row++;
        }
      }
    }
    fclose(file);
  }
    

  // 2. Display a matrix
  void display() const{
    for (int i = 0; i < SIZE; i++) {
      for (int j = 0; j < SIZE; j++) {
        cout << data[i][j] << " ";
      }
      cout << endl;
    }
  }

  // 3. Add two matrices (operator overloading for +)
  Matrix operator+(const Matrix& other) const {
    Matrix sum;
    for (int i = 0; i < SIZE; i++) {
      for (int j = 0; j < SIZE; j++) {
        sum.data[i][j] = data[i][j] + other.data[i][j];
      }
    }
    return sum;
  }

  // 4. Multiply two matrices (operator overloading for *)
  Matrix operator*(const Matrix& other) const{
    Matrix product;
    for (int i = 0; i < SIZE; i++) {
      for (int j = 0; j < SIZE; j++) {
        product.data[i][j] = 0;
      }
    }
    for (int i = 0; i < SIZE; i++) {
      for (int j = 0; j < SIZE; j++) {
        for (int k = 0; k < SIZE; k++) {
          product.data[i][j] += data[i][k] * other.data[k][j];
        }
      }
    }
    return product;
  }

  // 5. Compute the sum of matrix diagonal elements
  int sumOfDiagonals() const {
    int sum = 0;
    for (int i = 0; i < SIZE; i++) {
      sum += data[i][i];
      sum += data[i][SIZE - i - 1];
    }
    return sum;
  }

  // 6. Swap matrix rows
  void swapRows(int row1, int row2) {
    for (int i = 0; i < SIZE; i++) {
      swap(data[row1][i], data[row2][i]);
    }
  }
};

int main() {
  // Example usage:
  Matrix mat1;
  cout << "Enter values for Matrix 1:" << endl;
  mat1.readFromStdin("matrix-data.txt", 0);
  cout << "Matrix 1:" << endl;
  mat1.display();

  Matrix mat2;
  cout << "Enter values for Matrix 2:" << endl;
  mat2.readFromStdin("matrix-data.txt", 4);
  cout << "Matrix 2:" << endl;
  mat2.display();


  Matrix sum = mat1 + mat2;
  cout << "Sum of matrices:" << endl;
  sum.display();

  Matrix product = mat1 * mat2;
  cout << "Product of matrices:" << endl;
  product.display();

  cout << "Sum of diagonals of Matrix 1: " << mat1.sumOfDiagonals() << endl;


  mat1.swapRows(0, 2);
  cout << "Matrix 1 after swapping rows:" << endl;
  mat1.display();


  return 0;
}
