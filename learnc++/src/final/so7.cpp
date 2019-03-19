#include <iostream>
#include <string>
#include <list>
using namespace std;

class A{
private:
        string name;
public:
        A(string n) :name(n){}
        friend bool operator < (const class A& a1, const class A &a2);
        friend bool operator == (const class A &a1, const class A &a2){
                if (a1.name.size() == a2.name.size())
                        return true;
                else
                        return false;
        }
        friend ostream & operator << (ostream &o, const A &a){
                o << a.name;
                return o;
        }
        string get_name() const{
                return name;
        }
        int get_size() const{
                return name.size();
        }
};
// 在此处补充你的代码
bool operator < (const class A& a1, const class A &a2){
    return a1.get_size() < a2.get_size();
}
template<class T>
struct MyLarge:public binary_function<T,T,bool>{
    bool operator()(const class A& a1, const class A &a2){
        const char *ca1 = new char[a1.get_size()];
        const char *ca2 = new char[a2.get_size()];
        ca1 = a1.get_name().c_str();
        ca2 = a2.get_name().c_str();
        return *ca1 < *ca2;
    }
};
template<class T,class Pred>
void Show(T first, T second, Pred opred){
    for(; first!= second ;++first)
        opred( first);
};
struct Print {
    public:
        Print(){}
        void operator()(list<A>::iterator it){
            cout << *it<<" ";
  }
};

int main(int argc, char* argv[])
{
        list<A> lst;
        int ncase, n, i = 1;
        string s;
        cin >> ncase;
        while (ncase--){
                cout << "Case: "<<i++ << endl;
                cin >> n;
                for (int j = 0; j < n; j++){
                         cin >> s;
                         lst.push_back(A(s));
                }
                lst.sort();
                Show(lst.begin(), lst.end(), Print());
                cout << endl;
                lst.sort(MyLarge<A>());
                Show(lst.begin(), lst.end(), Print());
                cout << endl;
                lst.clear();
        }
        return 0;
}
