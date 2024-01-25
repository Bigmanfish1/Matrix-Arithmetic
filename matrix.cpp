#include "matrix.h"

using namespace std;

Matrix::Matrix(unsigned r, unsigned c)
{
    rows = r;
    cols = c;
    matrix = new double *[r];
    for (int i = 0; i < r; i++)
    {
        matrix[i] = new double[c];
        for (int j = 0; j < c; j++)
        {
            matrix[i][j] = 0;
        }
    }
}

Matrix::~Matrix()
{
    if (matrix != NULL)
    {
        for (int i = 0; i < rows; i++)
        {
            if (matrix[i] != NULL)
            {
                delete[] matrix[i];
            }
        }
        delete[] matrix;
        matrix = NULL;
    }
}

Matrix::Matrix(const Matrix &rhs)
{
    this->rows = rhs.rows;
    this->cols = rhs.cols;
    this->matrix = new double *[this->rows];
    for (int i = 0; i < this->rows; i++)
    {
        this->matrix[i] = new double[this->cols];
        for (int j = 0; j < this->cols; j++)
        {
            this->matrix[i][j] = rhs.matrix[i][j];
        }
    }
}

const Matrix &Matrix::operator=(const Matrix &rhs)
{
    if (this == &rhs)
    {
        return *this;
    }

    for (int i = 0; i < this->rows; i++)
    {
        delete[] this->matrix[i];
    }
    delete[] matrix;
    matrix = NULL;

    this->rows = rhs.rows;
    this->cols = rhs.cols;
    this->matrix = new double *[this->rows];

    for (int i = 0; i < this->rows; i++)
    {
        this->matrix[i] = new double[this->cols];
        for (int j = 0; j < this->cols; j++)
        {
            this->matrix[i][j] = rhs.matrix[i][j];
        }
    }
    return *this;
}

void Matrix::readFile(istream &inFile)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            inFile >> matrix[i][j];
        }
    }
}

void Matrix::print()
{
    cout << setprecision(3);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            cout << setw(10) << matrix[i][j];
        }
        cout << endl;
    }
}

double &Matrix::operator()(unsigned r, unsigned c)
{
    if (r < 0 || r >= rows)
    {
        throw "Error: invalid row index";
    }
    else if (c < 0 || c >= cols)
    {
        throw "Error: invalid column index";
    }
    else
    {
        return matrix[r][c];
    }
}

const double &Matrix::operator()(unsigned r, unsigned c) const
{
    if (r < 0 || r >= rows)
    {
        throw "Error: invalid row index";
    }
    else if (c < 0 || c >= cols)
    {
        throw "Error: invalid column index";
    }
    else
    {
        Vector vec = operator[](r);
        return vec[c];
    }
}

Vector Matrix::operator[](const unsigned r) const
{
    double *arr = new double[cols];
    for (int i = 0; i < cols; i++)
    {
        arr[i] = matrix[r][i];
    }

    Vector vector(cols);
    vector.setVector(arr);

    return vector;
}

unsigned Matrix::getRows() const
{
    return rows;
}

unsigned Matrix::getCols() const
{
    return cols;
}

Matrix Matrix::operator+(const Matrix &rhs)
{
    Matrix ob(this->rows, this->cols);
    if (this->rows != rhs.rows || this->cols == rhs.cols)
    {
        throw "Error: adding matrices of different dimensionality";
    }
    else
    {

        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                ob.matrix[i][j] = this->matrix[i][j] + rhs.matrix[i][j];
            }
        }
    }
    return ob;
}

Matrix &Matrix::operator+=(const Matrix &rhs)
{
    if (this->rows != rhs.rows || this->cols != rhs.cols)
    {
        throw "Error: adding matrices of different dimensionality";
    }
    else
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                this->matrix[i][j] = this->matrix[i][j] + rhs.matrix[i][j];
            }
        }
    }
    return *this;
}

Matrix Matrix::operator-(const Matrix &rhs)
{
    Matrix ob(rows, cols);
    if (this->rows != rhs.rows || this->cols != rhs.cols)
    {
        throw "Error: subtracting matrices of different dimensionality";
    }
    else
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                ob.matrix[i][j] = this->matrix[i][j] - rhs.matrix[i][j];
            }
        }
    }

    return ob;
}

Matrix &Matrix::operator-=(const Matrix &rhs)
{
    if (this->rows != rhs.rows || this->cols != rhs.cols)
    {
        throw "Error: subtracting matrices of different dimensionality";
    }
    else
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                this->matrix[i][j] = this->matrix[i][j] - rhs.matrix[i][j];
            }
        }
    }
    return *this;
}

Matrix Matrix::operator*(const Matrix &rhs)
{
    Matrix ob(this->rows, rhs.cols);
    if (this->cols != rhs.rows)
    {
        throw "Error: invalid matrix multiplication";
    }
    else
    {
        double sum = 0.0;

        for (int col = 0; col < this->rows; col++)
        {
            for (int r = 0; r < rhs.cols; r++)
            {

                for (int c = 0; c < cols; c++)
                {

                    sum += (this->matrix[col][c] * rhs.matrix[c][r]);
                }
                ob.matrix[col][r] = sum;
                sum = 0.0;
            }
        }
    }

    return ob;
}

Matrix &Matrix::operator*=(const Matrix &rhs)
{
    if (this->cols != rhs.rows)
    {
        throw "Error: invalid matrix multiplication";
    }
    else
    {
        double **temp = new double *[this->rows];
        for (int i = 0; i < this->rows; i++)
        {
            temp[i] = new double[rhs.cols];
            for (int j = 0; j < rhs.cols; j++)
            {
                temp[i][j] = 0.0;
            }
        }

        double sum = 0.0;
        for (int row = 0; row < this->rows; row++)
        {
            for (int colS = 0; colS < cols; colS++)
            {
                for (int col = 0; col < cols; col++)
                {
                    sum += (this->matrix[row][col] * rhs.matrix[col][colS]);
                }
                temp[row][colS] = sum;
                sum = 0.0;
            }
        }

        for (int i = 0; i < this->rows; i++)
        {
            delete[] matrix[i];
        }
        delete[] matrix;
        matrix = NULL;

        this->cols = rhs.cols;
        matrix = new double *[this->rows];

        for (int i = 0; i < this->rows; i++)
        {
            matrix[i] = new double[this->cols];
            for (int j = 0; j < rhs.cols; j++)
            {
                matrix[i][j] = temp[i][j];
            }
        }
        /*
            for (int i = 0; i < this->rows; i++)
            {
                delete[] temp[i];
            }
            delete[] temp;
            temp = NULL;
        */
    }

    return *this;
}

Matrix Matrix::operator^(int pow)
{
    Matrix ob = *this;
    if (this->rows != this->cols)
    {
        throw "Error: non-square matrix provided";
    }
    else if (pow < 0)
    {
        throw "Error: negative power is not supported";
    }
    else if (pow == 0)
    {
        for (int row = 0; row < this->rows; row++)
        {
            for (int col = 0; col < this->cols; col++)
            {
                if (row == col)
                {
                    ob.matrix[row][col] = 1;
                }
                else
                {
                    ob.matrix[row][col] = 0;
                }
            }
        }
    }
    else
    {
        double **temp = new double *[rows];
        for (int i = 0; i < rows; i++)
        {
            temp[i] = new double[cols];
            for (int j = 0; j < cols; j++)
            {
                temp[i][j] = 0.0;
            }
        }

        double sum = 0.0;
        for (int i = 1; i < pow; i++)
        {

            for (int row = 0; row < this->rows; row++)
            {
                for (int colS = 0; colS < cols; colS++)
                {
                    for (int col = 0; col < cols; col++)
                    {
                        sum += (ob.matrix[row][col] * this->matrix[col][colS]);
                    }
                    temp[row][colS] = sum;
                    sum = 0.0;
                }
            }

            for (int r = 0; r < rows; r++)
            {
                for (int c = 0; c < cols; c++)
                {
                    ob.matrix[r][c] = temp[r][c];
                    temp[r][c] = 0.0;
                }
            }
        }
    }

    return ob;
}

Matrix &Matrix::operator^=(int pow)
{
    if (this->rows != this->cols)
    {
        throw "Error: non-square matrix provided";
    }
    else if (pow < 0)
    {
        throw "Error: negative power is not supported";
    }
    else if (pow == 0)
    {
        for (int row = 0; row < this->rows; row++)
        {
            for (int col = 0; col < this->cols; col++)
            {
                if (row == col)
                {
                    this->matrix[row][col] = 1;
                }
                else
                {
                    this->matrix[row][col] = 0;
                }
            }
        }
    }
    else
    {
        double **temp = new double *[this->rows];
        for (int i = 0; i < this->rows; i++)
        {
            temp[i] = new double[this->cols];
            for (int j = 0; j < this->cols; j++)
            {
                temp[i][j] = this->matrix[i][j];
            }
        }

        double** temp1 = new double*[this->rows];
        for(int i = 0; i < this->rows; i++){
            temp1[i] = new double[this->cols];
            for(int j = 0; j < this->cols; j++){
                temp1[i][j] = 0.0;
            }
        } 

        double sum = 0.0;
        for (int i = 1; i < pow; i++)
        {

            for (int row = 0; row < this->rows; row++)
            {
                for (int colS = 0; colS < cols; colS++)
                {
                    for (int col = 0; col < cols; col++)
                    {
                        sum += (this->matrix[row][col] * temp[col][colS]);
                    }
                    temp1[row][colS] = sum;
                    sum = 0.0;
                }
            }

            for(int r = 0; r < rows; r++){
                for(int c = 0; c < cols; c++){
                    this->matrix[r][c] = temp1[r][c];
                    temp1[r][c] = 0.0;
                }
            }
        }
    }

    return *this;
}

Matrix Matrix::operator~()
{

    Matrix ob(cols, rows);

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            ob.matrix[j][i] = this->matrix[i][j];
        }
    }

    return ob;
}

Matrix Matrix::operator*(const double &rhs)
{
    Matrix ob(rows, cols);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            ob.matrix[i][j] = rhs * this->matrix[i][j];
        }
    }
    return ob;
}

Matrix &Matrix::operator*=(const double &rhs)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            matrix[i][j] = rhs * matrix[i][j];
        }
    }

    return *this;
}

Matrix operator*(const double &lhs, const Matrix &rhs)
{
    Matrix ob = rhs;
    for (int i = 0; i < ob.rows; i++)
    {
        for (int j = 0; j < ob.cols; j++)
        {
            ob.matrix[i][j] = lhs * ob.matrix[i][j];
        }
    }

    return ob;
}

Matrix Matrix::operator/(const double &rhs)
{
    Matrix ob(rows, cols);
    if (rhs == 0)
    {
        throw "Error: division by zero";
    }
    else
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                ob.matrix[i][j] = this->matrix[i][j] / rhs;
            }
        }
    }

    return ob;
}

Matrix &Matrix::operator|=(Matrix &rhs)
{
    if (this->rows != this->cols)
    {
        throw "Error: non-square matrix provided";
    }
    else if (rhs.cols != 1 || rhs.rows != this->rows)
    {
        throw "Error: incorrect augmentation";
    }
    else
    {
        double m;
        for (int j = 0; j < this->rows; j++) /////////////
        {
            for (int i = j + 1; i < this->rows; i++) /////////////
            {
                double num = this->matrix[j][j];
                if (num == 0)
                {
                    throw "Error: division by zero";
                }
                else
                {
                    m = this->matrix[i][j] / num;
                }

                for (int k = 0; k < this->cols; k++)
                {
                    this->matrix[i][k] = this->matrix[i][k] - m * this->matrix[j][k];
                }
                rhs.matrix[i][0] = rhs.matrix[i][0] - m * rhs.matrix[j][0];
            }
        }
    }

    return *this;
}

Matrix Matrix::operator|(const Matrix &rhs)
{
    Matrix s(this->rows, 1);
    if (this->rows != this->cols)
    {
        throw "Error: non-square matrix provided";
    }
    else if (rhs.cols != 1 || rhs.rows != this->rows)
    {
        throw "Error: incorrect augmentation";
    }
    else
    {
        bool state;

        Matrix tempB = rhs;
        Matrix tempA = *this;
        tempA |= tempB;

        s = tempB;

        for (int i = tempA.rows - 1; i >= 0; i--)
        {
            for (int j = i + 1; j < tempA.rows; j++)
            {
                s.matrix[i][0] = s.matrix[i][0] - tempA.matrix[i][j] * s.matrix[j][0];
            }
            double num = tempA.matrix[i][i];
            if (num == 0)
            {
                throw "Error: division by zero";
            }
            else
            {
                s.matrix[i][0] = s.matrix[i][0] / num;
            }
        }
    }

    return s;
}