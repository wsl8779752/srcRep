#ifndef COMPLEX_H
#define COMPLEX_H

class Complex
{
private:
    float x,y;
public:
    Complex(float a,float b);
    Complex(float x);
    void add(Complex tt ) ;
    void show() ;
};

#endif // COMPLEX_H
