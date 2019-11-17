//
// Created by thoth on 8/13/19.
//

#ifndef MATRIX_OPERATIONS_MATRIX_H
#define MATRIX_OPERATIONS_MATRIX_H

#define MAX(a, b)  ((a) > (b) ? (a) : (b))

#include <iostream>
#include <string>
#include <limits>

template<class T>
class Matrix {

private:

    T **matrix;
    T min_value = 0, max_value = 0;
    int cols, rows;

private:
    void update_min(T value);
    void update_max(T value);
    void value_setter(T *&container, T value);
    void row_col_greater_than_zero_checker();
    void matrix_initialization();
    bool in_range(int &constrain, int &value);
    void range_constrains(int &row, int &col);
    void constrain_square_matrix();
    std::string array_to_string(int row);
    bool identity_conditions(int &i, int &j);
    bool v_equal(T *&local, T *&external);
    void constrains_matrix_multiplication(int n_cols, int n_rows);
    void copy(const Matrix &obj) const;
    T **sub_matrix(T **matrix_, int n, int i);
    T recursive_determinant(T **matrix_, int n); // Calculate determinant
    T numerical_determinant(); // Calculate determinant
    T determinant_2x2(T **&matrix_); // Calculate determinant
    Matrix<T>  *matrix_multiplication(Matrix<T> B);

public:
    Matrix(const Matrix &old_obj);
    explicit Matrix(int cols); // Constructor, vector like [1xn]
    Matrix(int rows, int cols); // Constructor [nxm]
    ~Matrix(); // Destructor

    // Setters and getters
    void set(int i, int j, T value); // Set value to (i,j) <row,column>
    T get(int i, int j) ; // Get value from (i,j) <row,column>
    T **values() const;
    void fill(T value); // Fill all the matrix with a value
    void sequential_fill(); // Fill all the matrix with sequential values
    void fill_identity(); // Fill all the matrix with sequential values

    // Dimensions
    int *size() const; // Returns [n, m] as a int vector
    int length() const; // Return    max dimension, usefull for vectors

    // Values
    T max() const; // Maximum value of the matrix
    T min() const; // Minimum value of the matrix
    T det(); // Calculate determinant
    T norm() const; // Get  norm of vector

    // Utilitarian functions
    void display() const; // Display matrix to console
    void save_to_file(const std::string& filename); // Save
    Matrix<T> *clone(); // Clone the matrix

    // Booleans
    bool equals(Matrix<T> *matrix_); // Matrix has same values as another
    bool is_diag() const; // Matrix is diagonal
    bool is_identity(); // Check if matrix is identity
    bool is_symmetric() const; // Check if matrix is symmetric
    bool is_square() const; // Check if matrix is square nxn
    bool is_vector() const; // Check if matrix is vector
    bool operator==(const Matrix<T> &matrix_); // Equal operator
    bool operator!=(const Matrix<T> &matrix_); // Not equal operator

    // Mathematical operation
    Matrix<T> *transpose(); // Transpose the matrix and return a new matrix
    Matrix<T> &operator*=(const Matrix<T> &matrix_); // Multiplication with self
    Matrix<T> *operator*=(const Matrix<T> &matrix_) const; // Return a new matrix

    Matrix<T> &operator*=(T a); // Multiply a constant with self
    Matrix<T> *operator*=(T a) const; // Multiply matrix by a constant and return new matrix

    Matrix<T> &operator+=(const Matrix<T> &matrix_); // Add a matrix with self
    Matrix<T> &operator+=(T a); // Sum a constant with self
    Matrix<T> *operator+(const Matrix<T> &matrix_) const; // Add and return a new matrix

    Matrix<T> &operator-=(T a); // Substract a constant with self
    Matrix<T> &operator-=(const Matrix<T> &matrix_); // Substract a matrix with self
    Matrix<T> *operator-(const Matrix<T> &matrix_) const; // Substract and return a new matrix

    void normalize(); // Normalize the matrix

    // Bonus (1pt), returns inverse of the Matrix
    Matrix<T> *inverse();

};

#endif

