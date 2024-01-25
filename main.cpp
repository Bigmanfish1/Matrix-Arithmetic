#include <iostream>
#include "matrix.h"
#include "vector.h"
#include <fstream>
#include <string>

using namespace std;

static void print(Arithmetic *mat) {
    mat->print();
    cout << endl;
}

static void readFile(istream &infile, Arithmetic *mat) {
    mat->readFile(infile);
}

//
static void task1() {
    ifstream infile("example_input.txt");
    // The test code below assumes that you have implemented all Task 1 functionality

    // 1. Test constructor:
    cout << "Constructors: " << endl;

    Matrix *m1 = new Matrix(3, 4);
    print(m1);

    Vector *v1 = new Vector(7);
    v1->print();
    print(v1);


    // read file.
    readFile(infile, v1);
    v1->print();

    cout << "vector  Test" << endl;
    Vector v2(3);

    cout << v2[0] << endl;

    readFile(infile, m1);
    m1->print();

    // Test assignment operator:
    Matrix *m2 = new Matrix(1, 4);
    print(m2);
    m2 = m1; // assignment
    print(m2);

    // Test getters
    cout << "Getters: " << endl;
    cout << m1->getRows() << endl;
    cout << m2->getCols() << endl;
    cout << v1->getSize() << endl;

//    // Test [][]
    cout << "Test [][]: " << endl;
    try {
        Matrix m4(3, 3);
        m4.readFile(infile);
        cout << m4[0][2] << endl;
        m4(0,2) = 5;
        cout << m4[0][2] << endl;
        m4(5,2) = 5;
    } catch (const char *error) {
        cout << error << endl;
    }

    infile.close();
}


static void task2() {

    // Matrix Arithmeitc:
    // The test code below assumes that you have implemented all Task 2 functionality.
    // ------------------------------------------------------------------------------
    // NOTE: The examples below are illustrative, NOT exhaustive. You must extend the
    // provided code with your own tests. Trigger every exception, make sure all corner
    // cases work. Test all operators!
    ifstream infile("example_input.txt");

    cout << "Matrix arithmetic" << endl;
    Matrix *m1 = new Matrix(2, 2);
    m1->readFile(infile);
    m1->print();
    cout<< endl;
    Matrix* m2 = new Matrix(2, 2);
    m2->readFile(infile);
    m2->print();
    cout<< endl;
    /*
        Matrix a = m1->operator*(*m2);
    a.print();
    cout<< endl;
    Matrix c = m1->operator^(3);
    c.print();
    */
    
    m2->readFile(infile);
    Matrix m3 = m2->operator~();
    //m1->operator*(*m2).print();
    Vector *vec1 = new Vector(5);
    vec1->readFile(infile);
    vec1->operator^=(2);
    vec1->print();
    
    Matrix n = m1->operator^(2);
    n.print();
    m1->print();
    // Scalar * matrix
    cout << "Matrix Multiplication by scalar:" << endl;
    m1->operator*(3.5).print();
    m1->operator*=(2);
    m1->print();

    cout << "Vector Multiplication by scalar:" << endl;
    //Vector *vec1 = new Vector(5);
    vec1->readFile(infile);
    vec1->print();

    vec1->operator*(3.5).print();
    vec1->operator*=(2);
    vec1->print();


    // Scalar / matrix
    cout << "Division by scalar:" << endl;
    try {
        m1->operator/(7.2).print();
        m1->operator/(0).print();
    } // should trigger exception
    catch(const char * err) { cout << err << endl; }
    
    //Matrix* m2 = new Matrix(6, 2);
    //m2->readFile(infile);
    //m1->operator*(*m2).print();

    infile.close();
}

static void task3() {
    //////////////////////////////////
    // The rest is linear equations //
    //////////////////////////////////
    ifstream infile("task3Input.txt");

    cout << "Reading matrices..." << endl;
    Matrix system(3,3), augmented(3,1);
    system.readFile(infile);
    augmented.readFile(infile);

    Matrix A = system;
    Matrix b = augmented;

    A.print();
    b.print();

    cout << "Reducing to upper-triangular form:" << endl;

    A |= b;

    A.print();
    b.print();

    cout << "Solving the system:" << endl;
    Matrix c = A|b;
    c.print();

    cout << "Reducing to upper-triangular form AND solving the system:" << endl;
    c = system|augmented;
    c.print();

    infile.close();
}

int main() {
    task1();
    task2();
    task3();
    return 0;
}
