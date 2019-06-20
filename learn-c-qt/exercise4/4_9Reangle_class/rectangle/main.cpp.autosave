#include <stdio.h>
#include <iostream>
#include <cmath>
using namespace std;

class point{

private:
    int x,y;

public:
    point(int a,int b){
        x=a;
        y=b;
    }
    point(point &p1);
    int getx(){ return x ;};
    int gety(){ return y; };
};

point::point(point &p1){
    x=p1.x;
    y=p1.y;
}

class Rectangle{
private:
    point a;
    point b;
public:
   Rectangle(point a,point b);
   int calculate_area();
};
Rectangle::Rectangle(point a,point b):a(a),b(b){

}
int Rectangle::calculate_area(){
   return abs( (a.getx()-b.getx()) * (a.gety()-b.gety()) );

}
int main(){

    int x,y;
    cout<<"please enter x1.x and x1.y"<<endl;
    cin>>x>>y;

    point x1(x,y);
    cout<<"please enter x2.x and x2.y"<<endl;
    cin>>x>>y;
    point x2(x,y);

    Rectangle rec1(x1,x2);

    cout << " the area of rectangle(x1,x2) is: " << rec1.calculate_area() << endl;
    return 0;
}
