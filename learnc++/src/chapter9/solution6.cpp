#include <map> 
#include <iostream> 
#include <string> 
using namespace std;
class CPlayer 
{ 
    public: 
        CPlayer() {}
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
    dmmp::iterator i,enemy,upper;
    while(n--){
        cin>>newPlayer.id>>newPlayer.power;
        i = facer.insert(make_pair(newPlayer.power,newPlayer.id)); 
        enemy =--i;
        upper =(++++i);
        i--;
        unsigned int temp = (*i).first - (*enemy).first; 
        if( (*upper).first -(*i).first < temp )
        {  
            enemy = upper;
        }
        cout<<(*i).second<<" "<<(*enemy).second<<endl;
    }
    return 0;
}
