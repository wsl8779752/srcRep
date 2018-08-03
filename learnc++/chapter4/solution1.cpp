#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;
class Complex{
    private:
        double r,i;
    public:
        void Print() {
            cout << r << "+" << i << "i" << endl;
        }
        Complex & operator = ( const char *s){
            string str = s;
            int pos = str.find("+", 0);
            string strReal = str.substr(0, pos);//分离出代表实部的字符串
            r = atof(strReal.c_str());//atof库函数能将const char*指针指向的内容转换成float
            string strImaginary = str.substr(pos + 1, str.length() - pos - 2);//分离出虚部代表的字符串
            i = atof(strImaginary.c_str());
            return *this;
        }
};
int main(){
    Complex a;
    a = "3+4i"; a.Print();
    a = "5+6i"; a.Print();
    return 0;
}
