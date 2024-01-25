#include "vector.h"
using namespace std;

Vector::Vector(unsigned s)
{
    size = s;
    vector = new double[s];
    for (int i = 0; i < s; i++)
    {
        vector[i] = 0;
    }
}

Vector::~Vector()
{
    if (vector != NULL)
    {
        delete[] vector;
        vector = NULL;
    }
}

Vector::Vector(const Vector &rhs)
{
    this->size = rhs.size;
    this->vector = new double[this->size];
    for (int i = 0; i < this->size; i++)
    {
        this->vector[i] = rhs.vector[i];
    }
}

const Vector &Vector::operator=(const Vector &rhs)
{
    if(this == &rhs){
        return *this;
    }
    
    delete[] vector;
    vector = NULL;
    this->size = rhs.size;
    this->vector = new double[this->size];
    for (int i = 0; i < this->size; i++)
    {
        this->vector[i] = rhs.vector[i];
    }

    return *this;
}

void Vector::print()
{
    cout << setprecision(3);
    for (int i = 0; i < size; i++)
    {
        cout << setw(10) << vector[i];
    }
    cout<< endl;
}

void Vector::readFile(istream& inFile){
    for(int i = 0; i < size; i++){
        inFile>> vector[i];
    }
}
void Vector::setVector(const double *v)
{
    for (int i = 0; i < size; i++)
    {
        vector[i] = v[i];
    }
}

double &Vector::operator[](const unsigned int r)
{
    return vector[r];
}

const double &Vector::operator[](const unsigned int r) const
{
    return vector[r];
}

unsigned Vector::getSize() const
{
    return size;
}

Vector Vector::operator*(const double &rhs)
{
    Vector obj(this->size);
    for (int i = 0; i < size; i++)
    {
        obj.vector[i] = this->vector[i] * rhs;
    }
    return obj;
}

Vector &Vector::operator*=(const double &rhs)
{
    for (int i = 0; i < size; i++)
    {
        this->vector[i] = this->vector[i] * rhs;
    }

    return *this;
}

Vector operator*(const double &lhs, const Vector &v)
{
    Vector obj = v;
    for (int i = 0; i < v.size; i++)
    {
        obj.vector[i] = obj.vector[i] * lhs;
    }

    return obj;
}

Vector Vector::operator/(const double &rhs)
{
    Vector obj(this->size);
    if (rhs == 0)
    {
        throw "Error: division by zero";
    }
    else
    {
        for (int i = 0; i < size; i++)
        {
            obj.vector[i] = this->vector[i] / rhs;
        }
    }

    return obj;
}

Vector Vector::operator+(const Vector& rhs){
    Vector obj(this->size);
    if (this->size != rhs.size)
    {
        throw "Error: adding vectors of different dimensionality";
    }else{
        for(int i = 0; i < this->size; i++){
            obj.vector[i] = this->vector[i]+rhs.vector[i];
        }
    }

    return obj;
}

Vector& Vector::operator+=(const Vector& rhs){
    if(this->size != rhs.size){
        throw "Error: adding vectors of different dimensionality";
    }else{
        for(int i = 0; i < this->size; i++){
            this->vector[i] = this->vector[i] + rhs.vector[i];
        }
    }

    return *this;
}

Vector Vector::operator-(const Vector& rhs){
    Vector obj(this->size);

    if(this->size != rhs.size){
        throw "Error: subtracting vectors of different dimensionality";
    }else{
        for(int i = 0; i < this->size; i++){
            obj.vector[i] = this->vector[i] - rhs.vector[i];
        }
    }

    return obj;
}

Vector& Vector::operator-=(const Vector& rhs){
    if(this->size != rhs.size){
        throw "Error: subtracting vectors of different dimensionality";
    }else{
        for(int i = 0; i < this->size; i++){
            this->vector[i] = this->vector[i] - rhs.vector[i];
        }
    }

    return *this;
}

Vector Vector::operator^(int pow){
    Vector obj(this->size);
    if(pow < 0){
        throw "Error: negative power is not supported";
    }else if(pow == 0){
        for(int i = 0; i < this->size; i++){
            obj.vector[i] = 1;
        }
    }else{
        double num;
        for(int i = 0; i < size; i++){
            num = 1;
            for(int j = 1; j <= pow;j++){
                num *= this->vector[i];
            }
            obj.vector[i] = num;
        }
    }

    return obj;
}

Vector& Vector::operator^=(int pow){
    if( pow < 0){
        throw "Error: negative power is not supported";
    }else if(pow == 0){
        for(int i = 0; i < this->size; i++){
            this->vector[i] = 1;
        }
    }else{
        double num;
        for(int i = 0; i < size;i++){
            num = 1;
            for(int j = 1; j <= pow; j++){
            num *= vector[i];
            }
            vector[i] = num;
        }
        
    }

    return *this;
}

Vector Vector::operator~(){
    Vector obj(this->size);
    int count = 0;
    for(int i = size-1; i >= 0;i--){
        obj.vector[count] = this->vector[i];
        count++;
    }

    return obj;
}