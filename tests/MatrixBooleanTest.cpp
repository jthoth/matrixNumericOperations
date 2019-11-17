//
// Created by thoth on 8/13/19.
//

#include <gtest/gtest.h>
#include "../src/Matrix.cpp"

namespace {

    class MatrixBooleanTest : public testing::Test {
    protected:

        void TearDown() override {
            delete A;
            delete B;
            delete C;
        }

        Matrix<float> *A = new Matrix<float>(4, 4);
        Matrix<float> *B = new Matrix<float>(4, 4);
        Matrix<float> *C = new Matrix<float>(3, 3);

    };

    TEST_F(MatrixBooleanTest, matrix_equals_should_be_ok){
        A->sequential_fill();
        B->sequential_fill();
        ASSERT_TRUE(A->equals(B));
    }


    TEST_F(MatrixBooleanTest, matrix_is_diag_should_be_ok){
        A->fill_identity();
        ASSERT_TRUE(A->is_diag());
    }

    TEST_F(MatrixBooleanTest, matrix_is_diag_should_be_false){
        A->sequential_fill();
        ASSERT_FALSE(A->is_diag());
    }

    TEST_F(MatrixBooleanTest, matrix_is_identity_should_be_ok){
        A->fill_identity();
        ASSERT_TRUE(A->is_identity());
    }

    TEST_F(MatrixBooleanTest, matrix_is_identity_should_be_false){
        A->sequential_fill();
        ASSERT_FALSE(A->is_identity());
    }

    TEST_F(MatrixBooleanTest, matrix_is_symmetric_should_be_ok){
        A->fill_identity();
        ASSERT_TRUE(A->is_symmetric());
    }

    TEST_F(MatrixBooleanTest, matrix_is_symmetric_should_be_false){
        A->sequential_fill();
        ASSERT_FALSE(A->is_symmetric());
    }

    TEST_F(MatrixBooleanTest, matrix_is_square_should_be_ok){
        ASSERT_TRUE(A->is_square());
    }

    TEST_F(MatrixBooleanTest, matrix_is_vector_should_be_false){
        ASSERT_FALSE(A->is_vector());
    }

    TEST_F(MatrixBooleanTest, matrix_equal_operator_should_be_ok){
        ASSERT_TRUE(*A == *B);
    }

    TEST_F(MatrixBooleanTest, matrix_different_operator_should_be_ok){
        B->set(0, 0, 100);
        ASSERT_TRUE(*A != *B);
    }

    TEST_F(MatrixBooleanTest, matrix_different_size_operator_should_be_ok){
        ASSERT_TRUE(*A != *C);
    }




}