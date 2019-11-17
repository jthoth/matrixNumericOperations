//
// Created by thoth on 8/13/19.
//

#include <sstream>
#include <cmath>
#include <fstream>
#include "Matrix.h"

template<class T>
Matrix<T>::Matrix(const Matrix &obj): rows(obj.rows),
cols(obj.cols){
    this->matrix = new T *[obj.rows];
    copy(obj);
}

template<class T>
void Matrix<T>::copy(const Matrix<T> &obj) const {
    for (int i = 0; i < this->rows; ++i) {
        this->matrix[i] = new T [this->cols];
        for (int j = 0; j < this->cols; ++j) {
            this->matrix[i][j]  = obj.matrix[i][j];
        }
    }
}

template<class T>
void Matrix<T>::value_setter(T *&container, T value) {
    for (int i = 0; i < this->cols; ++i)
        container[i] = value;
}

template<class T>
Matrix<T>::Matrix(int cols): cols(cols), rows(1),
matrix(new T *[rows]){
    this->row_col_greater_than_zero_checker();
    this->matrix_initialization();
}

template<class T>
Matrix<T>::Matrix(int rows,  int cols) : cols(cols), rows(rows){
    this->row_col_greater_than_zero_checker();
    this->matrix = new T *[rows];
    this->matrix_initialization();
}

template<class T>
void Matrix<T>::row_col_greater_than_zero_checker() {
    if(this->cols < 0 || this->rows < 0){
        throw std::logic_error("[Matrix] The column and row "
                               "numbers should be positives");
    }
}

template<class T>
void Matrix<T>::matrix_initialization() {
    for (int i = 0; i < this->rows; ++i) {
        auto vector = new T [this->cols];
        this->value_setter(vector, 0);
        this->matrix[i] = vector;
    }
}

template<class T>
void Matrix<T>::set(int i, int j, T value) {
    this->update_max(value);
    this->update_min(value);
    this->range_constrains(i, j);
    this->matrix[i][j] = value;
}

template<class T>
T Matrix<T>::get(int i, int j){
    this->range_constrains(i, j);
    return this->matrix[i][j];
}

template<class T>
void Matrix<T>::fill(T value) {
    this->min_value = this->max_value = value;
    for (int i = 0; i < this->rows; ++i)
        this->value_setter(this->matrix[i], value);
}

template<class T>
void Matrix<T>::range_constrains(int &row, int &col) {
    if(in_range(rows, row) || in_range(cols, col)){
        throw std::logic_error("[Matrix] Index out of range");
    }
}

template<class T>
bool Matrix<T>::in_range(int &constrain, int &value) {
    return !(-1 < value && value < constrain);
}

template<class T>
int *Matrix<T>::size() const {
    int *_size = new int [2];
    _size[0] = this->rows;
    _size[1] = this->cols;

    return _size;
}

template<class T>
int Matrix<T>::length() const {
    return MAX(this->cols, this->rows);
}

template<class T>
T Matrix<T>::max() const {
    return this->max_value;
}

template<class T>
T Matrix<T>::min() const {
    return this->min_value;
}

template<class T>
void Matrix<T>::update_min(T value) {
    if(value < this->min_value){
        this->min_value = value;
    }
}

template<class T>
void Matrix<T>::update_max(T value) {
    if(value > this->max_value){
        this->max_value = value;
    }
}

template<class T>
void Matrix<T>::constrain_square_matrix() {
    if(!this->is_square()){
        throw std::logic_error("[Matrix] might be square");
    }
}

template<class T>
T Matrix<T>::norm() const {
    T _norm = 0;
    for (int i = 0; i < this->rows; ++i) {
        for (int j = 0; j < this->cols; ++j) {
            _norm += std::pow(this->matrix[i][j], 2);
        }
    }
    return std::sqrt(_norm);
}

template<class T>
void Matrix<T>::display() const {
    for (int i = 0; i < this->rows; ++i) {
        for (int j = 0; j < this->cols; ++j) {
            std::cout<<this->matrix[i][j]<<'\t';
        }
        std::cout<<'\n';
    }
}

template<class T>
void Matrix<T>::save_to_file(const std::string& filename) {
    std::ofstream outfile(filename, std::ios::trunc);
    for (int i = 0; i < this->rows; ++i) {
        outfile << this->array_to_string(i) << '\n';
    }
}

template<class T>
std::string Matrix<T>::array_to_string(int row) {
    std::ostringstream container;
    for (int j = 0; j < this->cols; ++j) {
        container << this->matrix[row][j] << '\t';
    }
    return container.str();
}

template<class T>
Matrix<T> *Matrix<T>::clone(){
    return new Matrix<T>(*this);
}

template<class T>
bool Matrix<T>::equals(Matrix<T> *matrix_){
    if(matrix_->cols != this->cols || matrix_->rows != this->rows)
        return false;

    for (int i = 0; i < this->rows; ++i) {
        if(!this->v_equal(this->matrix[i], matrix_->matrix[i]))
            return false;
    }
    return true;
}
template<class T>
bool Matrix<T>::is_diag() const {
    for (int i = 0; i < this->rows; ++i) {
        for (int j = 0; j < this->cols; ++j) {
            if(i != j && this->matrix[i][j] != 0)
                return false;
        }
    }
    return true;
}

template<class T>
bool Matrix<T>::is_identity() {
    for (int i = 0; i < this->rows; ++i) {
        for (int j = 0; j < this->cols; ++j) {
            if(!this->identity_conditions(i, j))
                return false;
        }
    }
    return true;
}

template<class T>
bool Matrix<T>::is_square() const {
    return this->rows == this->cols;
}

template<class T>
bool Matrix<T>::is_vector() const {
    return this->rows == 1;
}

template<class T>
bool Matrix<T>::is_symmetric() const {
    for (int i = 0; i < this->rows; ++i) {
        for (int j = 0; j < this->cols; ++j) {
            if(this->matrix[i][j] != this->matrix[j][i])
                return false;
        }
    }
    return true;
}

template<class T>
bool Matrix<T>::operator==(const Matrix<T> &matrix_){
    if(matrix_.cols != this->cols || matrix_.rows != this->rows)
        return false;
    for (int i = 0; i < this->rows; ++i) {
        if(!this->v_equal(this->matrix[i], matrix_.matrix[i]))
            return false;
    }
    return true;
}

template<class T>
bool Matrix<T>::operator!=(const Matrix<T> &matrix_){
    if(matrix_.cols != this->cols || matrix_.rows != this->rows)
        return true;
    for (int i = 0; i < this->rows; ++i) {
        if(!this->v_equal(this->matrix[i], matrix_.matrix[i]))
            return true;
    }
    return false;
}

template<class T>
T **Matrix<T>::values() const {
    return this->matrix;
}

template<class T>
bool Matrix<T>::v_equal(T *&local, T *&external) {
    for (int j = 0; j < this->cols; ++j) {
        if(local[j] != external[j]){
            return false;
        }
    }
    return true;
}

template<class T>
bool Matrix<T>::identity_conditions(int &i, int &j) {
    if(i == j && this->matrix[i][j] != 1)
        return false;
    return !(i != j && this->matrix[i][j] != 0);
}

template<class T>
Matrix<T> *Matrix<T>::transpose() {
    auto _matrix = new Matrix<T>(*this);
    for (int i = 0; i < this->cols; ++i) {
        for (int j = 0; j < this->cols; ++j) {
            _matrix->set(j, i, this->matrix[i][j]);
        }
    }
    return _matrix;
}

template<class T>
void Matrix<T>::sequential_fill() {
    T container = 0;
    for (int i = 0; i < this->rows; ++i) {
        for (int j = 0; j < this->cols; ++j) {
            this->set(i, j, ++container);
        }
    }
    this->min_value = 1;
    this->max_value = this->rows * this->cols;
}

template<class T>
Matrix<T> &Matrix<T>::operator*=(T a) {
    for (int i = 0; i < this->rows; ++i) {
        for (int j = 0; j < this->cols; ++j) {
            this->set(i, j, this->get(i, j) * a);
        }
    }
    return *this;
}

template<class T>
Matrix<T> *Matrix<T>::operator*=(T a) const {
    auto new_matrix = this->clone();
    new_matrix *= a;
    return new_matrix;
}

template<class T>
Matrix<T> &Matrix<T>::operator+=(const Matrix<T> &matrix_) {
    for (int i = 0; i < this->rows; ++i) {
        for (int j = 0; j < this->cols; ++j) {
            this->set(i, j, this->get(i, j) + matrix_.matrix[i][j]);
        }
    }
    return *this;
}

template<class T>
Matrix<T> &Matrix<T>::operator-=(const Matrix<T> &matrix_) {
    for (int i = 0; i < this->rows; ++i) {
        for (int j = 0; j < this->cols; ++j) {
            this->set(i, j, this->get(i, j) - matrix_.matrix[i][j]);
        }
    }
    return *this;
}

template<class T>
Matrix<T> *Matrix<T>::operator+(const Matrix<T> &matrix_) const {
    auto _matrix = new Matrix<T>(*this);
    for (int i = 0; i < this->rows; ++i) {
        for (int j = 0; j < this->cols; ++j) {
            _matrix->set(i, j, _matrix->get(i, j) + matrix_.matrix[i][j]);
        }
    }
    return _matrix;
}

template<class T>
Matrix<T> *Matrix<T>::operator-(const Matrix<T> &matrix_) const {
    auto _matrix = new Matrix<T>(*this);
    for (int i = 0; i < this->rows; ++i) {
        for (int j = 0; j < this->cols; ++j) {
            _matrix->set(i, j, _matrix->get(i, j) - matrix_.matrix[i][j]);
        }
    }
    return _matrix;
}

template<class T>
void Matrix<T>::normalize() {
    for (int i = 0; i < this->rows; ++i) {
        for (int j = 0; j < this->cols; ++j) {
            this->set(i, j, this->get(i, j) / this->max_value);
        }
    }
}

template<class T>
void Matrix<T>::constrains_matrix_multiplication(int n_cols, int n_rows) {
    if(n_cols != n_rows){
        throw std::logic_error("[Matrix] A(m) cols should "
                               "be equals B(n) rows");
    }
}

template<class T>
Matrix<T> &Matrix<T>::operator+=(T a) {
    for (int i = 0; i < this->rows; ++i) {
        for (int j = 0; j < this->cols; ++j) {
            this->set(i, j, this->get(i, j) + a);
        }
    }
    return *this;
}


template<class T>
Matrix<T> &Matrix<T>::operator-=(T a) {
    for (int i = 0; i < this->rows; ++i) {
        for (int j = 0; j < this->cols; ++j) {
            this->set(i, j, this->get(i, j) - a);
        }
    }
    return *this;
}

template<class T>
T Matrix<T>::det() {
    this->constrain_square_matrix();
    return this->numerical_determinant();
}

template<class T>
T Matrix<T>::recursive_determinant(T **matrix_, int n) {
    T determinant_ = 0;
    if(n == 2){
        return this->determinant_2x2(matrix_);
    }else{
        for (int i = 0; i < n; ++i) {
            determinant_ += (std::pow(-1, i) * matrix_[i][0] *
                    recursive_determinant(sub_matrix(matrix_, n, i), n -1));
        }
    }
    return determinant_;
}

template<class T>
T **Matrix<T>::sub_matrix(T **matrix_, int n, int i) {
    T **container = new T *[n - 1]; int _i = 0, _j =0;
    for (int k = 0; k < n; ++k) {
        if(k == i) continue;
        container[_i] = new T[n - 1]; _j = 0;
        for (int l = 0; l < n; ++l) {
            if(l == 0) continue;
            container[_i][_j++] = matrix_[k][l];
        } _i++;
    }
    return container;
}

template<class T>
T Matrix<T>::determinant_2x2(T **&matrix_) {
    return (matrix_[0][0] * matrix_[1][1]) - (matrix_[0][1] * matrix_[1][0]);
}

template<class T>
Matrix<T> &Matrix<T>::operator*=(const Matrix<T> &matrix_) {
    constrains_matrix_multiplication(this->cols, matrix_.rows);
    auto result = this->matrix_multiplication(matrix_);
    this->cols = result->cols; this->rows, result->rows;
    this->min_value = result->min_value;
    this->max_value = result->max_value;
    this->matrix = result->matrix;
    return *this;
}

template<class T>
Matrix<T> *Matrix<T>::matrix_multiplication(Matrix<T> B) {
    auto container = new Matrix<T>(this->rows, B.cols);
    for (int i = 0; i < this->rows; ++i) {
        for (int j = 0; j < B.cols; ++j) {
            T accumulator = 0;
            for (int k = 0; k < this->rows; ++k) {
                accumulator += this->get(i, k) * B.get(k, j);
            }
            container->set(i, j, accumulator);
        }
    }
    return container;
}

template<class T>
Matrix<T> *Matrix<T>::operator*=(const Matrix<T> &matrix_) const {
    constrains_matrix_multiplication(this->cols, matrix_.rows);
    return this->matrix_multiplication(matrix_);
}

template<class T>
T Matrix<T>::numerical_determinant() {
    auto _matrix = new Matrix<T>(*this); float rate;

    for (int i = 0; i < (this->cols / 2 ) + 1; ++i) {
        for (int j = 0; j < this->cols; ++j) {
            if(i != j){
                rate = _matrix->get(j, i)/_matrix->get(i, i);
                for (int k = 0; k < this->cols; ++k) {
                    _matrix->matrix[j][k] -= rate*_matrix->get(i, k);
                }
            }
        }
    }


    T determinant_ = 1;
    for (int l = 0; l < this->cols; ++l) {
        determinant_ *= _matrix->get(l, l);
    }

    delete _matrix;
    return std::isnan(determinant_) ? 0 : determinant_;
}

template<class T>
Matrix<T> *Matrix<T>::inverse() {
    this->constrain_square_matrix();
    float rate = 0;

    auto _matrix = new Matrix<T>(*this);

    auto _inverse = new Matrix<T>(*this);
    _inverse->fill_identity();

    for (int i = 0; i < this->cols; ++i) {
        for (int j = 0; j < this->cols; ++j) {
            if(i != j){
                rate = _matrix->get(j, i)/_matrix->get(i, i);
                for (int k = 0; k < this->cols; ++k) {
                    _matrix->matrix[j][k] -= rate*_matrix->get(i, k);
                    _inverse->matrix[j][k] -= rate*_inverse->get(i, k);
                }
            }
        }
    }

    for (int l = 0; l < this->cols; ++l) {
        T fraction = _matrix->matrix[l][l];
        for (int m = 0; m < this->cols; ++m) {
            _inverse->matrix[l][m] /= fraction;
        }
    }


    return _inverse;
}

template<class T>
void Matrix<T>::fill_identity() {
    for (int i = 0; i < this->rows; ++i) {
        for (int j = 0; j < this->cols; ++j) {
            if(i == j)
                this->set(i, j, 1);
            else
                this->set(i, j, 0);
        }
    }
}

template<class T>
Matrix<T>::~Matrix(){
    delete[] this->matrix;
}