#include <iostream>
#include <vector>
#include <stdexcept>

class Matrix {
private:
    int row;
    int column;
    std::vector<std::vector<int>> matrix;

public:
    Matrix(int r, int c)
        : row(r), column(c), matrix(r, std::vector<int>(c)) {}

    Matrix(const Matrix& other)
        : row(other.row), column(other.column), matrix(other.matrix) {}

    Matrix& operator=(const Matrix& other) {
        if (this != &other) {
            row = other.row;
            column = other.column;
            matrix = other.matrix;
        }
        return *this;
    }

    Matrix(Matrix&& other) noexcept
        : row(other.row), column(other.column), matrix(std::move(other.matrix)) {
        other.row = 0;
        other.column = 0;
    }

    Matrix& operator=(Matrix&& other) noexcept {
        if (this != &other) {
            row = other.row;
            column = other.column;
            matrix = std::move(other.matrix);
            other.row = 0;
            other.column = 0;
        }
        return *this;
    }

    void set(int n_row, int n_column, int n_value) {
        if (n_row < row && n_column < column) {
            matrix[n_row][n_column] = n_value;
        } else {
            throw std::out_of_range("Index out of bounds");
        }
    }

    int get(int n_row, int n_column) const {
        if (n_row < row && n_column < column) {
            return matrix[n_row][n_column];
        }
        throw std::out_of_range("Index out of bounds");
    }

    int get_column() const {
        return column;
    }

    int get_row() const {
        return row;
    }

    void print() const {
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < column; ++j) {
                std::cout << matrix[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    Matrix operator+(const Matrix& other) const {
        if (row != other.row || column != other.column) {
            throw std::invalid_argument("Matrices must have the same dimensions for addition");
        }

        Matrix result(row, column);
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < column; ++j) {
                result.matrix[i][j] = matrix[i][j] + other.matrix[i][j];
            }
        }
        return result;
    }

    Matrix operator-(const Matrix& other) const {
        if (row != other.row || column != other.column) {
            throw std::invalid_argument("Matrices must have the same dimensions for subtraction");
        }

        Matrix result(row, column);
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < column; ++j) {
                result.matrix[i][j] = matrix[i][j] - other.matrix[i][j];
            }
        }
        return result;
    }
};

int main() {
    Matrix mat1(2, 2);
    Matrix mat2(2, 2);

    int k = 0;
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            mat1.set(i, j, k++);
            mat2.set(i, j, k++);
        }
    }

    std::cout << "Matrix mat1:" << std::endl;
    mat1.print();
    
    std::cout << "Matrix mat2:" << std::endl;
    mat2.print();

    Matrix mat_sum = mat1 + mat2;
    std::cout << "Matrix mat1 + mat2:" << std::endl;
    mat_sum.print();

    Matrix mat_diff = mat1 - mat2;
    std::cout << "Matrix mat1 - mat2:" << std::endl;
    mat_diff.print();

    return 0;
}

