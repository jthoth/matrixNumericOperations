//
// Created by thoth on 8/13/19.
//

#include <gtest/gtest.h>
#include "../src/Matrix.cpp"

namespace {

    class MatrixGetterTest : public testing::Test {
    protected:
        void TearDown() override {
            delete matrix_;
        }

        Matrix<int> *matrix_ = new Matrix<int>(4, 4);
    };



    TEST_F(MatrixGetterTest, set_correct_index_test_should_be_ok){
        matrix_->set(0, 0, 3);
        EXPECT_TRUE(3 == matrix_->get(0, 0));
    }

    TEST_F(MatrixGetterTest, set_incorrect_index_test_should_be_wrong){
        matrix_->set(0, 0, 3);
        EXPECT_ANY_THROW({matrix_->get(100, 5); });
    }


    TEST_F(MatrixGetterTest, set_fill_x_value_should_be_ok){
        matrix_->fill(5);

        EXPECT_TRUE(5 == matrix_->get(0, 0));
        EXPECT_TRUE(5 == matrix_->get(3, 1));
        EXPECT_TRUE(5 == matrix_->get(3, 2));
        EXPECT_FALSE(3 == matrix_->get(1, 1));
    }

    TEST_F(MatrixGetterTest, set_sequential_fill_x_value_should_be_ok){
        matrix_->sequential_fill();
        EXPECT_TRUE(6 == matrix_->get(1, 1));
        EXPECT_FALSE(100 == matrix_->get(3, 3));
    }

}