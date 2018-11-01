#include <iostream> 
using namespace std;
int main(int argc, char *argv[])
{
    unsigned int t,n,i,j;
    cin>>t;
    while(t--){
        cin>>n>>i>>j;
        unsigned int temp = (0xffffffff<<(i+1))&(0xffffffff>>(32-j));;
        unsigned int temp2 =(((~n)>>j)&1)<<j;
        temp|= temp2;
        temp2 =( (n>>i)&1)<<i;
        temp|= temp2;
        cout<<temp<<endl;        
    }
    return 0;
}
