#include "cat.h"
#include <QDebug>

//int Cat1::num_of_cat=0;
extern int n;
extern void fn1();
int main(){

    qDebug("the num of cat is:%d",Cat1::get_num_of_cat());
    Cat1 mycat(10,2);
    qDebug("the num of cat is:%d",Cat1::get_num_of_cat());
    //n=3;
    qDebug( "%d" , n);
    for(int i=0;i<10;i++)
    fn1();
    qDebug( "%d" , n);
    return 0;
}

