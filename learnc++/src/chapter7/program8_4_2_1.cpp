#include <iostream>
#include <fstream>
using namespace std;
class CStudent 
{ 
    public:
       char name[20];
       int age; 
}; 
int main(){
    CStudent s;
    ofstream oFile("students.dat",ios::trunc|ios::out|ios::binary);
    while(cin>>s.name>>s.age)
        oFile.write((char *)&s,sizeof(s));
    oFile.close();
    return 0;
}
