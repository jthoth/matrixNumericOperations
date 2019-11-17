cmake_minimum_required(VERSION 3.14)
project(MatrixOperations)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(lib/googletest)
include_directories(lib/googletest/googletest/include)

add_executable(MatrixOperations main.cpp src/Matrix.cpp src/Matrix.h tests/MatrixBasisTest.cpp tests/MatrixGetterSettersTest.cpp tests/MatrixDimentionsTest.cpp tests/MatrixValuesTest.cpp tests/MatrixUtilitarianTests.cpp tests/MatrixBooleanTest.cpp tests/MatrixOperationTests.cpp tests/MatrixQuestionTests.cpp)

target_link_libraries(MatrixOperations gtest gtest_main)