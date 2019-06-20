#include "complex.h"
#include <QDebug>

Complex::Complex(float a,float b)
{
    x = a ;
    y = b ;

}

Complex::Complex(float a){

    x=a;
}

void Complex::add(Complex tt){
    x += tt.x;
    y += tt.y;
}

void Complex::show(){
    qDebug("the resuld is %2.1f+%4.0fi.",x,y);
}
