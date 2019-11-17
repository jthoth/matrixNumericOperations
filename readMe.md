# Matrix Operations Using C++ v11

![N|Solid](http://howtolearn.me/wp-content/uploads/2014/06/c-++-logo.jpg)

[![Build Status](https://travis-ci.org/joemccann/dillinger.svg?branch=master)](https://travis-ci.org/joemccann/dillinger)

This project is a homework, it is part of CC7515-1 (GPU Computing).
# Description

This homework is geared for  learning  or remembering those features of c++. The main idea is build a class that let us compute some matrix operations.

### Tech

* [Os linux mint]- Debian based operative system.
* [C++ v11]- Programming language.
* [Clion] - Cross-Platform IDE for C and C++ by JetBrains
* [Google Test] - Testing and Mocking Framework

### Installation

Installing GoogleTest with Cling.

```sh
$ cd MatrixOperation
$ mkdir lib && cd lib
$ git clone https://github.com/google/googletest.git
```
After downloading the library you should add the next lines to makeFile of Clion.

- add_subdirectory(lib/googletest-master)
- include_directories(lib/googletest-master/googletest/include)
- target_link_libraries(GenneticProgramming gtest gtest_main)

### Homework Questions
- Does the type of data in your matrix affect anything? What happens if you perform multiplication operations?
tion or inverse with an integer or double data type
-- **Matrices with different data type are not compatibles**
-- **With the multiplication the matrix class does not suffer from any problem, due to the calculation algorithm since this class does not imply square roots divisions. However when computing an integer inverse matrix there are several problems due to data type and the algorithm**
- What happens if the matrix is normalized with an integer or with a double?
-- **For an integer matrix almost all values are zero except the maximun and for a double matrix all works ok**
- If you started using very small or very large numbers and mainly prime numbers, what happens in terms of accuracy?
-- **The data types in c plus are assigned max and min values in memory, and if we use large number these can overload and makes wrong calculations. A solution for that is be aware about the quantity of memory that you need for compute these large numbers.**
-Can there be precision problems if two identical matrices are compared but with different types?
-- **The operator == in the matrix implementation only support the same data type, however if you use the values of the matrix for comparison, some data types can be compared, but the precision could generate a computational error due that.**

### Inverse Matrix
The worst case of  inverse matrix implementation is O(n^3) and space cost is O(2 NxM), because we are using a numeric inverse computation.


License
----

MIT



