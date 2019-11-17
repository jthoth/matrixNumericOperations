//
// Created by thoth on 8/13/19.
//

#include <gtest/gtest.h>
#include "../src/Matrix.cpp"

namespace {

    class MatrixQuestionsTest : public testing::Test {
    protected:

        void TearDown() override {
            delete A;
            delete B;

        }

        Matrix<int> *A = new Matrix<int>(3, 3);
        Matrix<float> *B = new Matrix<float>(3, 3);
        Matrix<double> *C = new Matrix<double>(3, 3);

    };

    TEST_F(MatrixQuestionsTest, data_type_affect_matrix_operations_should_be_ok){
        A->sequential_fill();
        B->sequential_fill();
        C->sequential_fill();

        //*A *= *B; Matrix with diferents data type does not have procedures

        *A *= *A;
        *B *= *B;
        *C *= *C;

        // Con la multiplicacion la clase matrix no sufre de ningun problema
        // debido al algoritmo de calculo ya que este no implica raices cuadradas
        // ni divisiones.


        auto N = B->inverse();
        auto O = C->inverse();

        // Cuando se calcual la inversa con double o float funciona correctamente
        // dado que estos soportan operaciones fraccionales

        //auto M = A->inverse();
        // Sin embargo con la matrix de numeros enteros el prgrama cae a una excpsion
        // arithmetica ya que el algoritmo usa divisiones y es altamente probrable que
        // aparezca una division para zero

    }

    TEST_F(MatrixQuestionsTest, normalization_different_datatypes){
        A->sequential_fill();
        A->normalize();

        C->sequential_fill();
        C->normalize();

        // Para la matriz normalizada de numeros enteros todos los valores
        // excepto el mayor es cero

        // Para la matrix de numeros de tipo double funciona correctamente.

        *A == *C;
    }

}