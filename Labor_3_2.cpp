
#include <ctime>
#include <cstdlib>
#include <iostream>

class Matrix {
private:
    int **data;
    unsigned int m;
    unsigned int n;

public:
    Matrix(unsigned int rows, unsigned int cols) 
        : m(rows), n(cols) {
        data = new int* [m];
        for (unsigned int i = 0; i < m; ++i) {
            data[i] = new int[n];
        }
    }

    Matrix(Matrix& temp, Matrix& other) {             // other = mat1 
        temp = *this;
        if (this->data != nullptr) {
            delete[] this->data;
        }
        
        this->data = new int* [other.m];
        for (unsigned int i = 0; i < other.m; ++i) {            //создание матрицы для создаваемого объекта
            this->data[i] = new int[other.n];
        }

        for (unsigned int i; i < other.m; ++i) {
            for (unsigned int j; j < other.n; ++j) {
                this->data[i][j] = other.data[i][j];
            }
        }
    }


    ~Matrix() {}

    int* operator[](unsigned int index) {
        return data[index];
    }

    void fillRandom() {
        for (unsigned int i = 0; i < m; ++i) {
            for (unsigned int j = 0; j < n; ++j) {
                data[i][j] = rand() % 10;
            }
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix) {
        for (unsigned int i = 0; i < matrix.m; ++i) {
            for (unsigned int j = 0; j < matrix.n; ++j) {
                os << matrix.data[i][j] << ' ';
            }
            os << '\n';
        }
        return os;
    }

    Matrix& operator+=(const Matrix& other) {
        for (unsigned int i = 0; i < m; ++i) {
            for (unsigned int j = 0; j < n; ++j) {
                data[i][j] += other.data[i][j];
            }
        }
        return *this;
    }

    Matrix& operator+(const Matrix& other) const {
        Matrix result(m, n);
        for (unsigned int i = 0; i < m; ++i) {
            for (unsigned int j = 0; j < n; ++j) {
                result.data[i][j] = data[i][j] + other.data[i][j];
            }
        }
        return result;
    }

    Matrix& operator-=(const Matrix& other) {
        for (unsigned int i = 0; i < m; ++i) {
            for (unsigned int j = 0; j < n; ++j) {
                data[i][j] -= other.data[i][j];
            }
        }
        return *this;
    }

    Matrix& operator-(const Matrix& other) const {
        Matrix result(m, n);
        for (unsigned int i = 0; i < m; ++i) {
            for (unsigned int j = 0; j < n; ++j) {
                result.data[i][j] = data[i][j] - other.data[i][j];
            }
        }
        return result;
    }

    friend Matrix operator* (const Matrix& a, const Matrix& b) {            // matrix a умножить 
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

    bool operator==(const Matrix& other) const {
        return data == other.data;
    }

    bool operator!=(const Matrix& other) const {
        return !(*this == other);                       // *this == other
    }
};

int main() {
    setlocale(LC_ALL, "RUS");   

    Matrix mat1(3, 3);
    Matrix mat2(3, 3);

    mat1.fillRandom();
    mat2.fillRandom();

    std::cout << "Matrix 1:\n" << mat1 << std:: endl;
    std::cout << "Matrix 2:\n" << mat2 << std::endl;

    Matrix sum = mat1 + mat2;
    std::cout << "Сумма матриц:\n" << sum << std::endl;

    Matrix diff = mat1 - mat2;
    std::cout << "Разность матриц:\n" << diff << std::endl;

    Matrix mult = mat1 * mat2;
    std::cout << "Произведение матриц:\n" << mult << std::endl;

    std::cout << "Matrix 1 == Matrix 2: " << (mat1 == mat2) << std::endl;
    std::cout << "Matrix 1 != Matrix 2: " << (mat1 != mat2) << std::endl;

    return 0;
}
