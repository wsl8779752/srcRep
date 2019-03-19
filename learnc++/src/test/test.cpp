#include <iostream> 
#include <iostream> 
using namespace std;
class BasedC 
{ 
    public: 
        virtual ~BasedC (){} 
         void print(){cout<<"Basedc print";}         
    private: 
        int kk;
}; 
class B1:public BasedC 
{ 
    public: 
        virtual void print(){ cout<<"B1 out"<<endl;}  
    private: 
}; 
class B2:public BasedC 
{ 
    public: 
        void print2(){cout<<"B2 print2"<<endl;}
    private: 
        int i;
}; 
int main(){
    B1 b1;
    B2 b2;
    b1.print();
    b2.print();
}
