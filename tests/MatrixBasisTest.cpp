//
// Created by thoth on 8/13/19.
//

#include <gtest/gtest.h>
#include "../src/Matrix.cpp"

namespace {

    TEST(Construtors, constrution_of_a_vector_with_cols_positives_ok){
        Matrix<int> matrix(5);
    }

    TEST(Construtors, constrution_of_a_vector_with_cols_negative_fail_catchcontrains_ok){
        EXPECT_ANY_THROW({
            Matrix<int> matrix(-100);
        });
    }

    TEST(Construtors, constrution_of_a_matrix_with_cols_positives_ok){
        Matrix<int> matrix(5, 5);
    }

    TEST(Construtors, constrution_of_a_matrix_with_cols_negative_fail_catchcontrains_ok){
        EXPECT_ANY_THROW({
                             Matrix<int> matrix(-100, -100);
                         });
        EXPECT_ANY_THROW({
                             Matrix<int> matrix(100, -100);
                         });
    }

}