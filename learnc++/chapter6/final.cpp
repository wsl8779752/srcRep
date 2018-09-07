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
#include <iomanip>
#define TOTAL_WARRIOR_kIND 5
using namespace std;
static in  N,timeHour;
typedef enum warriortype{
    DRAGON =0,
    NINJA,
    ICEMAN,
    LION,
    WOLF,
} WARRIORKIND;  
typedef enum {
    NOFLAG=0,
    READFLAH,
    BLUEFLAG,
}DFLAG;
typedef enum{
    DRAW = 0,
    REDWIN ,
    BLUEWIN,
}DEFFIGHTRESULT;
const string  warrior_string[] = {"dragon","ninja","iceman","lion","wolf"};
const string weaponsName[3] = { "sword","bomb","arrow"};
class headQuators;
class Cwarrior;
class ninja;
class lion;
class dragon;
class wolf;
class iceman;
class CWeapons 
{ 
    public: 
        CWeapons(string name1,Cwarrior  *master1):name(name1),master(master1){
        } 
    private: 
        string name;
        Cwarrior *master;
}; 
class Cwarrior 
{ 
    public: 
        Cwarrior (headQuators *p); 
        virtual ~Cwarrior(){} 
        void *get_addr(){
            return this;
        }
    protected: 
        int hp;
        int num;
        int damage;
        WARRIORKIND type; 
        headQuators *commander;
}; 
class CCity 
{ 
    public: 
        CCity (int n):num(n){} 
        virtual ~CCity (); 
         
    private: 
        int num;
        Cwarrior* newred;
        Cwarrior* newblue;
        DFLAG flag;
        int lifeElement;
        DEFFIGHTRESULT prefight;
        DEFFIGHTRESULT actfight;



}; 
class headQuators 
{ 
    public: 
        headQuators(string name1);
        virtual ~headQuators(){
            for ( int i = 0; i < TOTAL_WARRIOR_kIND; ++i) { 
                for (  int j = 0; j <warriorCount[i] ; ++j) { 
                    delete warriorP[i][j];
                } 
                delete warriorP[i];
            }
        }
        bool haveResourceToProNext;           
        void setLifeElement(int n){
             lifeElement = n ;
        } 
        int getLifeElement(){return lifeElement;}
        void setManufactorSequency();
        virtual int produceWarriors();
        static void  setwarriorConsumption(int *cost); 
        static void  setWarriorDamage(int *damage);
    private: 
        string name;
        friend class Cwarrior;
    protected:   
        int manufactorSequency[TOTAL_WARRIOR_kIND];
        int act;
        int warriorCount[TOTAL_WARRIOR_kIND];
        int dataId;
        Cwarrior **warriorP[TOTAL_WARRIOR_kIND];
        int warriorCountMax[TOTAL_WARRIOR_kIND] ;
        int lifeElement; 
        static int consumption[TOTAL_WARRIOR_kIND];
};
Cwarrior::Cwarrior(headQuators *p):commander(p){
    type = (WARRIORKIND)commander-> manufactorSequency[commander->act];  
    int actIndex = (int) type;
    num = commander->dataId ; 
    hp = commander-> consumption[actIndex];
    cout<<' '<<commander->name <<' '<<warrior_string[actIndex]<<" "<<num<<" "<<"born with strength "<<hp;
    cout<<','<<commander-> warriorCount[actIndex]<<' '<<warrior_string[actIndex]<<" in "<<commander->name <<" headquarter"<<endl;
}
class ninja:public Cwarrior 
{ 
    public: 
          ninja( headQuators *p):Cwarrior(p){ 
              weapon1 = new CWeapons(weaponsName[num%3],this);
              weapon2 = new CWeapons(weaponsName[(num+1)%3],this);
              cout<<"It has a "<<weaponsName[num%3]<<" and a "<<weaponsName[(num+1)%3]<<endl;  
        } 
        virtual ~ninja(){
            delete weapon1;
            delete weapon2;
        } 
    private: 
        CWeapons *weapon1;
        CWeapons *weapon2;
}; 
class dragon:public Cwarrior
{ 
    public: 
        dragon(headQuators *p):Cwarrior(p){
            morale = float(commander->getLifeElement() ) /(float) hp ;
            weapon =  new CWeapons(weaponsName[num%3],this);
            cout<<"It has a "<<weaponsName[num%3]<<",and it's morale is "<<fixed<< setprecision(2)<<morale<<endl;
        } 
        virtual ~dragon(){
            delete weapon;
        }
    private: 
        CWeapons *weapon;
        float morale;
}; 
class iceman:public Cwarrior 
{ 
    public: 
        iceman(headQuators *p):Cwarrior(p){
            weapon =  new CWeapons(weaponsName[num%3],this);
            cout<<"It has a "<<weaponsName[num%3]<<endl;
        } 
        virtual ~iceman(){
            delete weapon;
        } 
         
    private: 
        CWeapons *weapon;
}; 
class lion:public Cwarrior 
{ 
    public: 
        lion(headQuators *p):Cwarrior(p){
            loyalty = commander->getLifeElement()  ; 
            cout<<"It's loyalty is "<<loyalty<<endl;
        } 
    private: 
        int loyalty;
}; 
class wolf:public Cwarrior{
    public:
        wolf(headQuators *p):Cwarrior(p){}
};

 
headQuators ::headQuators(string name1):name(name1){
    haveResourceToProNext = true ;
    act = 0;
    dataId = 0;
    memset(warriorCount,0,sizeof(warriorCount));
    setManufactorSequency();
    for ( int i = 0; i < TOTAL_WARRIOR_kIND; ++i) { 
        warriorCountMax[i] = 10;
        warriorP[i] = new Cwarrior*[10];
    } 
}

int headQuators::consumption[TOTAL_WARRIOR_kIND];
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
    int actIndex;
    for (unsigned int i = 0; i < 6; ++i) { 
        actIndex = manufactorSequency[act] ;      //LINJA LION etc
        tempkind=(WARRIORKIND) actIndex;
        if( lifeElement >= consumption[tempkind])
        {
            dataId += 1;
            warriorCount[actIndex]++;
            lifeElement-= consumption[actIndex];
            if( warriorCount[actIndex] > warriorCountMax[actIndex]){
                warriorCountMax[actIndex] += 10;
                Cwarrior **p =  new Cwarrior *[warriorCountMax[actIndex]];
                memcpy( p,warriorP[actIndex], sizeof(Cwarrior *)*(unsigned long)(warriorCountMax[actIndex]-10));
                delete warriorP[actIndex];
                warriorP[actIndex] = p;
            }
            switch (tempkind){ 
                case NINJA: { 
                                warriorP[actIndex][warriorCount[actIndex]-1] = new ninja(this);                
                            } 
                            break; 
                case DRAGON: { 
                                 warriorP[actIndex][warriorCount[actIndex]-1] = new dragon(this);                
                             } 
                             break; 
                case ICEMAN: { 
                                 warriorP[actIndex][warriorCount[actIndex]-1] = new iceman(this);                
                             } 
                             break; 
                case LION: { 
                               warriorP[actIndex][warriorCount[actIndex]-1] = new lion(this);                
                           } 
                           break; 
                case WOLF: { 
                               warriorP[actIndex][warriorCount[actIndex]-1] = new wolf(this);                
                           } 
                           break; 
            } 
            act = (act+1)%TOTAL_WARRIOR_kIND ;
            return 1;
        }
            act = (act+1)%TOTAL_WARRIOR_kIND ;
    }
    haveResourceToProNext = false ;
    cout<<' '<<name<<" headquarter stops making warriors"<<endl;
    return -1;  
}
void headQuators::setwarriorConsumption(int *cost){
    memcpy(consumption,cost,sizeof(int )*TOTAL_WARRIOR_kIND);
}      
void dealWithInput(unsigned int & dataId, int *& lifeElement,int (*&cost)[TOTAL_WARRIOR_kIND],int (*&inputDamage)[TOTAL_WARRIOR_kIND]){
    cin>>dataId;
    lifeElement =  new int[dataId];
    cost = new int[dataId][TOTAL_WARRIOR_kIND];
    for (unsigned int i = 0; i < dataId; ++i) { 
        cin>>lifeElement[i]; 
        for (unsigned int j = 0; j < TOTAL_WARRIOR_kIND; ++j) { 
            cin>>cost[i][j];
            cin>>inputDamage[i][j];
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
    unsigned int dataNum;
    int *lifeElement,(*cost)[TOTAL_WARRIOR_kIND],(*inputDamage)[TOTAL_WARRIOR_kIND];
    dealWithInput(dataNum,lifeElement,cost,inputDamage);
    for (unsigned int i = 0; i < dataNum; ++i) { 
        headQuators* RedCommand=new headQuators("red");
        headQuators* BlueCommand = new headQuators("blue");
        RedCommand->setLifeElement(lifeElement[i]);
        BlueCommand->setLifeElement(lifeElement[i]);
       headQuators::setwarriorConsumption(cost[i]);
       headQuartors::setWarriorDamage(inputDamage[i]);
        cout<<"Case:"<<i+1<<endl;
        while(RedCommand->haveResourceToProNext == true || BlueCommand->haveResourceToProNext ==true) 
        {
            if(RedCommand->haveResourceToProNext == true ){
                timeHourOutput(0);
                RedCommand->produceWarriors();
            }
            if(BlueCommand->haveResourceToProNext == true){
                timeHourOutput(0);
                BlueCommand->produceWarriors();
            }
            timeHour++ ;
        }    
        delete RedCommand;
        delete BlueCommand;
    }
    delete []cost;
    delete []lifeElement;
    return 0;
}
