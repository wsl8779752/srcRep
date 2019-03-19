#include <iostream>
#include <set>
#include <iterator>
#include <algorithm>
using namespace std;
// 在此处补充你的代码
class A 
{ 
    public: 
        A(int n){ 
            name ='A';
            age = n;
        }
        bool operator<( A& n){
            return  age < n.age;
        }
        char name;
        int age;
        friend ostream &operator<<(ostream &n, A *b){
            n<<(b->name)<<" "<<(b->age)<<endl;
            return n;  
        }
}; 
class B :public A 
{ 
    public: 
        B(int n):A(n){name = 'B';} 
}; 

struct Comp{
    bool operator()(const A* a1, const A* a2){
        return (*a1).age < (*a2).age;
    }
};
void Print( A* it){
    cout<<it;
}
int main()
{
        int t;
        cin >> t;
        set<A*,Comp> ct;
        while( t -- ) {
                int n;
                cin >> n;
                ct.clear();
                for( int i = 0;i < n; ++i)	{
                        char c; int k;
                        cin >> c >> k;

                        if( c == 'A')
                                ct.insert(new A(k));
                        else
                                ct.insert(new B(k));
                }
                for_each(ct.begin(),ct.end(),Print);
                cout << "****" << endl;
        }
}
