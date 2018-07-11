#include <iostream> 
using namespace std;
class Location  
{ 
    private: 
        int x,y;
    public: 
        void init(int x=0 ,int y=0);
        void valueX(int val=0){x=val;}
        int valueX(){return x;}   
}; 
void Location::init(int X,int Y){
    x = X;
    y = Y;
} 
int  main(int argc, char *argv[])
{
    Location A;
    A.init(5);
    cout<<A.valueX();
    
        
    return 0;
}
