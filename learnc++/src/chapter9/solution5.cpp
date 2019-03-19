#include <map> 
#include <iostream> 
#include <string> 
#include <cstdio> 
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
    //freopen("data.out","w",stdout);
    dmmp facer;
    facer.insert(dmmp::value_type(1000000000,1));
    CPlayer newPlayer;
    cin>>n;
    dmmp::iterator i,enemy,upper;
    while(n--){
        cin>>newPlayer.id>>newPlayer.power;
        //i 是双向迭代器，所以++ --操作，不支持+1 -1操作
        i = facer.insert(make_pair(newPlayer.power,newPlayer.id)); 
        if( i == facer.begin())   //如果插入key是最小的
        {   
            enemy = ++i;
            i--;
        }    
        else if( i == --facer.end()){ //如果插入key是最大的
            enemy = --i;
            i++;
        }
        else {       //既不是最大，也不是最小
            enemy =--i;
            upper =(++++i);
            i--;
            unsigned int temp = (*i).first - (*enemy).first; 
            if( (*upper).first -(*i).first < temp )
            {  
                enemy = upper;
            }
        }
        cout<<(*i).second<<" "<<(*enemy).second<<endl;
    }
    //fclose(stdout);
    return 0;
}
