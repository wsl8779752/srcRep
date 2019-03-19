#include <iostream>
#include <map>
using namespace std;
// 在此处补充你的代码
class A 
{ 
    public: 
        A (int n=0){ count++;} 
        virtual ~A (){ 
            cout<<"A::destructor"<<endl; 
        }  
        A( A& n){ count++;}
        static int count; 
    private: 
}; 
class B     :public A
{ 
    public: 
        B(int n):A(n){} 
        B(B &n):A(n){}
        virtual ~B (){
            count--;
            cout<<"B::destructor"<<endl;
        } 
    private: 
}; 
int A::count = 0;
void func(B b) { }
int main()
{
        A a1(5),a2;
        cout << A::count << endl;
        B b1(4);
        cout << A::count << endl;
        func(b1);
        cout << A::count << endl;
        A * pa = new B(4);
        cout << A::count << endl;
        delete pa;
        cout << A::count << endl;
        return 0;
}
