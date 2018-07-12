#include <iostream>
#include <string>
#include <cstdio>
#include <cstring>
#include <sstream>
#include <cstdlib>
using namespace std;
typedef enum warriortype{
    DRAGON =0,
    NINJA,
    ICEMAN,
    LION,
    WOLF,
} WARRIORKIND;  
const string  warrior_string[] = {"dragon","ninja","iceman","lion","wolf"};
class warrior 
{ 
    public: 
        warrior (WARRIORKIND wKind,string name); 
        virtual ~warrior (){}; 
        static void  setwarriorConsumption(int *cost); 
        static int get_consumption(WARRIORKIND type){
            return consumption[type];
        }
    private: 
        int hp;
        int number;
        int damage;
        WARRIORKIND type; 
        string commandName;
        static int consumption[5];
}; 
warrior::warrior(WARRIORKIND wKind,string name):type(wKind),commandName(name){
    hp = consumption[type];
}
/*warrior::~warrior(){*/
    //;
/*}*/
void warrior::setwarriorConsumption(int *cost){
    memcpy(consumption,cost,sizeof(int )*5);
}      
class headQuators 
{ 
    public: 
        headQuators(string name1);
        virtual ~headQuators (); 
        void setLifeElement(int n){
             lifeElement = n ;
        } 
        void setManufactorSequency();
        //bool stopManufactor();   //停止的话，return true
        int produceWarriors();
        bool haveResourceToProNext;           
    private: 
        static int lifeElement; 
        int  manufactorSequency[5];
        int warriorCount[5];
        string name;
        int act;
        int dataId;
        friend class warrior;
        /*static redCommandId;*/
        /*static buleCommandId;*/
        warrior *p[];
}; 
headQuators ::headQuators(string name1):name(name1){
    setManufactorSequency();
    haveResourceToProNext = true ;
    act = 0;
    dataId = 0;
    memset(warriorCount,0,sizeof(warriorCount));
}
headQuators::~headQuators(){
    for (unsigned int i = 0; i < dataId; ++i) { 
        delete p[i];
    } 
}
/*bool headQuators:: stopManufactor(){*/
//if( lifeElement <warrior::getMinCost()) return true;
//else return false;
/*}*/
void headQuators::setManufactorSequency(){
if( name == "red "){
    manufactorSequency[0] = ICEMAN; 
    manufactorSequency[1] = LION ;
    manufactorSequency[2] = WOLF ;
    manufactorSequency[3] = NINJA;
    manufactorSequency[4] = DRAGON;
}
else { 
    manufactorSequency[0] = LION; 
    manufactorSequency[1] = DRAGON ;
    manufactorSequency[2] = NINJA ;
    manufactorSequency[3] = ICEMAN;
    manufactorSequency[4] = WOLF;
} 
}

int headQuators:: produceWarriors(){
    for (unsigned int i = 0; i < 5; ++i) { 
        WARRIORKIND tempkind =(WARRIORKIND) manufactorSequency[act];
        if( lifeElement >= warrior::get_consumption(tempkind))
        {
            p[dataId] = new warrior(tempkind,name);
            cout<<"red "<<warrior_string[manufactorSequency[act]]<<" "<<dataId<<" "<<"born with strength "<<warrior::get_consumption(tempkind) ;
            warriorCount[manufactorSequency[act]]++;
            cout<<' '<<warriorCount[manufactorSequency[act]]<<' '<<warrior_string[manufactorSequency[act]]<<" in "<<name<<" headquator"<<endl;
            if(++act == 5) act =0 ;
            return 1;
        }
    }
    haveResourceToProNext = false ;
    cout<<name<<" headquarter stops making warriors";
    return -1;  
}
void dealWithInput(int& dataId, int& lifeElement,int (&cost)[5]){
cin>>dataId>>lifeElement; 
    for (unsigned int i = 0; i < 5; ++i) { 
        cin>>cost[i];
    } 
}
void timeHourOutput(int &timeHour){
    if(timeHour <=9){
        cout<<"00"<<timeHour;
    }
    else if ( timeHour <= 99) { 
        cout<<'0'<<timeHour; 
    } 
    else { 
        cout<<timeHour; 
    } 
}
int main(){
    int dataId,lifeElement,cost[5];
    dealWithInput(dataId,lifeElement,cost);
    headQuators RedCommand("red"), BlueCommand("blue");
    RedCommand.setLifeElement(lifeElement);
    BlueCommand.setLifeElement(lifeElement);
    warrior::setwarriorConsumption(cost);
    cout<<"Case:"<<dataId<<endl;
    int timeHour=0;
    while(1) 
    {
        if(RedCommand.haveResourceToProNext == true ){
            timeHourOutput(timeHour);
            RedCommand.produceWarriors();
        }
        if(BlueCommand.haveResourceToProNext == true){
            timeHourOutput(timeHour);
            BlueCommand.produceWarriors();
        }
        timeHour++ ;
    }    
}
