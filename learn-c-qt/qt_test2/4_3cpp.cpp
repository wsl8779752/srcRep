#include <QTextStream>

 #include <stdio.h>

QTextStream cin(stdin,  QIODevice::ReadOnly);

QTextStream cout(stdout,  QIODevice::WriteOnly);

QTextStream cerr(stderr,  QIODevice::WriteOnly);

#include <cmath>
const float FENCE_PRICE=35;
const float CONCRETE_PRICE=20;

class Circle{
public:
    Circle(float r);
    float circumference(void);
    float area(void);
private:
    float radius;

};

Circle::Circle(float r)
{
    radius=r;
}

float Circle::circumference(void){

    return 2*M_PI*radius;
}

float Circle::area(void){

    return M_PI*radius*radius;
}

int main(){
    float radius;
    cout<<"enter the radius of the pool:" ;// 提示用户输入半径
    cout.flush();
    cin>>radius  ;
    radius=10;
    Circle pool(radius);
    Circle poolRim(radius+3);

    float fencecost = pool.circumference()*FENCE_PRICE;
    cout<<fencecost<<endl;

    float concreteconst =( poolRim.area()-pool.area() )*CONCRETE_PRICE;
    cout <<concreteconst<<endl ;
    cout.flush();
    return 0;
}


