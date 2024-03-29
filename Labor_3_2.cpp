
#include <iostream>
#include <cstdlib>
#include <math.h>

class Matrix {
private:
    int** data;
    unsigned int m;
    unsigned int n;

public:

    Matrix(unsigned int rows, unsigned int cols) : m(rows), n(cols) {
        data = new int* [m];
        for (unsigned int i = 0; i < m; ++i) {
            data[i] = new int[n];
        }
    }


    ~Matrix() {
        for (unsigned int i = 0; i < m; ++i) {
            delete[] data[i];
        }
        delete[] data;
    }

    // Перегрузка оператора [] для доступа и изменения элемента
    int* operator[](unsigned int row) {
        return data[row];
    }

    // Метод для заполнения случайными значениями от 0 до 9
    void randomFill() {
        for (unsigned int i = 0; i < m; ++i) {
            for (unsigned int j = 0; j < n; ++j) {
                data[i][j] = rand() % 10;
            }
        }
    }

    // Перегрузка оператора вывода в поток (<<)
    friend std::ostream& operator<<(std::ostream& os, Matrix& matrix) {
        for (unsigned int i = 0; i < matrix.m; ++i) {
            for (unsigned int j = 0; j < matrix.n; ++j) {
                os << matrix.data[i][j] << " ";
            }
            os << std::endl;
        }
        return os;
    }

    // Перегрузка оператора сложения (+)
    friend Matrix  operator+ (const Matrix& a, const Matrix& b) {
        Matrix result(a.m, a.n);
        for (unsigned int i = 0; i < a.m; ++i) {
            for (unsigned int j = 0; j < a.n; ++j) {
                result.data[i][j] = a.data[i][j] + b.data[i][j];
            }
        }
        return result;
    }

    // Перегрузка оператора вычитания (-)
    friend Matrix operator- (const Matrix& a, const Matrix& b) {
        Matrix result(a.m, a.n);
        for (unsigned int i = 0; i < a.m; ++i) {
            for (unsigned int j = 0; j < a.n; ++j) {
                result.data[i][j] = a.data[i][j] - b.data[i][j];
            }
        }
        return result;
    }

    // Перегрузка оператора умножения (*)
    friend Matrix operator* (const Matrix& a, const Matrix& b) {
        Matrix result(a.m, b.n);
        for (unsigned int i = 0; i < a.m; ++i) {
            for (unsigned int j = 0; j < b.n; ++j) {
                result.data[i][j] = 0;
                for (unsigned int k = 0; k < a.n; ++k) {
                    result.data[i][j] += a.data[i][k] * b.data[k][j];
                }
            }
        }
        return result;
    }

};

int main() {
    srand(static_cast<unsigned int>(time(0))); // Для генерации случайных чисел по времени 

    Matrix mat1(3, 3); 
    mat1.randomFill(); 
    std::cout << "First matrix:" << std::endl;
    std::cout << mat1; 

    Matrix mat2(3, 3); 
    mat2.randomFill(); 
    std::cout << "Second matrix:" << std::endl;
    std::cout << mat2; 

    Matrix sum = mat1 + mat2; 
    std::cout << "Sum of matrices:" << std::endl;
    std::cout << sum; 

    Matrix diff = mat1 - mat2;
    std::cout << "Matrix difference:" << std::endl;
    std::cout << diff; 

    Matrix mult = mat1 * mat2; 
    std::cout << "Product of matrices:" << std::endl;
    std::cout << mult; 

    return 0;
}﻿
