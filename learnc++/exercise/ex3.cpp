#include <iostream>
using namespace std;
class A { 
    public: 
        virtual ~A (){
            cout<<"A::destrueds"<<endl; 
        }  
    private: 
}; 
class B  :public A
{ 
    public: 
         virtual ~B (){ 
            cout<<"B::destrueds"<<endl; }
    private: 
}; 
class C :public B
{ 
    public: 
         ~C (){ cout<<"C::deseture"<<endl;} 
    private: 
}; 
int main(){
    A *pa = new C;
    delete pa ;A a;
    return 0;
}
