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
static int  timeHour;
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
class CWarrior;
class ninja;
class lion;
class dragon;
class wolf;
class iceman;
class CWeapon 
{ 
    public: 
        CWeapon(string name1,CWarrior  *master1):name(name1),master(master1){
        } 
    private: 
        string name;
        CWarrior *master;
}; 
class CWarrior 
{ 
    public: 
        CWarrior (headQuators *p); 
        virtual ~CWarrior(){} 
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
        CWarrior* newred;
        CWarrior* newblue;
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
        friend class CWarrior;
    protected:   
        int manufactorSequency[TOTAL_WARRIOR_kIND];
        int act;
        int warriorCount[TOTAL_WARRIOR_kIND];
        int dataId;
        CWarrior **warriorP[TOTAL_WARRIOR_kIND];
        int warriorCountMax[TOTAL_WARRIOR_kIND] ;
        int lifeElement; 
        static int consumption[TOTAL_WARRIOR_kIND];
};
CWarrior::CWarrior(headQuators *p):commander(p){
    type = (WARRIORKIND)commander-> manufactorSequency[commander->act];  
    int actIndex = (int) type;
    num = commander->dataId ; 
    hp = commander-> consumption[actIndex];
    cout<<' '<<commander->name <<' '<<warrior_string[actIndex]<<" "<<num<<" "<<"born with strength "<<hp;
    cout<<','<<commander-> warriorCount[actIndex]<<' '<<warrior_string[actIndex]<<" in "<<commander->name <<" headquarter"<<endl;
}
class ninja:public CWarrior 
{ 
    public: 
          ninja( headQuators *p):CWarrior(p){ 
              weapon1 = new CWeapon(weaponsName[num%3],this);
              weapon2 = new CWeapon(weaponsName[(num+1)%3],this);
              cout<<"It has a "<<weaponsName[num%3]<<" and a "<<weaponsName[(num+1)%3]<<endl;  
        } 
        virtual ~ninja(){
            delete weapon1;
            delete weapon2;
        } 
    private: 
        CWeapon *weapon1;
        CWeapon *weapon2;
}; 
class dragon:public CWarrior
{ 
    public: 
        dragon(headQuators *p):CWarrior(p){
            morale = float(commander->getLifeElement() ) /(float) hp ;
            weapon =  new CWeapon(weaponsName[num%3],this);
            cout<<"It has a "<<weaponsName[num%3]<<",and it's morale is "<<fixed<< setprecision(2)<<morale<<endl;
        } 
        virtual ~dragon(){
            delete weapon;
        }
    private: 
        CWeapon *weapon;
        float morale;
}; 
class iceman:public CWarrior 
{ 
    public: 
        iceman(headQuators *p):CWarrior(p){
            weapon =  new CWeapon(weaponsName[num%3],this);
            cout<<"It has a "<<weaponsName[num%3]<<endl;
        } 
        virtual ~iceman(){
            delete weapon;
        } 
         
    private: 
        CWeapon *weapon;
}; 
class lion:public CWarrior 
{ 
    public: 
        lion(headQuators *p):CWarrior(p){
            loyalty = commander->getLifeElement()  ; 
            cout<<"It's loyalty is "<<loyalty<<endl;
        } 
    private: 
        int loyalty;
}; 
class wolf:public CWarrior{
    public:
        wolf(headQuators *p):CWarrior(p){}
};

 
headQuators ::headQuators(string name1):name(name1){
    haveResourceToProNext = true ;
    act = 0;
    dataId = 0;
    memset(warriorCount,0,sizeof(warriorCount));
    setManufactorSequency();
    for ( int i = 0; i < TOTAL_WARRIOR_kIND; ++i) { 
        warriorCountMax[i] = 10;
        warriorP[i] = new CWarrior*[10];
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
                CWarrior **p =  new CWarrior *[warriorCountMax[actIndex]];
                memcpy( p,warriorP[actIndex], sizeof(CWarrior *)*(unsigned long)(warriorCountMax[actIndex]-10));
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
void dealWithInput(int& M,int& N,int& K,int& R,int& T,int (&cost)[TOTAL_WARRIOR_KIND],int (&inputDamage)[TOTAL_WARRIOR_KIND]){
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

class Ctime 
{ 
    public: 
        Ctime (); 
        virtual ~Ctime (); 
        static void timeincrease(){time++;}
        static void resettime(){time = 0;}
        void timeout(); 
        int getseond(int psecond){ second = psecond; return time*60 + second;}
    private: 
        static int time;
        int second ;
}; 
void Ctime::timeout(){
    printf("%03d",time);
    printf("%02d",second);
}
int Ctime::time = 0;
int main(){
    unsigned int dataNum;  //数据测试组数
    int M,N,K,R,T,cost[TOTAL_WARRIOR_kIND],inputDamage[TOTAL_WARRIOR_kIND]; //输入的生命元，城市数目等参数
    cin>>dataNum;
    for(unsigned int actcase = 0; actcase< dataNum; actcase++){
        dealwithinput(M,N,K,R,T,cost,inputDamage);

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
