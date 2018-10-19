#include <iostream>
using namespace std;
// 在此处补充你的代码
template <class T>
class CArray3D 
{ 
    public: 
        CArray3D (int i,int j,int k):s1(i),s2(j),s3(k){ 
            p = new T**[i];
			for (int i = 0; i < s1; i++)
			{
				p[i] = new T*[j];
				for (int j = 0; j < s2; j++)
				{
					p[i][j] = new T[k];
				}
			}
        }
        virtual ~CArray3D (){ 
			for (int i = 0; i < s1; i++)
			{
				for (int j = 0; j < s2; j++)
				{
                    delete p[i][j];
				}
                delete p[i];
			}
            delete p;
        }  
        T ***p;
        T **operator[](int i){ return p[i] ;}
    private: 
       int s1,s2,s3; 
}; 
int main()
{
    CArray3D<int> a(3,4,5);
    int No = 0;
    for( int i = 0; i < 3; ++ i )
        for( int j = 0; j < 4; ++j )
            for( int k = 0; k < 5; ++k )
                a[i][j][k] = No ++;
    for( int i = 0; i < 3; ++ i )
        for( int j = 0; j < 4; ++j )
            for( int k = 0; k < 5; ++k )
                cout << a[i][j][k] << ",";
    return 0;
}
