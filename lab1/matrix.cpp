#include "matrix.hpp"
#include <iostream>
#include <stdexcept>
#include <cstring>

// выделение памяти
void Matrix::allocate_memory() {
    data_ = new double*[rows_];
    for (int i = 0; i < rows_; i++) {
        data_[i] = new double[cols_];
    }
}

// освобождение памяти
void Matrix::deallocate_memory() {
    if (data_) {
        for (int i = 0; i < rows_; i++) {
            delete[] data_[i];
        }
        delete[] data_;
        data_ = nullptr;
    }
    rows_ = 0;
    cols_ = 0;
}

// копирование данных
void Matrix::copy_data(const Matrix& other) {
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            data_[i][j] = other.data_[i][j];
        }
    }
}

// Конструктор: единичная матрица n x n
Matrix::Matrix(int n) : rows_(n), cols_(n) {
    if (n <= 0) {
        throw std::invalid_argument("Размер матрицы должен быть положительным");
    }
    
    allocate_memory();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            data_[i][j] = 0.0;
        }
    }
    
    // Заполняем диагональ единицами
    for (int i = 0; i < n; i++) {
        data_[i][i] = 1.0;
    }
}

// Конструктор: матрица m x n с fill_value
Matrix::Matrix(int m, int n, double fill_value) : rows_(m), cols_(n) {
    if (m <= 0 || n <= 0) {
        throw std::invalid_argument("Размеры матрицы должны быть положительными");
    }
    
    allocate_memory();
    
    // Заполняем fill_value
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            data_[i][j] = fill_value;
        }
    }
}

// Конструктор копирования
Matrix::Matrix(const Matrix& other) : rows_(other.rows_), cols_(other.cols_) {
    allocate_memory();
    copy_data(other);
}

// Деструктор
Matrix::~Matrix() {
    deallocate_memory();
}

// Оператор присваивания
Matrix& Matrix::operator=(const Matrix& other) {
    if (this != &other) {
        deallocate_memory();
        rows_ = other.rows_;
        cols_ = other.cols_;
        allocate_memory();
        copy_data(other);
    }
    return *this;
}

// Проверка индексов
void Matrix::check_index(int i, int j) const {
    if (i < 0 || i >= rows_ || j < 0 || j >= cols_) {
        throw std::out_of_range("Индекс выходит за границы матрицы");
    }
}

// Получить значение элемента
double Matrix::get(int i, int j) const {
    check_index(i, j);
    return data_[i][j];
}

// Установить значение элемента
void Matrix::set(int i, int j, double value) {
    check_index(i, j);
    data_[i][j] = value;
}

// Операция -A (умножение на -1)
void Matrix::negate() {
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            data_[i][j] = -data_[i][j];
        }
    }
}

// Операция this += other
void Matrix::add_in_place(Matrix& other) {
    if (rows_ != other.rows_ || cols_ != other.cols_) {
        throw std::invalid_argument("Размеры матриц не совпадают для сложения");
    }
    
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            data_[i][j] += other.data_[i][j];
        }
    }
}

// Операция умножения матриц
Matrix Matrix::multiply(Matrix& other) const {
    if (cols_ != other.rows_) {
        throw std::invalid_argument("Несовместимые размеры для умножения матриц");
    }
    
    Matrix result(rows_, other.cols_, 0.0);
    
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < other.cols_; j++) {
            double sum = 0.0;
            for (int k = 0; k < cols_; k++) {
                sum += data_[i][k] * other.data_[k][j];
            }
            result.data_[i][j] = sum;
        }
    }
    
    return result;
}

// Вывод матрицы
void Matrix::print() const {
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            std::cout << data_[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}