#include "date_type.h"
#include <stdio.h>
#include <iostream>
using namespace std;
date_type::date_type()
{
    cout<<"date_type constructed"<<endl;
}

void date_type::input(){
    cout<<"please intput  alpha"<<endl;
    cin >> a>>b;
    cout<<"please input int"<<endl;
    cin>>x>>y;
    cout<<"please input float"<<endl;
    cin>>xx>>yy;
}
void date_type::show(char aa, char bb){
    aa=a;
    bb=b;
    cout<<"show char is:"<<aa<<bb<<endl;

}
void date_type::show(float xx1, float yy1){
    xx1=xx;
    yy1=yy;
    cout<<"show float is:"<<xx1<<yy1;
}
void date_type::show(int xx1, int yy1){
    xx1=x;
    yy1=y;
     cout<<"show int is:"<<xx1<<yy1;
}
