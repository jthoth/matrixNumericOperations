//
// Created by thoth on 8/13/19.
//

#include <gtest/gtest.h>
#include "../src/Matrix.cpp"

namespace {

    class MatrixOperationTest : public testing::Test {
    protected:

        void TearDown() override {
            delete A;
            delete B;
            delete C;
            delete D;
        }

        Matrix<float> *A = new Matrix<float>(4, 4);
        Matrix<float> *B = new Matrix<float>(4, 3);
        Matrix<float> *C = new Matrix<float>(3, 3);
        Matrix<float> *D = new Matrix<float>(3, 3);

    };

    TEST_F(MatrixOperationTest, get_transpose_matrix_should_be_ok){
        D->sequential_fill();

        D->set(1, 0, 2);
        D->set(2, 0, 3);
        D->set(2, 1, 6);

        D->set(0, 1, 4);
        D->set(0, 2, 7);
        D->set(1, 2, 8);

        C->sequential_fill();

        auto H = C->transpose();

        ASSERT_TRUE(*D == *H);

        delete H;

    }

    TEST_F(MatrixOperationTest, compute_matrix_multiplication_same_object_should_be_ok){

        A->sequential_fill();
        B->sequential_fill();


        *A *= *B;

        B->fill(0); // Reseting Matrix same mxl

        B->set(0 ,0, 70);
        B->set(0 ,1, 80);
        B->set(0 ,2, 90);

        B->set(1 ,0, 158);
        B->set(1 ,1, 184);
        B->set(1 ,2, 210);

        B->set(2 ,0, 246);
        B->set(2 ,1, 288);
        B->set(2 ,2, 330);

        B->set(3 ,0, 334);
        B->set(3 ,1, 392);
        B->set(3 ,2, 450);


        ASSERT_TRUE( *A == *B);

    }

    TEST_F(MatrixOperationTest, compute_multiplication_with_scalar_should_be_ok){
        C->fill(3);
        D->fill(1);

        *D *= 3;

        ASSERT_TRUE( *D == *C);

    }


    TEST_F(MatrixOperationTest, compute_add_between_two_matrix_should_be_ok){
        C->fill(1);
        D->fill(2);

        *C += *C;

        ASSERT_TRUE( *D == *C);

    }

    TEST_F(MatrixOperationTest, compute_substract_between_two_matrix_should_be_ok){
        C->fill(1);

        *C -= *C;

        ASSERT_TRUE( *D == *C); // D is a zero matrix

    }

    TEST_F(MatrixOperationTest, compute_normalization_matrix_should_be_ok){
        A->sequential_fill();
        float max = A->max(), accumulator = 1;

        A->normalize();

        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                ASSERT_TRUE( A->get(i, j)  == accumulator / max);
                ++accumulator;
            }
        }
    }

    TEST_F(MatrixOperationTest, compute_inverse_matrix_should_be_ok){

        D->set(0, 0, 25);
        D->set(0, 1, 12);
        D->set(0, 2, 11);

        D->set(1, 0, 3);
        D->set(1, 1, 7);
        D->set(1, 2, 35);

        D->set(2, 0, 40);
        D->set(2, 1, 5);
        D->set(2, 2, 10);

        auto G = D->inverse();

        ASSERT_FLOAT_EQ(G->get(0, 0), -0.00963303);
        ASSERT_FLOAT_EQ(G->get(0, 1), -0.0059633064);
        ASSERT_FLOAT_EQ(G->get(0, 2), 0.0314679);

        ASSERT_FLOAT_EQ(G->get(1, 0), 0.125688);
        ASSERT_FLOAT_EQ(G->get(1, 1), -0.017431185);
        ASSERT_FLOAT_EQ(G->get(1, 2), -0.0772477);

        ASSERT_FLOAT_EQ(G->get(2, 0), -0.024311924);
        ASSERT_FLOAT_EQ(G->get(2, 1), 0.0325688);
        ASSERT_FLOAT_EQ(G->get(2, 2), 0.012752293);


    }




}