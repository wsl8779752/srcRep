#include "cat.h"
#include <QDebug>
int Cat1::num_of_cat=1;
Cat1::Cat1(int x,int y)
{
    age = x ;
    gender = y;
    num_of_cat++;
    qDebug("new cat duixiang created ,the cat num is:%d",num_of_cat);
}
int Cat1::get_num_of_cat(){
    return num_of_cat;
}


