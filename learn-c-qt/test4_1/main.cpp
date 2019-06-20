
#include <cmath>
//#include <QTextStream>
#include <stdio.h>
#include <iostream>
#include "sub1.h"
#include "add1.h"

using namespace std;
//using-directive
/*******定义point类*************************/
class Point{
public :
Point(int xx=0,int yy=0){
    x=xx;
    y=yy;
}

Point(Point &p);
int getX(){
    return x;
}
int gety(){
    return y;
}

private:
int x,y;

};


/***Point类的复制函数********************************/
Point::Point(Point &p){
    x=p.x;
    y=p.y;
   cout<<"calling the copy constructor of point"<<endl;
}

/**CLASS类，类的组合*******************************/
class Line{
public:
    Line(Point xp1,Point xp2);
    Line(Line &tt);
    double getLen(){ return len;}
private:
    Point p1,p2;
    double len;
};

/**Line 组合类构造函数**********************************/
Line::Line(Point xp1, Point xp2):p1(xp1),p2(xp2){
    cout<<"calling constructor of Line"<<endl;
    double x = static_cast<double>(p1.getX()-p2.getX());
    double y = static_cast<double>(p1.gety()-p2.gety());
    len = sqrt(x*x+y*y);
}

/**Line 组合类复制构造函数********************************/
Line::Line(Line &tt):p1(tt.p1),p2(tt.p2){
    cout<<"calling the copy constructors of line "<< endl;
    len=tt.len;
}


int main(){

    Point myp1(1,1), myp2(4,5);
    Line line ( myp1, myp2 );
    Line line2(line);
    cout<<"the lenth of the line is:";
    cout<<line.getLen()<<endl;
    cout<<"the length of the line2 is:";
    cout<<line2.getLen()<<endl;
    float x=3.5,y=12.1;
    cout<<add12(x, y)<<endl;
    int a=1,b=2;
    cout<<add12(a,b)<<endl;

    return 0;
}
/*
void fun1(Point P){
    cout<<P.getX()<<endl;
}

Point fun2(){
    Point a(1,2);
    return a;
}
*/
