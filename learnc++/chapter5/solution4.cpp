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
using namespace std;
typedef enum warriortype{
    DRAGON =0,
    NINJA,
    ICEMAN,
    LION,
    WOLF,
} WARRIORKIND;  
class headQuators;
const string  warrior_string[] = {"dragon","ninja","iceman","lion","wolf"};
class Cwarrior 
{ 
    public: 
        Cwarrior (WARRIORKIND wKind,headQuators *name); 
        virtual ~Cwarrior(){} 
        static void  setwarriorConsumption(int *cost); 
        static int get_consumption(WARRIORKIND type){
            return consumption[type];
        }
        void *get_addr(){
            return this;
        }
    private: 
        int hp;
        int number;
        int damage;
        WARRIORKIND type; 
        headQuators *headQuatorsName;
        static int consumption[5];
}; 
int Cwarrior::consumption[5];
Cwarrior::Cwarrior(WARRIORKIND wKind,headQuators *name):type(wKind),headQuatorsName(name){
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
        string name;
        friend class Cwarrior;
    protected:   
        int  manufactorSequency[5];
        int act;
        int warriorCount[5];
        int dataId;
        int lifeElement; 
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
    int actIndex;
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
const string weaponsName[3] = { "sword","bomb","arrow"};
class CWeapons 
{ 
    public: 
        CWeapons(string name1,Cwarrior  *master1):name(name1),master(master1){
        } 
    private: 
        string name;
        Cwarrior *master;
}; 
class ninja:public Cwarrior 
{ 
    public: 
          ninja(WARRIORKIND kind,headQuators *name,int n):Cwarrior(kind,name),num(n){ 
              weapon1 = new CWeapons(weaponsName[num%3],this);
              weapon2 = new CWeapons(weaponsName[(num+1)%3],this);
              cout<<"It has a "<<weaponsName[num%3]<<" and a "<<weaponsName[(num+1)%3]<<endl;  
        } 
        virtual ~ninja(){
            delete weapon1;
            delete weapon2;
        } 
    private: 
        int num;
        CWeapons *weapon1;
        CWeapons *weapon2;
}; 
class dragon:public Cwarrior
{ 
    public: 
        dragon(WARRIORKIND kind,headQuators *name,int n,float m):Cwarrior(kind,name),num(n),morale(m){
            weapon =  new CWeapons(weaponsName[num%3],this);
            cout<<"It has a "<<weaponsName[num%3]<<",and it's morale is "<<fixed<< setprecision(2)<<morale<<endl;
        } 
        virtual ~dragon(){
            delete weapon;
        }
    private: 
        CWeapons *weapon;
        int num;
        float morale;
}; 
class iceman:public Cwarrior 
{ 
    public: 
        iceman(WARRIORKIND kind,headQuators *name,int n):Cwarrior(kind,name),num(n){
            weapon =  new CWeapons(weaponsName[num%3],this);
            cout<<"It has a "<<weaponsName[num%3]<<endl;
        } 
        virtual ~iceman(){
            delete weapon;
        } 
         
    private: 
        CWeapons *weapon;
        int num;
}; 
class lion:public Cwarrior 
{ 
    public: 
        lion(WARRIORKIND kind,headQuators *name,int n,int m):Cwarrior(kind,name),num(n),loyalty(m){
            cout<<"It's loyalty is "<<loyalty<<endl;
        } 
    private: 
        int num;
        int loyalty;
}; 
class wolf:public Cwarrior{
    public:
        wolf(WARRIORKIND kind,headQuators *name,int n):Cwarrior(kind,name),num(n){}
    private:
        int num;
};
class CNewHeadQuator:public headQuators 
{ 
    public: 
         CNewHeadQuator(string name1):headQuators(name1){
             for ( int i = 0; i < 5; ++i) { 
                warriorCountMax[i] = 10;
             } 
             ninjaIndex = new ninja*[10];
             dragonIndex = new dragon*[10];
             icemanIndex = new iceman*[10];
             lionIndex = new lion*[10];
             wolfIndex = new wolf*[10];        
         } 
        virtual ~CNewHeadQuator (){
            int j;
            for (  j = 0; j < warriorCount[NINJA]; ++j) { 
                delete ninjaIndex[j];
            } 
            for (  j = 0; j < warriorCount[DRAGON]; ++j) { 
                delete dragonIndex[j];
            } 
            for (  j = 0; j < warriorCount[ICEMAN]; ++j) { 
                delete icemanIndex[j];
            } 
            for (  j = 0; j < warriorCount[LION]; ++j) { 
                delete lionIndex[j];
            } 
            for (  j = 0; j < warriorCount[WOLF]; ++j) { 
                delete wolfIndex[j];
            } 
            delete dragonIndex;
            delete ninjaIndex;
            delete icemanIndex;
            delete lionIndex;
            delete wolfIndex;
        } 
        void produceWarriors(){
            headQuators::produceWarriors();
            if(haveResourceToProNext == true){
                int temp = act-1;
                if (temp == -1)  temp = 4; 
                int actindex = manufactorSequency[temp]; //actindex is NINJA,DRAGON etc
                WARRIORKIND tempkind=(WARRIORKIND) manufactorSequency[temp];
                int count = warriorCount[actindex]-1;
                switch (tempkind) { 
                    case NINJA: { 
                       if( count >= warriorCountMax[actindex]) {
                         warriorCountMax[actindex] += 10;       
                         ninja **p = new ninja*[warriorCountMax[actindex]];
                         memcpy( p,ninjaIndex, sizeof(ninja *)*(warriorCountMax[actindex]-10));
                         delete ninjaIndex;
                         ninjaIndex = p;
                       }             
                       ninjaIndex[count] = new ninja(tempkind,this,dataId) ;            
                    } 
                    break; 
                    case DRAGON: { 
                       if( count >= warriorCountMax[actindex]) {
                         warriorCountMax[actindex] += 10;       
                         dragon **p = new dragon*[warriorCountMax[actindex]];
                         memcpy(p , dragonIndex, sizeof(dragon *)*(warriorCountMax[actindex]-10));
                         delete dragonIndex;
                         dragonIndex = p;
                       }             
                       dragonIndex[count] = new dragon(tempkind,this,dataId,(float)lifeElement/(float)Cwarrior::get_consumption(tempkind));
                    } 
                    break; 
                    case ICEMAN: { 
                       if( count >= warriorCountMax[actindex]) {
                         warriorCountMax[actindex] += 10;       
                         iceman **p = new iceman*[warriorCountMax[actindex]];
                         memcpy(p , icemanIndex, sizeof(iceman *)*(warriorCountMax[actindex]-10));
                         delete icemanIndex;
                         icemanIndex = p;
                       }             
                       icemanIndex[count] = new iceman(tempkind,this,dataId);
                    }
                    break;             
                    case LION: { 
                       if( count >= warriorCountMax[actindex]) {
                         warriorCountMax[actindex] += 10;       
                         lion **p = new lion*[warriorCountMax[actindex]];
                         memcpy(p , lionIndex, sizeof(lion *)*(warriorCountMax[actindex]-10));
                         delete lionIndex;
                         lionIndex = p;
                       }             
                       lionIndex[count] = new lion(tempkind,this,dataId,lifeElement);
                    } 
                    break;           
                    case WOLF: { 
                       if( count >= warriorCountMax[actindex]) {
                         warriorCountMax[actindex] += 10;       
                         wolf **p = new wolf*[warriorCountMax[actindex]];
                         memcpy(p , wolfIndex, sizeof(wolf *)*(warriorCountMax[actindex]-10));
                         delete wolfIndex;
                         wolfIndex = p;
                       }             
                       wolfIndex[count] = new wolf(tempkind,this,dataId);
                    } 
                    break; 
                    default : break;
                }  
            }
        } 
        
    private:
        ninja **ninjaIndex ;
        dragon **dragonIndex ;
        iceman **icemanIndex ;
        lion **lionIndex ;
        wolf **wolfIndex ;
        int warriorCountMax[5] ;
}; 
int main(){
    unsigned int dataId;
    int *lifeElement,(*cost)[5];
    dealWithInput(dataId,lifeElement,cost);
    for (unsigned int i = 0; i < dataId; ++i) { 
        CNewHeadQuator* RedCommand=new CNewHeadQuator("red");
        CNewHeadQuator* BlueCommand = new CNewHeadQuator("blue");
        RedCommand->setLifeElement(lifeElement[i]);
        BlueCommand->setLifeElement(lifeElement[i]);
        Cwarrior::setwarriorConsumption(cost[i]);
        cout<<"Case:"<<i+1<<endl;
        int timeHour=0;
        while(RedCommand->haveResourceToProNext == true || BlueCommand->haveResourceToProNext ==true) 
        {
            if(RedCommand->haveResourceToProNext == true ){
                timeHourOutput(timeHour);
                RedCommand->produceWarriors();
            }
            if(BlueCommand->haveResourceToProNext == true){
                timeHourOutput(timeHour);
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
