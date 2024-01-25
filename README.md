# C++ Terminal-Based Matrix Caclculator

#### Overview

This C++ terminal-based matrix calculator is developed as part of the COS110 Assignment 2 at the University of Pretoria. The goal of this project is to create a mathematical library for various matrix manipulations and solving systems of linear equations using operator overloading.

#### Features
Matricies can be read from a file once put in particular format, the program will calculate the dimensions and will place each value into the correct entry in the matrix. Matricies can also be initialised to be empty matricies.

####Matrices and Vectors

-Implemented a Matrix class for two-dimensional dynamic arrays and a Vector class for one-dimensional dynamic arrays.

-Constructors to create matrices and vectors with specified dimensions.

-Overloaded operators for matrix and vector arithmetic, including addition, subtraction, scalar multiplication, division, and element-wise operations.

-Input and output functionality for matrices and vectors, supporting file reading and console printing.

#### Matrix Arithmetic

-Implemented basic matrix arithmetic operations, such as addition, subtraction, scalar multiplication, and division using operator overloading.

-Ensured error handling for invalid operations, such as adding or multiplying matrices of different dimensions.

-Implemented matrix multiplication, ensuring compatibility between the number of columns in the first matrix and the number of rows in the second matrix.

#### Gaussian Elimination

-Implemented the Gaussian elimination algorithm to solve systems of linear equations.

-Overloaded operators to reduce a system of linear equations to upper-triangular form and perform back-substitution to obtain the solution matrix.

-Provided error messages for cases like non-square matrices and incorrect augmentations.

#### How to Run

-Clone the repo

-Run: `make && make run`
