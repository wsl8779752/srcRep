#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
// 在此处补充你的代码
class CMy_add 
{ 
    public: 
        CMy_add(int &n):k(n){} 
        void operator()(int n){ k+= 0x07&n;}
    private:
        int  &k;
}; 
int main(int argc, char* argv[]) {
        int v, my_sum=0;
        vector<int> vec;
        cin>>v;
        while ( v ) {
                vec.push_back(v);
                cin>>v;
        }
        for_each(vec.begin(), vec.end(), CMy_add(my_sum));
        cout<<my_sum<<endl;
        return 0;
}
