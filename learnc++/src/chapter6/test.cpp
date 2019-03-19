#include <iostream>
#include "test.h" 
AAb::AAb()
{
}

AAb::~AAb()
{
}

#include <cstdlib> 
using namespace std;

class AAA 
{ 
    public: 
        static int getnimabi(){return nimabi;}     
        
    private: 
        static int nimabi;
}; 
int AAA::nimabi = 111110;
void print111()
{
    cout<<AAA::getnimabi()<<endl;
}
class Based{
    public:
        virtual ~Based(){}
        void virtual print(){cout<<"Based out"<<endl;}
};
class Derived:public Based{
    public:
    virtual ~Derived(){}
         void print(){
             Based::print();
             cout<<"Derived has vitrual out"<<endl;}

};
class NoVitualD : public Based{

};
int main(){
   /* int a[5];*/
    //cout<<sizeof(a)<<endl;
    //cout<<"size of int is: "<<sizeof(int);
        ////AAA kk;
    /*//print111();*/
    Based A;
    Derived B;
    NoVitualD C;
    Based *p;
    p = &A;
    p->print();
    p = &B;
    p->print();
    p = &C;
    p->print();
}
