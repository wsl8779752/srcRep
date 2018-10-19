#include <map> 
#include <iostream> 
#include <string> 
using namespace std;
class CPlayer 
{ 
    public: 
        CPlayer(); 
        virtual ~CPlayer (); 
        unsigned int power;
        int id;
}; 
typedef multimap<unsigned int,int> dmmp;
int main()
{
    int n;
    dmmp facer;
    facer.insert(dmmp::value_type(1000000000,1));
    CPlayer newPlayer;
    cin>>n;
    dmmp::iterator i,lower,upper;
    while(n--){
        cin>>newPlayer.id>>newPlayer.power;
        i = facer.insert(make_pair(newPlayer.power,newPlayer.id)); 
        lower = i-1;
        upper = i+1;
        int temp = ;
    }
    return 0;
}
