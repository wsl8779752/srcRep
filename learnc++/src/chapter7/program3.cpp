#include <iostream>
#include <fstream>
#include <cstring> 
using namespace std;
class CStudent 
{ 
    public:
       char name[20];
       int age; 
}; 
int main(){
    CStudent s;
    memset(s.name,0,1);
    ifstream iFile("students.dat",ios::out|ios::binary);
    if(!iFile){
        cout<<"error"<<endl;
        return 0;
    }
    int  L=0,R;
    iFile.seekg(0,ios::end);
    R = iFile.tellg()/sizeof(s)-1;
    int middle = (L + R)/2;
    int i;
    while( (i = strcmp(s.name),"Jack") !=0){
        iFile.seekg(middle*sizeof(s));
        iFile.read((char *s)&s,sizeof(s));
        if( i > 0 ) {
            R = middle;
        }
        if( i< 0) L = middle;
        middle =( L+R)/2;
    }


    return 0;
}
