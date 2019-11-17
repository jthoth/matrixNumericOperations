//
// Created by thoth on 8/13/19.
//

#include <gtest/gtest.h>
#include "../src/Matrix.cpp"

namespace {

    class MatrixValuesTest : public testing::Test {
    protected:

        void TearDown() override {
            delete matrix_;
        }

        Matrix<float> *matrix_ = new Matrix<float>(4, 4);
    };

    TEST_F(MatrixValuesTest, get_max_value_should_be_ok){
        matrix_->sequential_fill();
        ASSERT_FLOAT_EQ(16, matrix_->max());
        matrix_->set(0, 0,  100);
        ASSERT_FLOAT_EQ(100, matrix_->max());
    }

    TEST_F(MatrixValuesTest, get_min_value_should_be_ok){
        matrix_->sequential_fill();
        ASSERT_FLOAT_EQ(1, matrix_->min());
        matrix_->set(3, 0,  -30);
        ASSERT_FLOAT_EQ(-30, matrix_->min());
    }

    TEST_F(MatrixValuesTest, get_determinant_should_be_ok){
        float expected = -3752.4;

        matrix_->sequential_fill();
        matrix_->set(3, 3, 4.1);
        matrix_->set(3, 2, 0.2);
        matrix_->set(0, 0, 54);

        ASSERT_FLOAT_EQ(expected, matrix_->det());

    }


    TEST_F(MatrixValuesTest, get_norm_should_be_ok){
        float expected = 62.823959;

        matrix_->sequential_fill();
        matrix_->set(3, 3, 4.1);
        matrix_->set(3, 2, 0.2);
        matrix_->set(0, 0, 54);

        ASSERT_FLOAT_EQ(expected, matrix_->norm());
    }


}