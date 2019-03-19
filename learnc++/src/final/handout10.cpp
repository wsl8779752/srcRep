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
