//
// Created by thoth on 8/13/19.
//

#include <gtest/gtest.h>
#include "../src/Matrix.cpp"

namespace {

    class MatrixUtilitarianTest : public testing::Test {
    protected:
        void TearDown() override {
            delete matrix_;
        }

        Matrix<int> *matrix_ = new Matrix<int>(4, 4);
    };

    TEST_F(MatrixUtilitarianTest, save_file_and_check_existance_should_be_ok){
        std::string file_name = "matrix.txt";

        matrix_->fill_identity();
        matrix_->save_to_file(file_name);
        std::ifstream infile(file_name);
        ASSERT_EQ(true, infile.good());

        infile.close();
    }

    TEST_F(MatrixUtilitarianTest, clone_matrix_check_some_randoms_values_should_be_ok){
        matrix_->sequential_fill();
        auto copy = matrix_->clone();
        copy->set(0, 0, 100);

        ASSERT_FALSE(matrix_->get(0, 0) == copy->get(0, 0));
    }

}