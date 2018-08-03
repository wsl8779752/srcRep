#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;
// 在此处补充你的代码
class MyString:public string 
{ 
    public: 
        MyString(); 
        MyString(MyString &s);
        MyString(const string s);
        MyString(const char *s);
        MyString& operator=(MyString &n1);
        MyString& operator=(string s);
        MyString& operator+(MyString &n1);
        bool operator<(MyString &n1);
        bool operator==(MyString &n1);
        bool operator>(MyString &n1);
        MyString operator()(int i, int j);
        friend ostream& operator<<(ostream &os,const MyString &n1);
        virtual ~MyString (); 
    private: 
        string strData;
}; 
MyString::MyString(){strData = "";}
MyString::MyString(MyString &s):strData(s){
}
MyString::MyString(string s){
   strData = s ;
}
MyString::MyString(const char *s):strData(s){ 
} 

MyString& MyString::operator=(MyString &n1){ 
    strData =  n1.strData ; 
    return *this;
} 
MyString& MyString::operator=(string s){
    strData = s ;
    return *this;
}
MyString& MyString::operator+(MyString &n1){ 
    strData += n1.strData;
    return *this;
} 
bool MyString::operator<(MyString &n1){ 
    return strData<n1.strData; 
} 
bool MyString::operator==(MyString &n1){
   return strData==n1.strData;
}
bool MyString::operator>(MyString &n1){ 
    return strData>n1.strData; 
} 
MyString MyString::operator()(int i, int j){ 
     string s = strData.substr(i,j);
     return MyString(s);    
} 
MyString::~MyString(){
}
ostream& operator<<(ostream& os,const MyString &n1){
    os<<n1.strData;
    return os;
}
int CompareString( const void * e1, const void * e2) {
    MyString * s1 = (MyString * ) e1;
    MyString * s2 = (MyString * ) e2;
    if( *s1 < *s2 )     return -1;
    else if( *s1 == *s2 ) return 0;
    else  return 1;
}
int main(){
    MyString s1("abcd-"),s2,s3("efgh-"),s4(s1);
    MyString SArray[4] = {"big","me","about","take"};
    cout << "1. " << s1 << s2 << s3<< s4<< endl;
    s4 = s3;    s3 = s1 + s3;
    cout << "2. " << s1 << endl;
    cout << "3. " << s2 << endl;
    cout << "4. " << s3 << endl;
    cout << "5. " << s4 << endl;
    cout << "6. " << s1[2] << endl;
    s2 = s1;    s1 = "ijkl-";
    s1[2] = 'A' ;
    cout << "7. " << s2 << endl;
    cout << "8. " << s1 << endl;
    s1 += "mnop";
    cout << "9. " << s1 << endl;
    s4 = "qrst-" + s2;
    cout << "10. " << s4 << endl;
    s1 = s2 + s4 + " uvw " + "xyz";
    cout << "11. " << s1 << endl;
    qsort(SArray,4,sizeof(MyString), CompareString);
    for( int i = 0;i < 4;++i )
        cout << SArray[i] << endl;
    //输出s1从下标0开始长度为4的子串
    cout << s1(0,4) << endl;
    //输出s1从下标为5开始长度为10的子串
    cout << s1(5,10) << endl;
    return 0;
}
