#include <iostream>

#include <cstdlib> 
using namespace std;
class AAA 
{ 
    public: 
        static int getnimabi(){return nimabi;}     
        
    private: 
        static int nimabi;
}; 
int AAA::nimabi = 111110;
void print111()
{
    cout<<AAA::getnimabi()<<endl;
}
int main(){

        AAA kk;
    print111();

}
