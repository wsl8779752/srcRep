#include <iostream> 
#include <iomanip> 
using namespace std;
int main()
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
        cout<<setbase(16)<<temp<<endl;        
    }
    return 0;
}
