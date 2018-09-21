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

typedef enum {
    NOFIGHT = 0,
    DRAW,
    REDWIN,
    BLUEWIN,
    BLUESHOTDEATH,
    REDSHOTDEATH,
    BOTHSHOTDEATH    
}DFightResult;
const string  warrior_string[] = {"dragon","ninja","iceman","lion","wolf"};
const string weaponsName[3] = { "sword","bomb","arrow"};
class headQuators;
class CWarrior;

class Ctime 
{ 
    public: 
        Ctime (); 
        virtual ~Ctime (); 
        static void timeincrease(){time++;}
        static void resettime(){time = 0;}
        static void timeout(){
            printf("%03d",time);
            printf(":%02d ",second);
        }
        static int getseond(int psecond){ second = psecond; return time*60 + second;}
    private: 
        static int time;
        static int second ;
}; 
int Ctime::time = 0;
int Ctime::second = 0;

class CWeapon {
    protected:
        CWarrior * master;
        string name;
    public:
        CWeapon(CWarrior * master1);
        virtual ~CWeapon();
        virtual void used() = 0;
};
CWeapon::CWeapon(CWarrior *master1):master(master1){}
class CSword : public CWeapon {
    private:
        int damage;
    public:
        /** * 需要考虑每使用一次攻击力变成80% */
        virtual void used();
        int getDamage();
        virtual ~CSword();
        CSword(CWarrior * master1);
};
CSword::CSword(CWarrior* master1):CWeapon(master1){
    damage = master->getDamage()/5; //剑的攻击力为武士的20%
    name = "sword";
}
void CSword::used(){
    damage = damage*4/5;
}
class CArrow : public CWeapon {
    private:
        static int R;
		int availableTimes;
    public:
        CArrow(CWarrior * p);
        virtual ~CArrow();
        virtual void used();
        static int getR();
        static void setR(int r);
};
int CArrow::R = 0;
CArrow::CArrow(CWarrior* master1):CWeapon(master1){
    name = "arrow";
    availableTimes = 3;
}
void CArrow::used(){
    availableTimes -= 1;  //剑使用一次
}
 int CArrow::getR() {
    return R;
}
 void CArrow::setR(int r) {
    R = r; 
}

class CBomb : public CWeapon {

	public:
		CBomb(CWarrior * master1);
		virtual ~CBomb();
		virtual void used();
};
CBomb::CBomb(CWarrior *master1):CWeapon(master1){
      name = "bomb";
}
void CBomb::used(){
    return;
}
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
void CWarrior::equipWeapon(int m){
    switch (m%3) { 
        case 0: { 
        if( damage /5 ==0 ) return;            
            sword = new CSword(this);            
        } 
        break; 
        case 1: { 
            bomb = new CBomb(this);            
        } 
        break; 
        default: { 
            arrow = new CArrrow(this);         
        } 
        break; 
    } 
}
CWarrior::CWarrior(headQuators *p):commander(p){
    type = (WARRIORKIND)commander-> manufactorSequency[commander->act];  
    int actIndex = (int) type;
    num = commander->dataId ; 
    hp = commander-> consumption[actIndex];
    damage = commander->warriorDamage[actIndex]; 
    cout<<' '<<commander->name <<' '<<warrior_string[actIndex]<<" "<<num<<" "<<"born"<<endl; //with strength "<<hp;
    //cout<<','<<commander-> warriorCount[actIndex]<<' '<<warrior_string[actIndex]<<" in "<<commander->name <<" headquarter"<<endl;
    actCity = p ;　
    sowrd = nullptr;
    bomb = nullptr;
    arrow = nullptr;    
}
void CWarrior::marchToCity(CCity *nextCity){
    actCity =  nextCity;
}
bool CWarrior::escape(){
    return false;
}
void CWarrir::hpAndForceOutput{
    cout<<"with "<<hp<<" elements and force "<<damage;
}
void CWarrior::takeLifeElement(int m){
    commander->addLifeElement(m); //将生命元输送到司令部 
}
//输出样例： 000:35 blue dragon 1 shot
/*表示在 0点35分，编号为1的蓝魔dragon武士射出一支箭。如果射出的箭杀死了敌人，则应如下输出：*/
//000:35 blue dragon 1 shot and killed red lion 4
/*表示在 0点35分，编号为1的蓝魔dragon武士射出一支箭，杀死了编号为4的红魔lion。*/
void CWarrior::useArrow(CWarrior *p){
   if( arrow == nullptr ) return;  //有箭
   arrow->used();  //用箭
   p->shotByArrow(CArrow::R);  //对方被射伤 
   if( arrow->getAvailableTimes() == 0 ) {　 //使用到了３次
        delete arrow;　　//arrow没了
        arrow = nullptr;
   }
   Ctime::out();
   nameIdOutPut();
   cout<<" shot ";
   if( p->getLifeElement <= 0) { //对方被射死
       cout<<"and killed "; 
       p->nameIdOutPut();
   }
   cout<<endl;
}
//输出样例： 000:38 blue dragon 1 used a bomb and killed red lion 7
//表示在 0点38分，编号为1的蓝魔dragon武士用炸弹和编号为7的红魔lion同归于尽。
bool CWarrior::useBomb(CWarrior *p){
    if(bomb == nullptr) return false;
    //bomb->used(); 
    bomb = nullptr;
    actCity = nullptr;
    p->setCity(nullptr); 
    //p->setBomb(nullptr); //按说这里是需要设置的，但不影响最终结果
    Ctime::out();
    nameIdOutPut();
    cout<" used a bomb and killed ";
    p->nameIdOutPut();      
    cout<<endl;
    return true;
}
//勇士使用剑，信息输出在上层
void CWarrior::useSword(){
    if( sword == nullptr) return;
    else {
        sword->used();
        if( sword->getDamage() <= 0){
            delete sword;
            sword = nullptr;
        } 
    } 
}
void CWarrior::earnLifeElement(int m){
    commander->addEarnedLifeElement(m); 
}
bool CWarrior::confiscated(CWarrior *p){
    return false;
}
void CWarrior::getSwordDamage(){
    return sword == nullptr? 0: sword->getDamage(); 
}
void CWarrior::attack(CWarrior *p){
    int dd = getSwordDamage;
    useSword();
    p->hurted(damage+dd);
    if( p->getLifeElement() <= 0 ){

        return -1;//对方被杀死 
    }  
    else {　//对方没死
        p->fightBack(this);  //对方反击
    }
    if( lifeElement >0 ) return 0; //
    反击己方没死，平局
    else return 1;　　　//反击己方被杀死，对方赢
}
void CWarrior::fightBack(CWarrior *p){
    p->hurted(damage/2 + getSwordDamage()); 
    useSword();
}
void CWarrior::hurted(int n){
    lifeElement -= n;
}

void CWarrior::shotByArrow(int m){
    lifeElement -=n ;
}
void CWarrior::cheerup(){
    return ;
}
void CWarrior::addHp(int m){
    hp += m;
}
void CWarrior::weaponNmInfoOutput(){
    if (arrow != nullptr) printf(" arrow(%d),",arrow->getAvailableTimes());  
    if( bomb != nullptr) cout<<"bomb,"
    if( sword != nullptr){
        printf("sword(%d)\n",sword->getDamage()); 
        return;
    }
    cout<<" no weapon"<<endl;
}
class CCity {
private:
	int num;
protected:
	CWarrior * newRed;
	CWarrior * newBlue;
    CWarrior * oldRed;
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
	CCity(int m=0);
    void setNum(int m);
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
class headQuators :public CCity
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
        int manufactorSequency[TOTAL_WARRIOR_kIND];
        int act;
        int warriorCount[TOTAL_WARRIOR_kIND];  //每个种类的计数
        int dataId;
        CWarrior **warriorP[TOTAL_WARRIOR_kIND];  //warriorP用于记录每种指针
        int warriorCountMax[TOTAL_WARRIOR_kIND] ; //warriorP每个类别指针数组的最大长度
        static int consumption[TOTAL_WARRIOR_kIND];
        friend class CWarrior;
};
class CNinja:public CWarrior 
{ 
    public: 
       
        virtual ~ninja(){
            delete weapon1;
            delete weapon2;
        } 
    private: 
        CWeapon *weapon1;
        CWeapon *weapon2;
}; 
CNinja::CNinja( headQuators *p):CWarrior(p){ 
    equipWeapon(num);
    equipWeapon(num+1);
 //cout<<"It has a "<<weaponsName[num%3]<<" and a "<<weaponsName[(num+1)%3]<<endl;  
 }            
void CNinja::fightBack(CWarrior *p){}
class CDragon:public CWarrior
{ 
    public: 
        dragon(headQuators *p):CWarrior(p){
            weapon =  new CWeapon(weaponsName[num%3],this);
            //cout<<"It has a "<<weaponsName[num%3]<<",and it's morale is "<<fixed<< setprecision(2)<<morale<<endl;
        } 
        virtual ~dragon(){
            delete weapon;
        }
    private: 
        CWeapon *weapon;
        float morale;
}; 
CDragon:CDragon(headQuators *p):CWarrior(p){
    morale = float(commander->getLifeElement() ) /(float) hp ;
    equipWeapon(num);
    cout<<"Its morale is "<<fixed<<setprecision(2)<<morale<<endl;
}
//dragon类的战斗逻辑需要考虑杀死敌人，士气增加，未获胜，士气值减少
virtual int CDragon::attack(CWarrior *p){
    int temp = CWarrior::attack(p);
    if ( temp == -1 ){
        morale +=0.2;
    }
    else morale -= 0.2;  //平局或者被对方杀死
    return temp;
}
/*virtual void CDragon::hutred( int n){*/
    
/*}*/
virtual void CDragon::fightBack(CWarrior *p){
    CWarrior::fightBack(p);
    if( p->getLifeElement() <= 0 ) //反击将对方反击死，士气加2
       morale += 0.2;
    else morale -= 0.2 ; //反击未将对方反击死，士气减2
}
//dragon 在一次在它主动进攻的战斗结束后，如果还没有战死，而且士气值大于0.8，就会欢呼
//输出样例：003:40 blue dragon 2 yelled in city 4
void CDragon::cheerup(){
    if (morale > 0.8) { 
        nameIdOutPut();
       cout<<" yelled in city "<< actCity->getNum()<<endl;   
    } 
}
class CIceman:public CWarrior 
{ 
    public: 
        virtual ~iceman(){
            delete weapon;
        } 
         
    private: 
        CWeapon *weapon;
}; 
CIceman::CIceman(headQuators *p):CWarrior(p){
    step = 0;
    equipWeapon(num);
    //cout<<"It has a "<<weaponsName[num%3]<<endl;
} 
class CLion:public CWarrior 
{ 
    public: 
        lion(headQuators *p):CWarrior(p){
            loyalty = commander->getLifeElement()  ; 
            cout<<"It's loyalty is "<<loyalty<<endl;
        } 
    private: 
        int loyalty;
}; 
int CLion::K = 0;
CLion:Clion(headQuators *p):CWarrior(p){
          loyalty = commander->getLifeElement()  ; 
          cout<<"It's loyalty is "<<loyalty<<endl;
      }
//输出样例： 000:05 blue lion 1 ran away 
//表示在 0点5分，编号为1的蓝魔lion武士逃走
virtual bool CLion::escape(){
    if ( loyalty <= 0 ) { 
        Ctime::out();
        cout<<" ";
        nameIdOutPut();        
        cout<<" ran away"<<endl;
        actCity = nullptr;
        return true; 
    }
    else return false; 
}
/*狮子攻击反击需要考虑的问题：*/
//1.没有武器
//2.战斗未杀死对方情况下，士气减弱Ｋ，这里也分为主动攻击未杀死对方和自己被攻击
//反击的情况下未杀死对方
/*3.被杀死的时候，生命值转移到对方*/
virtual void CLion::attack(CWarrior *p){
    p->hurted(damage);
    if( p->getLifeElement() <= 0 )  return -1;//对方被杀死 
    else {　//对方没死
        p->fightBack(this);  //对方反击
        loyalty -= K;       //　自己的士气减少
    }
    if( lifeElement >0 ) return 0; //反击己方没死，平局
    else return 1;　　　//反击己方被杀死，对方赢
}
virtual void CLion::fightBak(CWarrior *P){
    p->hurted(damage/2); //狮子被攻击，会反击对方
    if( p->getLifeElement() <= 0) return;　//对方被杀死，返回
    else loyalty -= K;   //反击对方没死，狮子经历了一场未胜利的战斗
}   
virtual void CLion::hurted(int n){
    lifeELement -= n;
    CWarrior *temp;
    //lion被杀死，生命值转移到对方，但又不包含被射死的情况
    if(lifeElement <= 0){
        temp = actCity->getNewRed(); 
        if( p != this) 
        {  
            //生命值转移到对方
            p -> lifeElementTransCauseLionDieBattle(lifeElement +n);
            return ;      
        }
        else　actCity->getNewBlue()->lifeElementTransCauseLionDieBattle(lifeElement +n);   
    }
}
class CWolf:public CWarrior{
    public:
        wolf(headQuators *p):CWarrior(p){}
};
CWolf:CWolf(headQuators *p):CWarrior(p){ }
void CWolf::attack(CWarrior *p){
    int temp;
    temp = CWarrior::attack(p):
    if( temp == -1) confiscated(p);
    return temp;    
}
void CWolf::fightBack(CWarrior *P){
    CWarrior:fightBack(p);
    if( p->getLifeElement() <= 0) { //对方被反击死，缴获对方武器
        confiscated(p);     
    }          
}
bool CWolf::confiscated(CWarrior *p){
    CWeapon temp;
    bool result =  false ;
    if(sword == nullptr && (temp= p->getSword())!= nullptr)  //自己没的才缴获 
    {
        sword = temp ;
        p->setSword(nullptr);
        result = true;
    }
    if(arrow == nullptr && (temp= p->getArrow())!= nullptr)  //自己没的才缴获 
    {
        arrow = temp ;
        p->setArrow(nullptr);
        result = true;
    }
    if(bomb == nullptr && (temp= p->getBomb())!= nullptr)  //自己没的才缴获 
    {
        bomb = temp ;
        p->setBomb(nullptr);
        result = true;
    }
   return result; 
}
void CIceman::marchToCity(CCity *nextCity){
    actCity = nextCity;
    step++;
    if(step%2 == 0)  //每走两步
    {
        hp -= 9;
        if( hp <= 0 ) hp=1;
        damage ++ 20;
    }    
}
int CCity::totalNum = 0;
CCity::CCity(int m):num(m) {
    flag = NOFLAG;
    preFightResult = NOFIGHT;
    actFightResult = NOFIGHT;
    warriorShotByArrow = nullptr;
    newBlue = nullptr;
    newRed = nullptr ;
    oldRed = nullptr;
    lifeElement = 0;
    shotByEnemy = nullptr;
}

void CCity::setNum(int m){num = m;}
int CCity::getLifeElement() {
    return lifeElement;
}

void CCity::setLifeElement(int m) {
	this->lifeElement = m;
}
//在每个小时的第20分：每个城市产出10个生命元。生命元留在城市，直到被武士取走
void CCity::producelifeElement() {
    lifeElement += 10 ;
}

void CCity::march(){  //march只负责将勇士向前推进，不负责记录逻辑
   CCity *temp;
  if( num != totalNum )  
      temp = this +1 ;
  else temp = City[num+1] ;
  temp->setNewRedtoOld();
  temp->setNewred(oldRed); 
 // 处理cout那些垃圾
  if( newRed != nullptr ) {
      newRed->marchToCity(temp); 
      Ctime::timeout();
      newRed.NameIdOutPut();
      if(num == totalNum)
      {
        cout<<"reached blue headquarter";
      }
      else  cout<<" march to city "<<num+1;
      newRed.hpAndForceOutput();
      cout<<endl;
  }
  if(num ! = 1)
      temp = this -1;
  else temp = City[0]  ;
      temp->setNewblue(newBlue);
 //处理ｃｏｕｔ垃圾
  if( newBlue != nullptr ) {
      newRed->marchToCity(temp); 
      Ctime::timeout();
      newBlue.NameIdOutPut();
      if(num == 1) cout<<"reached red headquarter"; 
      else cout<<" marched to city "<<num-1;
        newRed.hpAndForceOutput();
      cout<<endl;  
  }
}
void  CCity::bombUsed() {
	// TODO - implement CCity::bombUsed
	throw "Not yet implemented";
}
void CCity::fight() {
    if( newRed != nullptr && newBlue != nullptr){
        CWarrior *attacker = newRed;
        CWariior *target = newBlue;
        int reverse = -1;
        if( flag == BLUEFLAG || (flag == NOFLAG && num%2 ==0 )) {//蓝方主动攻击 
            attacker = newBlue;
            target = newRed ;
            reverse =1;
        } 
        int k = attacker->attack(target);
        if( reverse * k == 0) actFightResult = DRAW;
        else if( reverse*k == 1) actFightResult = REDWIN;
        else actFightResult = BLUEWIN;
    }
    activeAttackInfoOutput(); //主动攻击信息输出
    fightBackInfoOutput(); //反击信息输出
    killInfoOutput(); //被杀信息输出
    newRed = actFightResult == BLUEWIN? nullptr:newRed;
    newBlue = actFightResult == REDWIN? nullptr:newBLue;
    //勇士欢呼,条件是自己没死，并且轮到自己主动进攻
    if(　newRed != nullptr ){ 
        if( reverse == -1) newRed->cheerup(); 
    }
    if( newBlue != nullptr){
        if( reverse == 1) newBlue->cheerup(); 
    } 
    //处理被剑射死时候的武器缴获,战斗情况下的武器缴获处理包含在attack 函数里
    if(actFightResult == BLUESHOTDEATH){  //蓝武士被杀死，红武士缴获兵器
        newRed->confiscated(shotByEnemy); 
    }
    if(actFightResult == REDSHOTDEATH){   //处理被剑射死时候的武器缴获
        newBlue->confiscated(shotByEnemy); //红武士被射死，蓝武士缴获兵器
    }
    //拿生命元和升旗仪式需要一方胜利
    if( actFightResult == REDWIN || BLUESHOTDEATH){  //红方胜
        //红方武士取走生命元并暂存在司令部的earnedLifElement里
        newRed->earnLifeElement(lifeElement);
        lifeElement = 0; 
        if(preFightResult == REDWIN || BLUESHOTDEATH){ //连续两场红方胜
            if( FLAG == BLUEFLAG || FLAG == NOFLAG ) setFlag(REDFLAG);
        }
    }
    if( actFightResult == BLUEWIN || actFightResult == REDSHOTDEATH) { //蓝方胜利
        //蓝方武士取走生命元并暂存在司令部的earnedLifElement里
        newBlue->earnLifeElement(lifeElement);
        lifeElement = 0; 
        if( preFightResult == BLUEWIN ||preFightResult ==  REDSHOTDEATH) { //蓝方胜利
            if(FLAG == REDFLAG || FLAG == NOFLAG ) setFlag(BLUEFLAG);
        }
    }
    //当某个城市有连续两场战斗都是同一方的武士杀死敌人(两场战斗之间如果有
    //若干个战斗时刻并没有发生战斗，则这两场战斗仍然算是连续的；但如果中间
    //有平局的战斗，就不算连续了) ，那么该城市就会插上胜方的旗帜，
    if( actFightResult != NOFIGHT || actFightResult != BOTHSHOTDEATH) 
        preFightResult = actFightResult;
}
void CCity::activeAttackInfoOutput(){
    Ctime::out();
    attacker-> nameIdOutPut(); 
    cout<<" attacked ";
    target-> nameIdOutPut();
    cout<<" in city "<<num<<" ";
    attacker-> hpAndForceOutput(); cout<<endl;
}
void CCity::fightBackInfoOutput(){
    if( target->getLifeElement()<=0) //被主动攻击直接杀死，没有反击
       return ;
    Ctime::out(); target-> nameIdOutPut(); cout<<" fight against "; 
    attacker->nameIdOutPut(); cout<<" in city "<<num<<" "<<endl;
}
void CCity::killInfoOutput(){
    if( actFightResult == REDWIN){
        Ctime::out();
        newRed->nameIdOutPut();
       cout<<" was killed in city "<<num<<endl; 
    }
    if( actFightResult == BLUEWIN){
        Ctime::out();
        newBlue->nameIdOutPut();
       cout<<" was killed in city "<<num<<endl; 
    }
    
}
//30分不战斗时获取生命元
void  CCity::lifeElementTaken() {
    if( newRed != nullptr && newBlue == nullptr) {  //只有红方武士
        newRed->takeLifeElement(lifeElement); //红方武士取走生命元并传送到司令部
        lifeElement = 0;
    }
    if( newRed == nullptr && newBlue != nullptr) {  //只有蓝方武士
        newBLue->takeLifeElement(lifeElement); //蓝方武士取走生命元并传送到司令部
        lifeElement = 0;
    }
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
void CCity::lionEspcae(){
   if( newRed!=nullptr && newRed->escape()==true )
          //delete newRed;
          newRed = NULL;
   }  
   if ( newBlue!=nullptr && newBlue->escape()==true) { 
       //delete newBlue;
       newBLue = NULL ; 
   } 
}
void CCity::releaseArrow(){
   CWarrior *p; 
   //红武士所在城市的右方是蓝军司令部，不需要放箭,因为敌人已经在10分时走掉，
   //但程序上没有写敌人走掉的逻辑，实际上此时程序运行的是有敌人
   if( newRed != nullptr && num != totalNum) //本城市的右方不是敌方司令部
   {
       p = city[num+1]->getNewBlue();  //取得下一步要到达城市的敌人地址
       if( p != nullptr ) newRed->useArrow(p); 
   }  
   //蓝武士所在城市的左方如果是红军司令部，不需要放箭,因为敌人已经在10分时走掉
   if( newBlue != nullptr && num!= 1) {
       p = city[num-1]->getNewRed(); //取得下一步要走到城市的敌人地址
       if( p != nullptr ) newBlue->useArrow(p); 
   }
}
//射箭结果影响到后续缴获武器，旗帜更换等，所以必须要记录在这里
void CCity::recordArrowResult(){
    if ( newRed!= nullptr && newRed->getLifeElement()<= 0 ) { //放箭死
        newRed->setCity(nullptr);
        shotByEnemy = newRed ;
        newRed == nullptr;
        if( newBlue != nullptr ){
            if( newBlue->getLifeElement() <=0 ) //两个都被射死 
                actFightResult = SHOTBOTHDEATH;
            else actFightResult = REDSHOTDEATH;
        }   
    }     
    if (newBlue != nullptr && newBlue->getLifeElement()<= 0 ) { 
        newBlue ->setCity(nullptr);
        shotByEnemy = newBlue;
        newBLue = nullptr;  
        if( newRed! = nullptr) actFightResult = BLUESHOTDEATH;
    } 
}
void　CCity::bombUsed(){
    int damage,hp;
    if( newRed != nullptr && newBlue != nullptr){  //有两个武士才评估是否使用炸弹
        damage = newBlue->getDamage();
        hp = newRed->getLifeElement();  
        if( damage >= hp || damage/2 >= hp) //红方武士判断被对方攻击死或者自己攻击被反击死 
        {
            if( newRed->useBomb(newBlue) ){
                newRed = nullptr;
                newBlue = nullptr;
                return ;
            }
        }    
        damage = newRed->getDamage();
        hp =  newBlue->getLifeElement();  
        if( damage >= hp || damage/2 >= hp) //蓝方武士判断被对方攻击死或者自己攻击被反击死 
        {
            if( newBlue->useBomb(newRed)) {
                newRed = nullptr;
                newBlue = nullptr;
                return ;
            }
        }    
    }    
}
void CCity::blueWarriorGetPrize(){
    if( actFightResult == BLUEWIN ) {
        newBLue->addHp(8);
        city[totalNum+1]-> addLifeElement(-8); 
    }
}
void CCity::redWarriorGetPrize(){
    if ( actFightResult == REDWIN){
        newRed->addHp(8);
       city[0]->addLifeElement(-8);  
    }
}
void CCity::redWarriorReportWeapon(){
    if( newRed == nullptr ) return;
    Ctime::out();
    newRed->nameIdOutPut();
    cout<<" has ";
    newRed->weaponNmInfoOutput();     
}
void CCity::blueWarriorReportWeapon(){
    if( newBlue == nullptr ) return;
    Ctime::out();
    newBlue->nameIdOutPut();
    cout<<" has ";
    newBlue->weaponNmInfoOutput();     
}
headQuators ::headQuators(string name1):name(name1){
    haveResourceToProNext = true ;
    act = 0;
    dataId = 0;
    memset(warriorCount,0,sizeof(warriorCount));　//设定初始的计数器为０
    setManufactorSequency();
    for ( int i = 0; i < TOTAL_WARRIOR_kIND; ++i) { 
        warriorCountMax[i] = 10　　;　　//设定初始的每个指针数组的长度为１０
        warriorP[i] = new CWarrior*[10];
    } 
    taken = false;
    arrived = false;
    earnedLifeElement = 0;
    totalMax = 100;
    if(name == "blue") num = totalNum+1;
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
                                warriorP[actIndex][warriorCount[actIndex]-1] = new CNinja(this);                
                            } 
                            break; 
                case DRAGON: { 
                                 warriorP[actIndex][warriorCount[actIndex]-1] = new CDragon(this);                
                             } 
                             break; 
                case ICEMAN: { 
                                 warriorP[actIndex][warriorCount[actIndex]-1] = new CIceman(this);                
                             } 
                             break; 
                case LION: { 
                               warriorP[actIndex][warriorCount[actIndex]-1] = new CLion(this);                
                           } 
                           break; 
                case WOLF: { 
                               warriorP[actIndex][warriorCount[actIndex]-1] = new CWolf(this);                
                           } 
                           break; 
            } 
            act = (act+1)%TOTAL_WARRIOR_kIND ;
            haveResourceToPronext = true;
            return 1;
        }
            act = (act+1)%TOTAL_WARRIOR_kIND ;
    }
    haveResourceToProNext = false ;
    //cout<<' '<<name<<" headquarter stops making warriors"<<endl;//
    return -1;  
}
void headQuators::setwarriorConsumption(int *cost){
    memcpy(consumption,cost,sizeof(int )*TOTAL_WARRIOR_kIND);
}      
void virtual headQuators::lionEspcae(){
    switch ( name ) { 
        case red: { 
                      if( newRed != nullptr && newRed->escape() == true)
                          newRed  == nullptr;               
                  } 
                  break; 

        default: { 
                     if ( newBlue != nullptr && newBlue->escape() == true )
                         newBlue == nullptr; 
                 } 
                 break; 
    } 
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
void headQuators::march(){ //march 之前必须保证newRed 和　newBlue是正确的
    City *temp;
    if (name == "red" ) {
        temp = City[1];
        temp->setNewRedtoOld();
        temp->setNewred(newRed);
        //处理ｃｏｕｔ
        if(newRed != nullptr) 
        {
            newRed->marchToCity(temp); 
            Ctime::out(10);
            newRed.nameIdOutPut();
            cout<<" marched to city 1 "
            newRed.hpAndForceOutput();    
        }    
        return ;
    }
    if( name == "blue"){
        temp = City[totalNum];
        temp->setNewblue(newBLue);
        //处理ｃｏｕｔ
        if(newBlue != nullptr) 
        {
            newBlue->marchToCity(temp); 
            Ctime::out(10);
            newBlue.nameIdOutPut();
            cout<<" marched to city "<<CCity::getTotalNum()<<" ";
            newBlue.hpAndForceOutput();    
        }    
        return ;
    }
}
void headQuators::setNewRedAndNewBlue(){
   int i = (act-1+TOTAL_WARRIOR_kIND)%TOTAL_WARRIOR_KIND;
   switch (name) { 
       case "red": {
            if( haveResourceToPronext == false) newRed = nullptr;                
            else newRed =  warrior[i][warriorCount[i]-1];
       } 
       break; 
   
       default: { 
            if( haveResourceToPronext == false) newBLue = nullptr;                
            else newBLue =  warrior[i][warriorCount[i]-1];
       } 
       break; 
   }  
}
void headQuators::addEarnedLifelement(int m){
    earnedLifeElement +=m;
}    
void headQuators::accquireTrophy(){
    lifeElement += earnedLifeElement;
    earnLifeElement = 0;
}
void headQuators::addlifeElement(int m){
    lifeElement += m;
}
void headQuators::reportLifeElement(){
    Ctime::out();
    cout<<" "<<lifeElement<<" elements in "<<name<<" headquaters"<<endl;
}
CCcity **City;
int main(){
    unsigned int dataNum;  //数据测试组数
    //定义参数，用以处理输入参数。例如城市生命源，城市数目等
    int M,N,K,R,T,cost[TOTAL_WARRIOR_kIND],inputDamage[TOTAL_WARRIOR_kIND]; 
    cin>>dataNum;
    for(unsigned int actcase = 0; actcase< dataNum; actcase++){
        cout<<"Case "<< actcase + 1 <<":"<<endl;
        dealWithInput(M,N,K,R,T,cost,inputDamage);
        CCity::setTotalNum(N);
        CWarrior::setK(K);
        CArrow::setR(R);
        Ctime battletime;
        headQuators* RedCommand=new headQuators("red");
        headQuators* BlueCommand = new headQuators("blue");
        while( RedCommand->taken ! =  true ||  BlueCommand -> taken!= true )
        RedCommand->setLifeElement(M);  //设定城市的初始生命元
        BlueCommand->setLifeElement(M); //同上
        headQuators::setwarriorConsumption(cost);　　//设定司令部生产消耗
        headQuartors::setWarriorDamage(inputDamage);　//设定司令部生产武士的攻击力
        City = new CCity*[N+2]; //City指向的内存，存放司令部和城市的对象指针
        City[0] = RedCommand;
        City[N+1] = BlueCommand ;
        CCity *temp = new CCity[N];
        for ( int i = 0; i < N; ++i) { 
            City[i+1] =  temp+i;　//将城市的指针赋值到 City[N+2]数组里，方便后续写代码
            temp->setNum(i+1);   //设定城市的编号
        } 
        while(1) 
        {
            //需要reset 所有战斗状态
            //每小时０分事件（武士出生）输出
            if (Ctime::getseond(0)>T)  break;  
            RedCommand->produceWarriors();  //先制造一个武士
            RedCommand->updataWarriors();  //将制造新武士设置为newRed
            BlueCommand->produceWarriors();　//蓝方制造一个武士
            BlueCommand->updataWarriors();　//蓝方制造的武士设置为newblue
            
            //每小时５分事件（lion逃跑）
            if(Ctime::getseond(5)>T) break; 
            for ( int i = 0; i < N+2 ; ++i)  city[i]->lionescape(); 
                
            //１０分事件输出，包含武士前进到某一城市，城市被占领等
            for ( int i = 0; i < N+2; ++i)  City[i]->march();  //所有的武士前进
            //前进后判断是否司令部被占领
            if( RedCommand->newblue != nullptr ){
                if(arrived == false) arrived = true;  //是第一次到达的话，设定到达为真
                else taken = true;　　//如果之前已经有武士到达，说明司令部被占领　　　　　　　
            } 
            if( BlueCommand->newRed != nullptr){
                if(arrived == false) arrived = true;  //是第一次到达的话，设定到达为真
                else taken = true;　　//如果之前已经有武士到达，说明司令部被占领　　　　　　　
            } 
            if(RedCommand->getTaken() == true || BlueCommand->getTaken() == true)
              break;  //有司令部被占领，则循环终止  

            //20分事件（每个城市产生10个生命元）输出
            if( Ctime::getsecond(20) >T) break;
            for ( int i = 0; i < N; ++i)  city[i+1]-> produceLifeElement(); 

            //30分事件(如果一个城市只有一个武士，武士取走生命元,并输送到司令部)
            if( Ctime::getsecond(30) >T) break;
            for ( int i = 0; i < N; ++i)  city[i+1]->lifeElementTaken();  

            //35分事件输出（武士射箭）
            if( Ctime::getsecond(35) >T) break;
            for ( int i = 0; i < N; ++i)  city[i+1]->releaseArrow(); 
            for ( int i = 0; i < N ; ++i) { //记录射箭结果，方便缴获武器，旗帜更换等
                city[i+1]->recordArrowResult(); 
            }

            //38分事件输出（武士使用bomb)
            if( Ctime::getsecond(35) >T) break;
            for ( int i = 0; i < N ; ++i)  city[i+1]->bombUsed(); 
             
            //40分事件输出，包括主动进攻、反击、战死、欢呼、获取生命元、升旗
             if( Ctime::getsecond(40) >T) break;
            for ( int i = 0; i < N ; ++i)  city[i+1]->fight(); 
            //如果司令部的生命元不足以奖励所有的武士，则优先奖励距离敌方司令部近的武士。
            for ( int i = 0; i < N ; ++i) { 
               if( RedCommand->getLifeElement() <8 ) break;  
               city[i+1]->blueSendOutPrize(); 
            } 
            for ( int i = 0; i < N ; ++i) { 
               if( BlueCommand->getLifeElement() <8 ) break;  
               city[totalNum-i]->redSendOutPrize(); 
            } 
            RedCommand->accquireTrophy();  //发放完了奖励后，取得战斗胜利的生命元 
            BlueCommand->accquireTrophy(); 
            for ( int i = 0; i < N ; ++i)  city[i+1]->resetFightResult(); //恢复战斗结果
            
          //50分司令部报告生命源数量000:50 100 elements in red headquarter  
          if( Ctime::getseond(50)>T) break;
          RedCommand->reportLifeElement();
          BlueCommand->reportlifeElement();  

          //55分武士报告武器情况
          if(Ctime::getsecond(55)>T ) break;
          for ( int i = 0; i < N ; ++i) { 
              city[i+1]->redWarriorReportWeapon(); 
          } 
          for ( int i = 0; i < N ; ++i) { 
              city[i+1]->blueWarriorReportWeapon(); 
          } 
            Ctime::timeincrease();
        }    
        delete RedCommand;
        delete BlueCommand;
        delete []temp;
    }
    delete []cost;
    delete []lifeElement;
    return 0;
}
