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
    ifstream oFile("students.dat",ios::in|ios::binary);
    if(!oFile) {
        cout<<"error"<<endl;
        return 0;
    } 
    while(oFile.read((char *)&s,sizeof(s)))
       cout<<s.name<<" "<<s.age<<endl ;
    oFile.close();
    return 0;
}
