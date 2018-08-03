/**
 * @file part4.cpp
 * @brief 
 * @author rensheng946@163.com
 * @version 1.0
 * @date 2018-07-13
 */
#include <iostream>
#include <string>
#include <cstdio>
#include <cstring>
#include <sstream>
#include <cstdlib>
#ifndef uint8_t
#define uint8_t unsigned char
#endif /* ifndef uint8_t */
using namespace std;
/**
 * @brief nimamabi
 */
typedef enum warriortype{
    DRAGON =0,
    NINJA,
    ICEMAN,
    LION,
    WOLF,
} WARRIORKIND;  
const string  warrior_string[] = {"dragon","ninja","iceman","lion","wolf"};
class Cwarrior 
{ 
    public: 
        Cwarrior (WARRIORKIND wKind,string name); 
        //virtual ~Cwarrior(){}; 
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
int Cwarrior::consumption[5];
Cwarrior::Cwarrior(WARRIORKIND wKind,string name):type(wKind),commandName(name){
    hp = consumption[type];
}
void Cwarrior::setwarriorConsumption(int *cost){
    memcpy(consumption,cost,sizeof(int )*5);
}      
class headQuators 
{ 
    public: 
        headQuators(string name1);
        bool haveResourceToProNext;           
        void setLifeElement(int n){
             lifeElement = n ;
        } 
        void setManufactorSequency();
        int produceWarriors();
    private: 
        int lifeElement; 
        int  manufactorSequency[5];
        int warriorCount[5];
        string name;
        int act;
        int dataId;
        friend class Cwarrior;
}; 
headQuators ::headQuators(string name1):name(name1){
    haveResourceToProNext = true ;
    act = 0;
    dataId = 0;
    memset(warriorCount,0,sizeof(warriorCount));
    setManufactorSequency();
}
void headQuators::setManufactorSequency(){
    if( name == "red"){
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
    WARRIORKIND tempkind ;
    uint8_t actIndex;
    for (unsigned int i = 0; i < 6; ++i) { 
        actIndex = manufactorSequency[act];
        tempkind=(WARRIORKIND) manufactorSequency[act];
        if(++act == 5) act =0 ;
        if( lifeElement >= Cwarrior::get_consumption(tempkind))
        {
            //p[dataId] = new Cwarrior(tempkind,name);
            cout<<' '<<name<<' '<<warrior_string[actIndex]<<" "<<dataId+1<<" "<<"born with strength "<<Cwarrior::get_consumption(tempkind) ;
            warriorCount[actIndex]++;
            cout<<','<<warriorCount[actIndex]<<' '<<warrior_string[actIndex]<<" in "<<name<<" headquarter"<<endl;
            lifeElement-= Cwarrior::get_consumption(tempkind);
            dataId+=1;
            return 1;
        }
    }
    haveResourceToProNext = false ;
    cout<<' '<<name<<" headquarter stops making warriors"<<endl;
    return -1;  
}
void dealWithInput(unsigned int & dataId, int *& lifeElement,int (*&cost)[5]){
    cin>>dataId;
    lifeElement =  new int[dataId];
    cost = new int[dataId][5];
    for (unsigned int i = 0; i < dataId; ++i) { 
        cin>>lifeElement[i]; 
        for (unsigned int j = 0; j < 5; ++j) { 
            cin>>cost[i][j];
        } 
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
    unsigned int dataId;
    int *lifeElement,(*cost)[5];
    dealWithInput(dataId,lifeElement,cost);
    headQuators RedCommand("red"), BlueCommand("blue");
    for (unsigned int i = 0; i < dataId; ++i) { 
        RedCommand.setLifeElement(lifeElement[i]);
        BlueCommand.setLifeElement(lifeElement[i]);
        Cwarrior::setwarriorConsumption(cost[i]);
        cout<<"Case:"<<i+1<<endl;
        int timeHour=0;
        while(RedCommand.haveResourceToProNext == true || BlueCommand.haveResourceToProNext ==true) 
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
    delete []cost;
    delete []lifeElement;
}
