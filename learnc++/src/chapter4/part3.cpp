#include <iostream>
#include <cstring>
using namespace std;
// 在此处补充你的代码
class Array2
{
public:
    Array2(int m, int n)
    {
        p= new int*[m];
        for (int i = 0; i < m; i++)
            p[i] = new int[n];
    }
    Array2() :p(NULL){}
    Array2 & operator =(const Array2 &arr)
    {
        if (p == arr.p) return *this;
        if (p != NULL) delete[]p;
        p = arr.p;
        return *this;
    }
    int * & operator [](const int & m)
    {
        return p[m]; //关键在于返回的类型为int *即可
    }
    int & operator ()(const int &m, int const & n)
    {
        return p[m][n];
    }
private:
    int **p;
    };

int main() {
    Array2 a(3,4);
    int i,j;
    for(  i = 0;i < 3; ++i )
        for(  j = 0; j < 4; j ++ )
            a[i][j] = i * 4 + j;
    for(  i = 0;i < 3; ++i ) {
        for(  j = 0; j < 4; j ++ ) {
            cout << a(i,j) << ",";
        }
        cout << endl;
    }
    cout << "next" << endl;
    Array2 b;     b = a;
    for(  i = 0;i < 3; ++i ) {
        for(  j = 0; j < 4; j ++ ) {
            cout << b[i][j] << ",";
        }
        cout << endl;
    }
    return 0;
}
