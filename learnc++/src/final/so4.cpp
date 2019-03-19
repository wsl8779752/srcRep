#include <iostream>
using namespace std;
// 在此处补充你的代码
class CType 
{ 
    public: 
        void setvalue(int n){ k = n;} 
        int operator++(int){ int ans = k ; k*=k; return ans;  }
        int k;
}; 

ostream&  operator<<(ostream &o,CType& n){ 
    o<<n.k;
    return o;
}
int main(int argc, char* argv[]) {
        CType obj;
        int n;
        cin>>n;
        while ( n ) {
                obj.setvalue(n);
                cout<<obj++<<" "<<obj<<endl;
                cin>>n;
        }
        return 0;
}
