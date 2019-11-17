//
// Created by thoth on 8/13/19.
//

#include <gtest/gtest.h>
#include "../src/Matrix.cpp"

namespace {

    class MatrixDimensionTest : public testing::Test {
    protected:

        void TearDown() override {
            delete matrix_;
        }

        Matrix<int> *matrix_ = new Matrix<int>(4, 5);
    };

    TEST_F(MatrixDimensionTest, get_dimentions_should_be_ok){
        int *size = matrix_->size();
        EXPECT_EQ(size[0], 4);
        EXPECT_EQ(size[1], 5);
    }

    TEST_F(MatrixDimensionTest, get_length_should_be_ok){
        int length = matrix_->length();
        EXPECT_EQ(length, 5);
    }

}