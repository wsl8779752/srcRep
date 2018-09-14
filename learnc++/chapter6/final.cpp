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
}DFlag;
typedef enum{
    DRAW = 0,
    REDWIN ,
    BLUEWIN,
}DFightResult;
typedef enum {
    NOFIGHT = 0,
    redWin,
    blueWin,
    blueShotDeath,
    redShotDeath
} DFightResult;
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
class CWarrior 
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
class CCity {
private:
	int num;
protected:
	CWarrior * newRed;
	CWarrior * newBlue;
    Cwarrior * oldRed;
private:
	DFlag flag;
	DFightResult preFightResult;
	DFightResult actFightResult;
	int warriorShotByArrow;
protected:
	int lifeElement;
private:
	static int totalNum;

public:
	CCity(int m = 0);
	int getLifeElement();
	void setLifeElement(int m);
	void addlifeElement(int m = 10);
	void march();
	void  bombUsed();
	void fight();
	void  earnLifeElement();
	void resetFlag();
	void blueWarriorGetPrize();
	void redWarriorGetPrize();
	CWarrior * getNewblue();
	void setNewblue(CWarrior * newblue);
	CWarrior * getNewred();
	void setNewred(CWarrior * newred);
	void getTotalNum();
	void setTotalNum(int totalNUM);
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
int CCity::totalNum = 0;
CCity::CCity(int m ):num(m) {
    flag = NOFLAG;
    preFightResult = NOFIGHT;
    actFightResult = NOFIGHT;
    warriorShotByArrow = nullptr;
    newBlue = nullptr;
    newRed = nullptr ;
    lifeElement = 0;
}

int CCity::getLifeElement() {
    return lifeElement;
}

void CCity::setLifeElement(int m) {
	this->lifeElement = m;
}

void CCity::addlifeElement(int m) {
    lifeElement += m ;
}

void CCity::march() {  //march只负责将勇士向前推进，不负责记录逻辑
    CCity *temp;
  if( num != totalNum )  
      temp = this +1 ;
  else temp = City[num+1] ;
  temp->setNewRedtoOld();
  temp->setNewred(oldRed); 
 // 处理cout那些垃圾
  if( newRed != nullptr ) {
      Ctime::timeout(10);
  }

  if(num ! = 1)
      temp = this -1;
  else temp = City[0]}  ;
      temp->setNewblue(newBlue);
 //处理ｃｏｕｔ垃圾
}

void  CCity::bombUsed() {
	// TODO - implement CCity::bombUsed
	throw "Not yet implemented";
}

void CCity::fight() {
	// TODO - implement CCity::fight
	throw "Not yet implemented";
}

void  CCity::earnLifeElement() {
	// TODO - implement CCity::earnLifeElement
	throw "Not yet implemented";
}

void CCity::resetFlag() {
	// TODO - implement CCity::resetFlag
	throw "Not yet implemented";
}

void CCity::blueWarriorGetPrize() {
	// TODO - implement CCity::blueWarriorGetPrize
	throw "Not yet implemented";
}

void CCity::redWarriorGetPrize() {
	// TODO - implement CCity::redWarriorGetPrize
	throw "Not yet implemented";
}

CWarrior * CCity::getNewblue() {
	return this->newblue;
}

void CCity::setNewblue(CWarrior * newblue) {
	this->newblue = newblue;
}

CWarrior * CCity::getNewred() {
	return this->newred;
}

void CCity::setNewred(CWarrior * newred) {
	this->newred = newred;
}

void CCity::setNewblue(CWarrior * newblue) {
	// TODO - implement CCity::setNewblue
	throw "Not yet implemented";
}

void CCity::setNewred(CWarrior * newred) {
	// TODO - implement CCity::setNewred
	throw "Not yet implemented";
}

void CCity::setNewblue(CWarrior * newblue) {
	this->newblue = newblue;
}

void CCity::setNewred(CWarrior * newred) {
	this->newred = newred;
}

void CCity::setNewblue(CWarrior * newblue) {
	// TODO - implement CCity::setNewblue
	throw "Not yet implemented";
}

void CCity::setNewred(CWarrior * newred) {
	// TODO - implement CCity::setNewred
	throw "Not yet implemented";
}

void CCity::setNewblue(CWarrior * newblue) {
	// TODO - implement CCity::setNewblue
	throw "Not yet implemented";
}

void CCity::setNewred(CWarrior * newred) {
	// TODO - implement CCity::setNewred
	throw "Not yet implemented";
}

void CCity::setNewblue(CWarrior * newblue) {
	// TODO - implement CCity::setNewblue
	throw "Not yet implemented";
}

void CCity::setNewred(CWarrior * newred) {
	// TODO - implement CCity::setNewred
	throw "Not yet implemented";
}
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
void dealWithInput(int& M,int& N,int& K,int& R,int& T,int *cost,int *inputDamage){
    cin>>M;
    cin>>N;
    cin>>R;
    cin>>K;
    cin>>T;    
    for (unsigned int j = 0; j < TOTAL_WARRIOR_kIND; ++j) { 
        cin>>cost[j];
        cin>>inputDamage[j];
    } 
}
void headQuators::march(){
    City *temp;
    if (name == "red" ) {
        temp = City[1];
        temp->setNewRedtoOld();
        temp->setNewred(newRed);
        //处理ｃｏｕｔ
        return ;
    }
    if( name == "blue"){
        temp = City[totalNum];
        temp->setNewblue(newBLue);
        //处理ｃｏｕｔ
        return ;
    }
}
class Ctime 
{ 
    public: 
        Ctime (); 
        virtual ~Ctime (); 
        static void timeincrease(){time++;}
        static void resettime(){time = 0;}
        static void timeout(); 
        static int getseond(int psecond){ second = psecond; return time*60 + second;}
    private: 
        static int time;
        int second ;
}; 
static void Ctime::timeout(){
    printf("%03d",time);
    printf("%02d",second);
}
int Ctime::time = 0;
int main(){
    unsigned int dataNum;  //数据测试组数
    //定义参数，用以处理输入参数。例如城市生命源，城市数目等
    int M,N,K,R,T,cost[TOTAL_WARRIOR_kIND],inputDamage[TOTAL_WARRIOR_kIND]; 
    cin>>dataNum;
    for(unsigned int actcase = 0; actcase< dataNum; actcase++){
        cout<<"Case "<< actcase + 1 <<":"<<endl;
        dealWithInput(M,N,K,R,T,cost,inputDamage);
        Ctime battletime;
        headQuators* RedCommand=new headQuators("red");
        headQuators* BlueCommand = new headQuators("blue");
        while( RedCommand->taken ! =  true ||  BlueCommand -> taken!= true )
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
