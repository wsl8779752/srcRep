/**
 * @file part4.cpp
 * @brief
 * @author rensheng946@163.com
 * @version 1.0
 * @date 2018-07-13
 */
#include <cstring>
#include <sstream>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <cstdio>
using namespace std;
#define TOTAL_WARRIOR_KIND 5
//#define TEST_MODE


typedef enum warriortype{
    DRAGON =0,
    NINJA,
    ICEMAN,
    LION,
    WOLF,
} WARRIORKIND;
typedef enum {
    NOFLAG=0,
    REDFLAG,
    BLUEFLAG
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
class CCity;
class CHeadquator;
class CWarrior;

class Ctime
{
    public:
        static void timeincrease(){time++;}
        static void resettime(){time = 0;}
        static void out(){
            printf("%03d",time);
            printf(":%02d ",second);
        }
        static int getSecond(int psecond){ second = psecond; return time*60 + second;}
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
class CSword : public CWeapon {
    private:
        int damage;
    public:
        CSword(CWarrior * master1);
        virtual ~CSword();
        /** * 需要考虑每使用一次攻击力变成80% */
        virtual void used();
        int getDamage();
};
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
        int getAvailableTimes();
};
class CBomb : public CWeapon {
	public:
		CBomb(CWarrior * master1);
		virtual ~CBomb();
		virtual void used();
};
class CWarrior {
    protected:
        int num;
        int hp;
        int damage;
        WARRIORKIND type;
        CHeadquator* commander;
        CCity* actCity;
        CSword * sword;
        CBomb * bomb;
        CArrow * arrow;
        //类的方法排序是按照属性的操作先后，
        //无属性的操作是按照时间发生顺序先后
    public:
        CWarrior(CHeadquator * p);
        virtual ~CWarrior();
        int getHp();
        void addHp(int m);
        int getDamage();
        void setDamage(int damage);
        WARRIORKIND getType();
        CCity* getCity();
        void setCity(CCity * city);
        void equipWeapon(int m);
        CSword * getSword();
        void setSword(CSword * sword);
        CBomb * getBomb();
        void setBomb(CBomb * bomb);
        CArrow * getArrow();
        void setArrow(CArrow * arrow);
        /** * 普通武士的march就是设定城市 */
        virtual bool escape();
        virtual void marchToCity(CCity * nextCity = nullptr);
        void takeLifeElement(int m);  //30分没战斗取得生命远
        void shotByArrow(int m);
        virtual int attack(CWarrior* p);
        virtual void fightBack(CWarrior* p);
        virtual void hurted(int m);
        virtual void cheerUp();
        virtual bool confiscated(CWarrior * p);
        /** * 输出自己的名字和Id，样例“blue dragon 2” */
        void nameIdOutput();
        /** * 输出生命值和攻击力样例“with 20 elements and force 30" */
        void hpAndForceOutput();
        void useArrow(CWarrior * p);
        bool useBomb(CWarrior * p);
        void useSword();
        int getSwordDamage();
        void earnLifeElement(int m);
        void lifeElementTransCauseLionDieBattle(int m);
        void weaponNmInfoOutput();
        /** * 需要看武器析构 */
};
class CDragon : public CWarrior {
    private:
        float morale;
    public:
        CDragon(CHeadquator* p);
        virtual ~CDragon();
        virtual int attack(CWarrior * p);
        virtual void fightBack(CWarrior * enemy);
        virtual void cheerUp();
};
class CNinja : public CWarrior {
    public:
        CNinja(CHeadquator * p);
        virtual ~CNinja();
        virtual void fightBack(CWarrior * p);
};
class CIceman :public CWarrior {
    public:
        CIceman (CHeadquator* p);
        virtual ~CIceman ();
        void marchToCity(CCity *nextCity);
    private:
        int step;
};
class CLion : public CWarrior {
    private:
        int loyalty;
        static int K;
    public:
        CLion(CHeadquator * p);
        virtual ~CLion();
        virtual int attack(CWarrior * p);
        virtual void fightBack(CWarrior * p);
        virtual void hurted(int m);
        virtual bool escape();
        static void setK(int K);
};
class CWolf : public CWarrior {
    public:
        CWolf(CHeadquator * p);
        virtual ~CWolf();
        virtual void fightBack(CWarrior * p);
        virtual int attack(CWarrior * p);
        virtual bool confiscated(CWarrior * p);
};

class CCity {
protected:
	int num;
	int lifeElement;
private:
	DFlag flag;
	DFightResult preFightResult;
	DFightResult actFightResult;
protected:
	static int totalNum;
	CWarrior * newBlue;
	CWarrior * newRed;
private:
	CWarrior * oldRed;
	CWarrior* warriorShotByEnemy;
public:
	CCity(int m = 0);
	virtual ~CCity();
	int getNum();
	void setNum(int num);
	int getLifeElement();
	void setLifeElement(int lifeElement);
	/** * 在每个小时的第20分：每个城市产出10个生命元。生命元留在城市，
     * 直到被武士取走 */
	void produceLifeElement();
	/** * 30分不包括战斗时的获取生命元 */
	void  lifeElementTaken();
	void setFlag(DFlag flag);
	void resetFightResult();
	static int  getTotalNum();
	static void setTotalNum(int n);
	CWarrior * getNewBlue();
	void setNewBlue(CWarrior * newblue);
	CWarrior * getNewRed();
	void setNewRed(CWarrior * newred);
	void setNewRedToOld();
	virtual void lionEscape();
	virtual void march();
    void releaseArrow();
	void recordArrowResult();
	void  bombUsed();
	void fight();
	void blueWarriorGetPrize();
	void redWarriorGetPrize();
	void activeAttackInfoOutput(CWarrior* attacker,CWarrior* target);
	void fightBackInfoOutput(CWarrior* attacker,CWarrior* target);
	void killInfoOutput();
    void redWarriorReportWeapon();
    void blueWarriorReportWeapon();

};
class CHeadquator : public CCity {
private:
	string name;
	bool haveResourceToProNext;
	int act;
	int dataId;
	int  manufactorSequency[TOTAL_WARRIOR_KIND];
	int warriorCountMax[TOTAL_WARRIOR_KIND];
	static int consumption[TOTAL_WARRIOR_KIND];
	int warriorCount[TOTAL_WARRIOR_KIND];
	CWarrior ** warriorP[TOTAL_WARRIOR_KIND];
	static int warriorDamage[TOTAL_WARRIOR_KIND];
	bool taken;
	bool arrived;
	int totalMax;
	long earnedLifeElement;
public:
	CHeadquator(string name1);
	virtual ~CHeadquator();
    string& getName();
    int getDataId();
    int getManufactorSequency();
	void setManufactorSequency();
    int getWarriorConsumption();
	static void  setWarriorConsumption(int * cost);
    int getWarriorDamage();
	static void setWarriorDamage(int * damage);
	bool getTaken();
	void setTaken(bool temp);
    bool getArrived();
    void setArrived(bool temp);
	int produceWarriors();
	virtual void  lionEscape();
	virtual void march();
	void setNewRedAndNewBlue();
	void addEarnedLifeElement(int m);
	void accquireTrophy();
	/** * 在原来的lifeElement 基础上增加m */
	void addLifeElement(int m);
    void reportLifeElement();
};

//CWarpon的方法定义
CWeapon::CWeapon(CWarrior *master1):master(master1){}
CWeapon::~CWeapon(){}

//CSword的方法定义
CSword::CSword(CWarrior* master1):CWeapon(master1){
    damage = master->getDamage()/5; //剑的攻击力为武士的20%
    name = "sword";
}
CSword::~CSword(){}
void CSword::used(){
    damage = damage*4/5;
}
int CSword::getDamage(){ return damage;}

//CArrow的方法定义
int CArrow::R = 0;
CArrow::CArrow(CWarrior* master1):CWeapon(master1){
    name = "arrow";
    availableTimes = 3;
}
CArrow:: ~CArrow(){}
void CArrow::used(){
    availableTimes -= 1;  //剑使用一次
}
 int CArrow::getR() {
    return R;
}
 void CArrow::setR(int r) {
    R = r;
}
int CArrow::getAvailableTimes(){return availableTimes;}

//CBomb的方法定义
CBomb::CBomb(CWarrior *master1):CWeapon(master1){
    name = "bomb";
}
CBomb::~CBomb(){}
void CBomb::used(){
    return;
}

//Cwarrior 的方法定义
CWarrior::CWarrior(CHeadquator *p):commander(p){
    type = (WARRIORKIND)commander-> getManufactorSequency();
    int actIndex = (int) type;
    num = commander->getDataId() ;
    hp = commander-> getWarriorConsumption() ;
    damage = commander->getWarriorDamage();
    Ctime::out();
    cout<<' '<<commander->getName() <<' '<<warrior_string[actIndex]<<" "<<num<<" "<<\
        "born"<<endl; //with strength "<<hp;
    //cout<<','<<commander-> warriorCount[actIndex]<<' '<<warrior_string[actIndex]<<" in "<<commander->name <<" headquarter"<<endl;
    actCity=p;
    sword = nullptr;
    bomb = nullptr;
    arrow = nullptr;
}
CWarrior::~CWarrior() {
    delete sword;
    delete bomb;
    delete arrow;
}
int CWarrior::getHp(){ return hp;}
void CWarrior::addHp(int m){
    hp += m;
}
int CWarrior::getDamage(){
	return this->damage;
}
void CWarrior::setDamage(int damage1) {
	this->damage = damage1;
}
WARRIORKIND CWarrior::getType() {
	return this->type;
}
CCity * CWarrior::getCity() {
    return actCity;
}
void CWarrior::setCity(CCity * city) {
    actCity = city;
}
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
            arrow = new CArrow(this);
        }
        break;
    }
}
CSword * CWarrior::getSword() {
	return this->sword;
}
void CWarrior::setSword(CSword * sword1){
	this->sword = sword1;
}
CBomb * CWarrior::getBomb() {
	return this->bomb;
}
void CWarrior::setBomb(CBomb * bomb1) {
	this->bomb = bomb1;
}
CArrow * CWarrior::getArrow() {
	return this->arrow;
}
void CWarrior::setArrow(CArrow * arrow1) {
	this->arrow = arrow1;
}
bool CWarrior::escape(){
    return false;
}
void CWarrior::marchToCity(CCity * nextCity) {
    actCity =  nextCity;
}
void CWarrior::takeLifeElement(int m){
    commander->addLifeElement(m); //将生命元输送到司令部
}
void CWarrior::shotByArrow(int m){
   hp -= m;
}
int CWarrior::attack(CWarrior *p){
    int dd = getSwordDamage();
    useSword();
    p->hurted(damage+dd);
    if( p->getHp() <= 0 ){

        return -1;//对方被杀死
    }
    else{  //对方没死
        p->fightBack(this);  //对方反击
    }
    if(hp >0) return 0; // 反击己方没死，平局
    else return 1;//反击己方被杀死，对方赢
}
void CWarrior::fightBack(CWarrior *p){
    p->hurted(damage/2 + getSwordDamage());
    useSword();
}
void CWarrior::hurted(int n){
    hp -= n;
}
void CWarrior::cheerUp(){
    return ;
}
bool CWarrior::confiscated(CWarrior *p){
    return false;
}
void CWarrior::nameIdOutput(){
    cout<<commander->getName()<<" "<<warrior_string[type]<<" "<<num;
}
void CWarrior::hpAndForceOutput() {
    cout<<"with "<<hp<<" elements and force "<<damage;
}
//输出样例： 000:35 blue dragon 1 shot
/*表示在 0点35分，编号为1的蓝魔dragon武士射出一支箭。如果射出的箭杀死了敌人，则应如下输出：*/
//000:35 blue dragon 1 shot and killed red lion 4
/*表示在 0点35分，编号为1的蓝魔dragon武士射出一支箭，杀死了编号为4的红魔lion。*/
void CWarrior::useArrow(CWarrior *p){
   if( arrow == nullptr ) return;  //有箭
   arrow->used();  //用箭
   p->shotByArrow(CArrow::getR());  //对方被射伤
   if( arrow->getAvailableTimes() == 0 ) { //使用到了３次
        delete arrow;  //arrow没了
        arrow = nullptr;
   }
   Ctime::out();
   nameIdOutput();
   cout<<" shot ";
   if( p->getHp() <= 0) { //对方被射死
       cout<<"and killed ";
       p->nameIdOutput();
   }
   cout<<endl;
}
//输出样例： 000:38 blue dragon 1 used a bomb and killed red lion 7
//表示在 0点38分，编号为1的蓝魔dragon武士用炸弹和编号为7的红魔lion同归于尽。
bool CWarrior::useBomb(CWarrior *p){
    if(bomb == nullptr) return false;
    //bomb->used();
    //bomb = nullptr;
    actCity = nullptr;
    p->setCity(nullptr);
    //p->setBomb(nullptr); //按说这里是需要设置的，但不影响最终结果
    Ctime::out();
    nameIdOutput();
    cout<<" used a bomb and killed ";
    p->nameIdOutput();
    cout<<endl;
    return true;
}
//勇士使用剑，信息输出在上层,因为有些勇士不用剑，也能攻击
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
int CWarrior::getSwordDamage(){
    return sword == nullptr? 0: sword->getDamage();
}
void CWarrior::earnLifeElement(int m){
    commander->addEarnedLifeElement(m);
}
void CWarrior::lifeElementTransCauseLionDieBattle(int m) {
    hp += m;
}
void CWarrior::weaponNmInfoOutput(){
    if (arrow != nullptr) printf(" arrow(%d),",arrow->getAvailableTimes());
    if( bomb != nullptr) cout<<"bomb,";
    if( sword != nullptr){
        printf("sword(%d)\n",sword->getDamage());
        return;
    }
    cout<<" no weapon"<<endl;
}

CDragon::CDragon(CHeadquator *p):CWarrior(p){
    morale = float( commander->getLifeElement()) /(float)hp ;
    equipWeapon(num);
    cout<<"Its morale is "<<fixed<<setprecision(2)<<morale<<endl;
}
CDragon::~CDragon(){}
//dragon类的战斗逻辑需要考虑杀死敌人，士气增加，未获胜，士气值减少
 int CDragon::attack(CWarrior *p){
    int temp = CWarrior::attack(p);
    if ( temp == -1 ){
        morale +=0.2;
    }
    else morale -= 0.2;  //平局或者被对方杀死
    return temp;
}
 void CDragon::fightBack(CWarrior *p){
    CWarrior::fightBack(p);
    if( p->getHp() <= 0 ) //反击将对方反击死，士气加2
       morale += 0.2;
    else morale -= 0.2 ; //反击未将对方反击死，士气减2
}
//dragon 在一次在它主动进攻的战斗结束后，如果还没有战死，而且士气值大于0.8，就会欢呼
//输出样例：003:40 blue dragon 2 yelled in city 4
void CDragon::cheerUp(){
    if ( morale >(float)  0.8) {
        nameIdOutput();
       cout<<" yelled in city "<< actCity->getNum()<<endl;
    }
}

//CNinja的方法实现
CNinja::CNinja(CHeadquator *p):CWarrior(p){
    equipWeapon(num);
    equipWeapon(num+1);
}
CNinja::~CNinja(){ }
void CNinja::fightBack(CWarrior *p){}

//CIceman的方法实现
CIceman::CIceman(CHeadquator *p):CWarrior(p){
    step = 0;
    equipWeapon(num);
    //cout<<"it has a "<<weaponsname[num%3]<<endl;
}
CIceman::~CIceman(){}
void CIceman::marchToCity(CCity *nextCity){
    actCity = nextCity;
    step++;
    if(step%2 == 0)  //每走两步
    {
        hp -= 9;
        if( hp <= 0 ) hp=1;
        damage += 20;
    }
}
//CLion的方法实现
int CLion::K = 0;
CLion::CLion(CHeadquator *p):CWarrior(p){
          loyalty = commander->getLifeElement()  ;
          cout<<"it's loyalty is "<<loyalty<<endl;
}
CLion::~CLion(){}
/*狮子攻击反击需要考虑的问题：*/
//1.没有武器
//2.战斗未杀死对方情况下，士气减弱Ｋ，这里也分为主动攻击未杀死对方和自己被攻击
//反击的情况下未杀死对方
/*3.被杀死的时候，生命值转移到对方*/
 int CLion::attack(CWarrior *p){
    p->hurted(damage);
    if( p->getHp() <= 0 )  return -1;//对方被杀死
    else {  //对方没死
        p->fightBack(this);  //对方反击
        loyalty -= K;       //　自己的士气减少
    }
    if( hp >0 ) return 0; //反击己方没死，平局
    else return 1; //反击己方被杀死，对方赢
}
void CLion::fightBack(CWarrior *p){
    p->hurted(damage/2); //狮子被攻击，会反击对方
    if( p->getHp() <= 0) return;  //对方被杀死，返回
    else loyalty -= K;   //反击对方没死，狮子经历了一场未胜利的战斗
}
void CLion::hurted(int n){
    hp -= n;
    CWarrior *temp;
    //lion被杀死，生命值转移到对方，但又不包含被射死的情况
    if(hp <= 0){
        temp = actCity->getNewRed();
        if( temp != this)
        {
            //生命值转移到对方
            temp -> lifeElementTransCauseLionDieBattle(hp +n);
            return ;
        }
        else actCity->getNewBlue()->lifeElementTransCauseLionDieBattle(hp +n);
    }
}
//表示在 0点5分，编号为1的蓝魔lion武士逃走
//输出样例： 000:05 blue lion 1 ran away
bool CLion::escape(){
    if ( loyalty <= 0 ) {
        Ctime::out();
        cout<<" ";
        nameIdOutput();
        cout<<" ran away"<<endl;
        actCity = nullptr;
        return true;
    }
    else return false;
}
void CLion::setK(int kk){ K = kk;}

//CWolf方法实现
CWolf::CWolf(CHeadquator *p):CWarrior(p){ }
CWolf::~CWolf(){}
int CWolf::attack(CWarrior *p){
    int temp;
    temp = CWarrior::attack(p);
    if( temp == -1) confiscated(p);
    return temp;
}
void CWolf::fightBack(CWarrior *p){
    CWarrior::fightBack(p);
    if( p->getHp() <= 0) { //对方被反击死，缴获对方武器
        confiscated(p);
    }
}
bool CWolf::confiscated(CWarrior *p){
    CWeapon *temp;
    bool result =  false ;
    if(sword == nullptr && (temp= p->getSword())!= nullptr)  //自己没的才缴获
    {
        sword = (CSword*) temp ;
        p->setSword(nullptr);
        result = true;
    }
    if(arrow == nullptr && (temp= p->getArrow())!= nullptr)  //自己没的才缴获
    {
        arrow = (CArrow*)temp ;
        p->setArrow(nullptr);
        result = true;
    }
    if(bomb == nullptr && (temp= p->getBomb())!= nullptr)  //自己没的才缴获
    {
        bomb = (CBomb *)temp ;
        p->setBomb(nullptr);
        result = true;
    }
   return result;
}

//CCity的方法实现
int CCity::totalNum = 0;
static CCity **City;
CCity::CCity(int m):num(m) {
    lifeElement = 0;
    flag = NOFLAG;
    preFightResult = NOFIGHT;
    actFightResult = NOFIGHT;
    newBlue = nullptr;
    newRed = nullptr ;
    oldRed = nullptr;
    warriorShotByEnemy = nullptr;
}
CCity::~CCity(){}
int CCity::getNum(){ return num;}
void CCity::setNum(int m){num = m;}
int CCity::getLifeElement() {
    return lifeElement;
}
void CCity::setLifeElement(int m) {
	this->lifeElement = m;
}
//在每个小时的第20分：每个城市产出10个生命元。生命元留在城市，直到被武士取走
void CCity::produceLifeElement() {
    lifeElement += 10;
}
//30分不战斗时获取生命元
void  CCity::lifeElementTaken() {
    if( newRed != nullptr && newBlue == nullptr) {  //只有红方武士
        newRed->takeLifeElement(lifeElement); //红方武士取走生命元并传送到司令部
        lifeElement = 0;
    }
    if( newRed == nullptr && newBlue != nullptr) {  //只有蓝方武士
        newBlue->takeLifeElement(lifeElement); //蓝方武士取走生命元并传送到司令部
        lifeElement = 0;
    }
}
void CCity::setFlag(DFlag tfg) {
   flag = tfg;
   //输出样例：004:40 blue flag raised in city 4
   Ctime::out();
   if( flag == REDFLAG ) cout<<"red flag raised in city "<<num<<endl;
   else cout<<"blue flag raised in city "<<num<<endl;
}
void CCity::resetFightResult(){
    actFightResult = NOFIGHT;
}
int CCity::getTotalNum(){ return totalNum;}
void CCity::setTotalNum(int n){ totalNum = n;};
CWarrior * CCity::getNewBlue() {
	return this->newBlue;
}
void CCity::setNewBlue(CWarrior * newblue1) {
	this->newBlue = newblue1;
}
CWarrior * CCity::getNewRed() {
	return this->newRed;
}
void CCity::setNewRed(CWarrior * newred1) {
	this->newRed = newred1;
}
void CCity::setNewRedToOld(){
    oldRed = newRed;
}
void CCity::lionEscape(){
   if( newRed!=nullptr && newRed->escape()==true ){
          newRed = nullptr;
   }
   if(newBlue!=nullptr && newBlue->escape()==true) {
       newBlue = nullptr ;
   }
#ifdef TEST_MODE
   cout<<"city "<<num<<" lion escape "<<endl;
#endif
}
void CCity::march(){  //march只负责将勇士向前推进，不负责记录逻辑
   CCity *temp;
  if( num != totalNum )
      temp = this +1 ;
  else temp = City[num+1] ;
  temp->setNewRedToOld();
  temp->setNewRed(oldRed);
 // 处理cout那些垃圾
  if( newRed != nullptr ) {
      newRed->marchToCity(temp);
      Ctime::out();
      newRed-> nameIdOutput();
      if(num == totalNum)
      {
        cout<<"reached blue headquarter";
      }
      else  cout<<" march to city "<<num+1;
      newRed-> hpAndForceOutput();
      cout<<endl;
  }
  if(num != 1)
      temp = this -1;
  else temp = City[0]  ;
      temp->setNewBlue(newBlue);
 //处理ｃｏｕｔ垃圾
  if( newBlue != nullptr ) {
      newRed->marchToCity(temp);
      Ctime::out();
      newBlue->nameIdOutput();
      if(num == 1) cout<<"reached red headquarter";
      else cout<<" marched to city "<<num-1;
        newRed-> hpAndForceOutput();
      cout<<endl;
  }
#ifdef TEST_MODE
   cout<<"city "<<num<<" march "<<endl;
#endif

}
void CCity::releaseArrow(){
   CWarrior *p;
   //红武士所在城市的右方是蓝军司令部，不需要放箭,因为敌人已经在10分时走掉，
   //但程序上没有写敌人走掉的逻辑，实际上此时程序运行的是有敌人
   if( newRed != nullptr && num != totalNum) //本城市的右方不是敌方司令部
   {
       p = City[num+1]->getNewBlue();  //取得下一步要到达城市的敌人地址
       if( p != nullptr ) newRed->useArrow(p);
   }
   //蓝武士所在城市的左方如果是红军司令部，不需要放箭,因为敌人已经在10分时走掉
   if( newBlue != nullptr && num!= 1) {
       p = City[num-1]->getNewRed(); //取得下一步要走到城市的敌人地址
       if( p != nullptr ) newBlue->useArrow(p);
   }
}
//射箭结果影响到后续缴获武器，旗帜更换等，所以必须要记录在这里
void CCity::recordArrowResult(){
    if ( newRed!= nullptr && newRed->getHp()<= 0 ) { //放箭死
        newRed->setCity(nullptr);
        warriorShotByEnemy = newRed ;
        newRed = nullptr;
        if( newBlue != nullptr ){
            if( newBlue->getHp() <=0 ) //两个都被射死
                actFightResult = BOTHSHOTDEATH;
            else actFightResult = REDSHOTDEATH;
        }
    }
    if (newBlue != nullptr && newBlue->getHp()<= 0 ) {
        newBlue ->setCity(nullptr);
        warriorShotByEnemy = newBlue;
        newBlue = nullptr;
        if( newRed != nullptr) actFightResult = BLUESHOTDEATH;
    }
}

void CCity::bombUsed(){
    int damage,hp;
    if( newRed != nullptr && newBlue != nullptr){  //有两个武士才评估是否使用炸弹
        damage = newBlue->getDamage();
        hp = newRed->getHp();
        //红方武士判断被对方攻击死或者自己攻击被反击死
        if( damage >= hp || damage/2 >= hp){
            if( newRed->useBomb(newBlue) ){
                newRed = nullptr;
                newBlue = nullptr;
                return ;
            }
        }
        damage = newRed->getDamage();
        hp =  newBlue->getHp();
       //蓝方武士判断被对方攻击死或者自己攻击被反击死
        if( damage >= hp || damage/2 >= hp) {
            if( newBlue->useBomb(newRed)) {
                newRed = nullptr;
                newBlue = nullptr;
                return ;
            }
        }
    }
}
void CCity::fight() {
    if( newRed != nullptr && newBlue != nullptr){
        CWarrior *attacker = newRed;
        CWarrior *target = newBlue;
        int reverse1 = -1;
        if( flag == BLUEFLAG || (flag == NOFLAG && num%2 ==0 )) {//蓝方主动攻击
            attacker = newBlue;
            target = newRed ;
            reverse1 =1;
        }
        int k = attacker->attack(target);
        if( reverse1 * k == 0) actFightResult = DRAW;
        else if( reverse1*k == 1) actFightResult = REDWIN;
        else actFightResult = BLUEWIN;
        activeAttackInfoOutput(attacker,target); //主动攻击信息输出
        fightBackInfoOutput(attacker,target); //反击信息输出
        killInfoOutput(); //被杀信息输出
        newRed = actFightResult == BLUEWIN? nullptr:newRed;
        newBlue = actFightResult == REDWIN? nullptr:newBlue;
    }
    //勇士欢呼,条件是自己没死，并且轮到自己主动进攻
    if( newRed != nullptr ){
        if( flag == REDFLAG || (flag == NOFLAG && num%2 ==1 )) newRed->cheerUp();
    }
    if( newBlue != nullptr){
        if( flag == BLUEFLAG || (flag == NOFLAG && num%2 ==0 )) newBlue->cheerUp();
    }
    //处理被剑射死时候的武器缴获,战斗情况下的武器缴获处理包含在attack 函数里
    if(actFightResult == BLUESHOTDEATH){  //蓝武士被杀死，红武士缴获兵器
        newRed->confiscated(warriorShotByEnemy); }
    if(actFightResult == REDSHOTDEATH){   //处理被剑射死时候的武器缴获
        newBlue->confiscated(warriorShotByEnemy); //红武士被射死，蓝武士缴获兵器
    }
    //拿生命元和升旗仪式需要一方胜利
    if( actFightResult == REDWIN || BLUESHOTDEATH){  //红方胜
        //红方武士取走生命元并暂存在司令部的earnedLifElement里
        newRed->earnLifeElement(lifeElement);
        lifeElement = 0;
        if(preFightResult == REDWIN || BLUESHOTDEATH){ //连续两场红方胜
            if( flag == BLUEFLAG || flag == NOFLAG ) setFlag(REDFLAG);
        }
    }
    if( actFightResult == BLUEWIN || actFightResult == REDSHOTDEATH) { //蓝方胜利
        //蓝方武士取走生命元并暂存在司令部的earnedLifElement里
        newBlue->earnLifeElement(lifeElement);
        lifeElement = 0;
        if( preFightResult == BLUEWIN ||preFightResult ==  REDSHOTDEATH) { //蓝方胜利
            if(flag == REDFLAG || flag == NOFLAG ) setFlag(BLUEFLAG);
        }
    }
    //当某个城市有连续两场战斗都是同一方的武士杀死敌人(两场战斗之间如果有
    //若干个战斗时刻并没有发生战斗，则这两场战斗仍然算是连续的；但如果中间
    //有平局的战斗，就不算连续了) ，那么该城市就会插上胜方的旗帜，
    if( actFightResult != NOFIGHT || actFightResult != BOTHSHOTDEATH)
        preFightResult = actFightResult;
}
void CCity::blueWarriorGetPrize(){
    if( actFightResult == BLUEWIN ) {
        newBlue->addHp(8);
    }
}
void CCity::redWarriorGetPrize(){
    if ( actFightResult == REDWIN){
        newRed->addHp(8);
    }
}
void CCity::activeAttackInfoOutput(CWarrior* attacker,CWarrior* target){
    Ctime::out();
    attacker-> nameIdOutput();
    cout<<" attacked ";
    target-> nameIdOutput();
    cout<<" in city "<<num<<" ";
    attacker-> hpAndForceOutput(); cout<<endl;
}
void CCity::fightBackInfoOutput(CWarrior* attacker,CWarrior* target){
    if( target->getHp()<=0) //被主动攻击直接杀死，没有反击
       return ;
    Ctime::out(); target-> nameIdOutput(); cout<<" fight against ";
    attacker->nameIdOutput(); cout<<" in city "<<num<<" "<<endl;
}
void CCity::killInfoOutput(){
    if( actFightResult == REDWIN){
        Ctime::out();
        newRed->nameIdOutput();
       cout<<" was killed in city "<<num<<endl;
    }
    if( actFightResult == BLUEWIN){
        Ctime::out();
        newBlue->nameIdOutput();
       cout<<" was killed in city "<<num<<endl;
    }
}

void CCity::redWarriorReportWeapon(){
    if( newRed == nullptr ) return;
    Ctime::out();
    newRed->nameIdOutput();
    cout<<" has ";
    newRed->weaponNmInfoOutput();
}
void CCity::blueWarriorReportWeapon(){
    if( newBlue == nullptr ) return;
    Ctime::out();
    newBlue->nameIdOutput();
    cout<<" has ";
    newBlue->weaponNmInfoOutput();
}

int CHeadquator::consumption[TOTAL_WARRIOR_KIND]={0};
int CHeadquator::warriorDamage[TOTAL_WARRIOR_KIND]={0};
CHeadquator::CHeadquator(string name1):CCity(0),name(name1){
    haveResourceToProNext = true ;
    act = 0;
    dataId = 0;
    memset(warriorCount,0,sizeof(warriorCount)); //设定初始的计数器为０
    setManufactorSequency();
    for ( int i = 0; i < TOTAL_WARRIOR_KIND; ++i) {
        warriorCountMax[i] = 10; //设定初始的每个指针数组的长度为１０
        warriorP[i] = new CWarrior*[10];
    }
    taken = false;
    arrived = false;
    earnedLifeElement = 0;
    totalMax = 100;
    if(name == "blue") num = totalNum+1;
}
CHeadquator::~CHeadquator(){
    for (unsigned int i = 0; i < TOTAL_WARRIOR_KIND; ++i) {
        for ( int j = 0;  j< warriorCount[i]; ++j) {
            delete warriorP[i][j];
        }
       delete warriorP[i];
    }
}
string& CHeadquator::getName(){ return name;}
int CHeadquator::getDataId(){ return dataId; }
int CHeadquator::getManufactorSequency(){
    return manufactorSequency[act];
}
void CHeadquator::setManufactorSequency(){
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

int CHeadquator:: getWarriorConsumption(){
    return consumption[manufactorSequency[act]];
}
void CHeadquator::setWarriorConsumption(int *cost){
    memcpy(consumption,cost,sizeof(int )*TOTAL_WARRIOR_KIND);
}
int CHeadquator::getWarriorDamage(){
    return warriorDamage[manufactorSequency[act]];
}
void CHeadquator::setWarriorDamage(int *damage){
    memcpy(warriorDamage,damage,sizeof(warriorDamage));
}
bool CHeadquator::getTaken(){ return taken;}
void CHeadquator::setTaken(bool temp){taken = temp;}
bool CHeadquator::getArrived(){ return arrived;}
void CHeadquator::setArrived(bool temp){ arrived = temp;}
void CHeadquator::setNewRedAndNewBlue(){
   /*int i = (act-1+TOTAL_WARRIOR_KIND)%TOTAL_WARRIOR_KIND;*/
   //int actIndex = manufactorSequency[i];
   //if( name == "red"){
       //if( haveResourceToProNext == false) newRed = nullptr;
       //else newRed =  warriorP[actIndex][warriorCount[actIndex]-1];
       //return;
   //}
   //if( haveResourceToProNext == false) newBlue = nullptr;
   /*else newBlue =  warriorP[actIndex][warriorCount[actIndex]-1];*/
}
int CHeadquator:: produceWarriors(){
    WARRIORKIND tempkind ;
    int actIndex;
    //for (unsigned int i = 0; i < 6; ++i) {
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
        if( name == "red") newRed = warriorP[actIndex][warriorCount[actIndex-1]];
        else newBlue = warriorP[actIndex][warriorCount[actIndex-1]];
        act = (act+1)%TOTAL_WARRIOR_KIND ;
        haveResourceToProNext = true;
        return 1;
    }
    if( name == "red" ) newRed = nullptr;
    else newBlue = nullptr;
    //act = (act+1)%TOTAL_WARRIOR_KIND ;
    //}
    haveResourceToProNext = false ;
    //cout<<' '<<name<<" headquarter stops making warriors"<<endl;//
    return -1;
}
void  CHeadquator::lionEscape(){
        if(name == "red") {
            if( newRed != nullptr && newRed->escape() == true)
                newRed  = nullptr;
            return;
        }
        if ( newBlue != nullptr && newBlue->escape() == true )
                         newBlue = nullptr;
}
void CHeadquator::march(){ //march 之前必须保证newRed 和　newBlue是正确的
    CCity *temp;
    if (name == "red" ) {
        temp = City[1];
        temp->setNewRedToOld();
        temp->setNewRed(newRed);
        //处理ｃｏｕｔ
        if(newRed != nullptr)
        {
            newRed->marchToCity(temp);
            Ctime::out();
            newRed-> nameIdOutput();
            cout<<" marched to city 1 ";
            newRed-> hpAndForceOutput();
        }
#ifdef TEST_MODE
         cout<<"red heedQuators in but newRed is nullptr "<<endl;
#endif

        return ;
    }
    if( name == "blue"){
        temp = City[totalNum];
        temp->setNewBlue(newBlue);
        //处理ｃｏｕｔ
        if(newBlue != nullptr)
        {
            newBlue->marchToCity(temp);
            Ctime::out();
            newBlue-> nameIdOutput();
            cout<<" marched to city "<<CCity::getTotalNum()<<" ";
            newBlue-> hpAndForceOutput();
        }
#ifdef TEST_MODE
         cout<<"blue heedQuators in but newBule nullptr "<<endl;
#endif
        return ;
    }
}
void CHeadquator::addEarnedLifeElement(int m){
    earnedLifeElement +=m;
}
void CHeadquator::accquireTrophy(){
    lifeElement += earnedLifeElement;
    earnedLifeElement = 0;
}
void CHeadquator::addLifeElement(int m){
    lifeElement += m;
}
void CHeadquator::reportLifeElement(){
    Ctime::out();
    cout<<" "<<lifeElement<<" elements in "<<name<<" headquaters"<<endl;
}
void dealWithInput(int& M,int& N,int& K,int& R,int& T,int *cost,int *inputDamage){
    cin>>M;
    cin>>N;
    cin>>R;
    cin>>K;
    cin>>T;
    for (unsigned int j = 0; j < TOTAL_WARRIOR_KIND; ++j) {
        cin>>cost[j];
    }

    for (unsigned int j = 0; j < TOTAL_WARRIOR_KIND; ++j) {
        cin>>inputDamage[j];
    }
}

int main(){
    unsigned int dataNum;  //数据测试组数
    //定义参数，用以处理输入参数。例如城市生命源，城市数目等
    int M,N,K,R,T,cost[TOTAL_WARRIOR_KIND],inputDamage[TOTAL_WARRIOR_KIND];
    cin>>dataNum;
    for(unsigned int actcase = 0; actcase< dataNum; actcase++){
        dealWithInput(M,N,K,R,T,cost,inputDamage);
        cout<<"Case "<< actcase + 1 <<":"<<endl;
        CCity::setTotalNum(N);
        CLion::setK(K);
        CArrow::setR(R);
        //Ctime battletime;
        CHeadquator* RedCommand=new CHeadquator("red");
        CHeadquator* BlueCommand = new CHeadquator("blue");
        RedCommand->setLifeElement(M);  //设定城市的初始生命元
        BlueCommand->setLifeElement(M); //同上
        CHeadquator::setWarriorConsumption(cost);    //设定司令部生产消耗
        CHeadquator::setWarriorDamage(inputDamage);  //设定司令部生产武士的攻击力
        City = new CCity*[N+2]; //City指向的内存，存放司令部和城市的对象指针
        City[0] = RedCommand;
        City[N+1] = BlueCommand ;
        CCity *temp = new CCity[N];
        for ( int i = 0; i < N; ++i) {
            City[i+1] =  temp+i; //将城市的指针赋值到 City[N+2]数组里，方便后续写代码
            temp->setNum(i+1);   //设定城市的编号
        }
        while(1)
        {
            //需要reset 所有战斗状态
            //每小时０分事件（武士出生）输出
            if (Ctime::getSecond(0)>T)  break;
            RedCommand->produceWarriors();  //先制造一个武士
            RedCommand->setNewRedAndNewBlue();  //将制造新武士设置为newRed
            BlueCommand->produceWarriors();  //蓝方制造一个武士
            BlueCommand->setNewRedAndNewBlue();  //蓝方制造的武士设置为newblue

            //每小时５分事件（lion逃跑）
            if(Ctime::getSecond(5)>T) break;
            for ( int i = 0; i < N+2 ; ++i)  City[i]->lionEscape();
            cout<<"5 minutes lionescape over"<<endl;
            //１０分事件输出，包含武士前进到某一城市，城市被占领等
            if(Ctime::getSecond(10)>T) break;
            for ( int i = 0; i < N+2; ++i)  City[i]->march();  //所有的武士前进
            //前进后判断是否司令部被占领
            cout<<"ten minutes march over"<<endl;
            if( RedCommand->getNewBlue() != nullptr ){//红方司令部有新到的蓝武士
                //是第一次到达的话，设定到达为真
                if(RedCommand->getArrived() == false)
                    RedCommand->setArrived(true);
                //如果之前已经有武士到达，说明司令部被占领
                else RedCommand->setTaken(true);
            }
            if( BlueCommand->getNewRed() != nullptr){//蓝方司令部有新到的红武士
                //是第一次到达的话，设定到达为真
                if(BlueCommand->getArrived() == false)
                    BlueCommand->setArrived(true);
                //如果之前已经有武士到达，说明司令部被占领　　　
                else BlueCommand->setTaken(true) ;
            }
            if(RedCommand->getTaken() == true || BlueCommand->getTaken() == true)
              break;  //有司令部被占领，则循环终止
            //20分事件（每个城市产生10个生命元）输出
            if( Ctime::getSecond(20) >T) break;
            for ( int i = 0; i < N; ++i)  City[i+1]-> produceLifeElement();

            //30分事件(如果一个城市只有一个武士，武士取走生命元,并输送到司令部)
            if( Ctime::getSecond(30) >T) break;
            for ( int i = 0; i < N; ++i)  City[i+1]->lifeElementTaken();

            //35分事件输出（武士射箭）
            if( Ctime::getSecond(35) >T) break;
            for ( int i = 0; i < N; ++i)  City[i+1]->releaseArrow();
            for ( int i = 0; i < N ; ++i) { //记录射箭结果，方便缴获武器，旗帜更换等
                City[i+1]->recordArrowResult();
            }

            //38分事件输出（武士使用bomb)
            if( Ctime::getSecond(35) >T) break;
            for ( int i = 0; i < N ; ++i)  City[i+1]->bombUsed();

            //40分事件输出，包括主动进攻、反击、战死、欢呼、获取生命元、升旗
             if( Ctime::getSecond(40) >T) break;
            for ( int i = 0; i < N ; ++i)  City[i+1]->fight();
            //如果司令部的生命元不足以奖励所有的武士，则优先奖励距离敌方司令部近的武士。
            for ( int i = 0; i < N ; ++i) {
               if( RedCommand->getLifeElement() <8 ) break;
               City[i+1]->redWarriorGetPrize();
               RedCommand->addLifeElement(-8);
            }
            for ( int i = 0; i < N ; ++i) {
               if( BlueCommand->getLifeElement() <8 ) break;
               City[N-i]->blueWarriorGetPrize();
               BlueCommand->addLifeElement(-8);
            }
            RedCommand->accquireTrophy();  //发放完了奖励后，取得战斗胜利的生命元
            BlueCommand->accquireTrophy();
            for ( int i = 0; i < N ; ++i)  City[i+1]->resetFightResult(); //恢复战斗结果

          //50分司令部报告生命源数量000:50 100 elements in red headquarter
          if( Ctime::getSecond(50)>T) break;
          RedCommand->reportLifeElement();
          BlueCommand->reportLifeElement();

          //55分武士报告武器情况
          if(Ctime::getSecond(55)>T ) break;
          for ( int i = 0; i < N ; ++i) {
              City[i+1]->redWarriorReportWeapon();
          }
          for ( int i = 0; i < N ; ++i) {
              City[i+1]->blueWarriorReportWeapon();
          }
            Ctime::timeincrease();
        }
        delete RedCommand;
        delete BlueCommand;
        delete []temp;
        delete City;
    }
    return 0;
}
