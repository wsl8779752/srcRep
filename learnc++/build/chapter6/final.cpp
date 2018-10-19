/**
 * @file part4.cpp
 * @brief 
 * @author rensheng946@163.com
 * @version 1.0
 * @date 2018-07-13
 */
#include <cstring>
#include <iostream>
#include <cstdio> 
#include <iomanip> 
using namespace std;
#define TOTAL_WARRIOR_KIND 5
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
    //BOTHSHOTDEATH    
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
        virtual void marchToCity(CCity * nextCity = NULL);
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
        double morale;
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
	CWarrior * oldRed;
private:
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
    CWarrior *getOldRed();
	virtual void lionEscape();
	virtual void march();
    void releaseArrow();
	void recordArrowResult();
	void  bombUsed();
	void fight();
    bool blueWarriorGetPrize();
	bool redWarriorGetPrize();
   /* void activeAttackInfoOutput(CWarrior* attacker,CWarrior* target);*/
	//void fightBackInfoOutput(CWarrior* attacker,CWarrior* target);
	/*void killInfoOutput();*/
    virtual void redWarriorReportWeapon();
    virtual void blueWarriorReportWeapon();
};
class CHeadquator : public CCity {
private:
	string name;
	bool produceResult;
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
    CWarrior *arrivedEnemy;
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
/*    bool getArrived();*/
    /*void setArrived(bool temp);*/
	int produceWarriors();
	virtual void  lionEscape();
	virtual void march();
	void setNewRedAndNewBlue();
	void addEarnedLifeElement(int m);
	void accquireTrophy();
	/** * 在原来的lifeElement 基础上增加m */
	void addLifeElement(int m);
    void reportLifeElement();
    virtual void blueWarriorReportWeapon();
    virtual void redWarriorReportWeapon();
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
    nameIdOutput();
    cout<<" born"<<endl;
    //cout<<' '<<commander->getName() <<' '<<warrior_string[actIndex]<<" "<<num<<" "<<\
        //"born"<<endl; //with strength "<<hp;
    //cout<<','<<commander-> warriorCount[actIndex]<<' '<<warrior_string[actIndex]<<" in "<<commander->name <<" headquarter"<<endl;
    actCity=p;
    sword = NULL;
    bomb = NULL;
    arrow = NULL;    
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
    Ctime::out();
    nameIdOutput();
    if( nextCity->getNum() == CCity::getTotalNum()+1)
        cout<<" reached blue headquarter";
    else if ( nextCity->getNum() == 0 )     
        cout<<" reached red headquarter";
    else  cout<<" marched to city "<<nextCity->getNum() ;
    cout<<" ";
    hpAndForceOutput();
    cout<<endl;
    actCity =  nextCity;
}
void CWarrior::takeLifeElement(int m){
    Ctime::out();
    nameIdOutput();
    cout<<" earned "<<m<<" elements for his headquarter"<<endl;
    commander->addLifeElement(m); //将生命元输送到司令部 
}
void CWarrior::shotByArrow(int m){
   hp -= m;
}
//主动攻击函数，主动攻击方赢返回-1，平局返回0,输返回1
//输出样例：000:40 red iceman 1 attacked blue lion 1 in city 1 with 20 elements
// and force 30
int CWarrior::attack(CWarrior *p){
    int dd = getSwordDamage();
    useSword();
    //攻击信息输出
    Ctime::out();
    nameIdOutput();
    cout<<" attacked ";
    p->nameIdOutput();
    cout<<" in city "<<actCity->getNum()<<" ";
    hpAndForceOutput();
    cout<<endl;  
    p->hurted(damage+dd);
    if( p->getHp() <= 0 ){

        return -1;//对方被杀死,己方赢，返回-1 
    }  
    else{  //对方没死
        p->fightBack(this);  //对方反击
    }
    if(hp >0) return 0; // 反击己方没死，平局，返回0
    else return 1;//反击己方被杀死，对方赢，返回1
}
void CWarrior::fightBack(CWarrior *p){
    //反击信息输出
    Ctime::out();
    nameIdOutput();
    cout<<" fought back against ";
    p->nameIdOutput();
    cout<<" in city "<<actCity->getNum()<<endl;
    p->hurted(damage/2 + getSwordDamage()); 
    useSword();
}
void CWarrior::hurted(int n){
    hp -= n;
    if( hp  <= 0) {
        Ctime::out();
        nameIdOutput();
        cout<<" was killed in city "<<actCity->getNum()<<endl; 
    }
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
   if( arrow == NULL ) return;  //无箭
   arrow->used();  //有箭用箭
   p->shotByArrow(CArrow::getR());  //对方被射伤 
   if( arrow->getAvailableTimes() == 0 ) { //使用到了３次
        delete arrow;  //arrow没了
        arrow = NULL;
   }
   Ctime::out();
   nameIdOutput();
   cout<<" shot";
   if( p->getHp() <= 0) { //对方被射死
       cout<<" and killed "; 
       p->nameIdOutput();
   }
   cout<<endl;
}
//输出样例： 000:38 blue dragon 1 used a bomb and killed red lion 7
//表示在 0点38分，编号为1的蓝魔dragon武士用炸弹和编号为7的红魔lion同归于尽。
bool CWarrior::useBomb(CWarrior *p){
    if(bomb == NULL) return false;
    //bomb->used(); 
    //bomb = NULL;
    actCity = NULL;
    p->setCity(NULL); 
    //p->setBomb(NULL); //按说这里是需要设置的，但不影响最终结果
    Ctime::out();
    nameIdOutput();
    cout<<" used a bomb and killed ";
    p->nameIdOutput();      
    cout<<endl;
    return true;
}
//勇士使用剑，信息输出在上层,因为有些勇士不用剑，也能攻击
void CWarrior::useSword(){
    if( sword == NULL) return;
    else {
        sword->used();
        if( sword->getDamage() <= 0){
            delete sword;
            sword = NULL;
        } 
    } 
}
int CWarrior::getSwordDamage(){
    return sword == NULL? 0: sword->getDamage(); 
}
void CWarrior::earnLifeElement(int m){
    Ctime::out();
    nameIdOutput();
    cout<<" earned "<<m<<" elements for his headquarter"<<endl;
    commander->addEarnedLifeElement(m); 
}
void CWarrior::lifeElementTransCauseLionDieBattle(int m) {
    hp += m;
}
void CWarrior::weaponNmInfoOutput(){
    Ctime::out();
    nameIdOutput();
    cout<<" has ";
    if( arrow || bomb || sword ){
        if (arrow != NULL) printf("arrow(%d)",arrow->getAvailableTimes());  
        if( bomb != NULL) {
            if( arrow != NULL) cout<<",";
            cout<<"bomb";
        }   
        if( sword != NULL){
            if( bomb != NULL || arrow!= NULL) cout<<",";
            printf("sword(%d)",sword->getDamage()); 
        }
        cout<<endl;
    }
    else
        cout<<"no weapon"<<endl;
}

CDragon::CDragon(CHeadquator *p):CWarrior(p){
    morale = double( commander->getLifeElement()) /(double)hp ;
    equipWeapon(num);
    //printf("Its morale is %.2f\n",morale);
    cout<<"Its morale is "<<fixed<<setprecision(2)<<morale<<endl;
}
CDragon::~CDragon(){}
//dragon类的战斗逻辑需要考虑杀死敌人，士气增加，未获胜，士气值减少
//主动攻击结束后，没有战死，士气>0.8 就会欢呼
 int CDragon::attack(CWarrior *p){
    int temp = CWarrior::attack(p);
    if ( temp == -1 ){
        morale +=0.2;
    }
    else morale -= 0.2;  //平局或者被对方杀死
    if( temp != 1) cheerUp();  //在一次主动攻击后，没死
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
    if ( morale >0.8) { 
        Ctime::out();
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
    step++;
    if(step%2 == 0)  //每走两步
    {
        hp -= 9;
        if( hp <= 0 ) hp=1;
        damage += 20;
    }    
    CWarrior::marchToCity(nextCity); //先参数改变，再输出信息
}
//CLion的方法实现
int CLion::K = 0;
CLion::CLion(CHeadquator *p):CWarrior(p){
          loyalty = commander->getLifeElement()  ; 
          cout<<"Its loyalty is "<<loyalty<<endl;
}
CLion::~CLion(){}
/*狮子攻击反击需要考虑的问题：*/
//1.没有武器
//2.战斗未杀死对方情况下，士气减弱Ｋ，这里也分为主动攻击未杀死对方和自己被攻击
//反击的情况下未杀死对方
/*3.被杀死的时候，生命值转移到对方*/
 int CLion::attack(CWarrior *p){
     int temp = CWarrior::attack(p);
     if(temp != -1 ) loyalty -= K; //主动攻击，对方没死，经历了异常未获胜的战斗
     return temp;
}
void CLion::fightBack(CWarrior *p){
    CWarrior::fightBack(p);
    if( p->getHp() > 0) //反击对方没死，狮子经历了一场未胜利的战斗，忠诚度减少
        loyalty -= K;   
}   
void CLion::hurted(int n){
    CWarrior::hurted(n);  
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
        //cout<<" ";
        nameIdOutput();        
        cout<<" ran away"<<endl;
        actCity = NULL;
        return true; 
    }
    else 
        return false; 
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
    if(sword == NULL && (temp= p->getSword())!= NULL)  //自己没的才缴获 
    {
        sword = (CSword*) temp ;
        p->setSword(NULL);
        result = true;
    }
    if(arrow == NULL && (temp= p->getArrow())!= NULL)  //自己没的才缴获 
    {
        arrow = (CArrow*)temp ;
        p->setArrow(NULL);
        result = true;
    }
    if(bomb == NULL && (temp= p->getBomb())!= NULL)  //自己没的才缴获 
    {
        bomb = (CBomb *)temp ;
        p->setBomb(NULL);
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
    newBlue = NULL;
    newRed = NULL ;
    oldRed = NULL;
    warriorShotByEnemy = NULL;
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
    if( newRed != NULL && newBlue == NULL) {  //只有红方武士
        newRed->takeLifeElement(lifeElement); //红方武士取走生命元并传送到司令部
        lifeElement = 0;
    }
    if( newRed == NULL && newBlue != NULL) {  //只有蓝方武士
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
CWarrior *CCity::getOldRed(){ 
    return oldRed; 
} 
void CCity::lionEscape(){
   if( newRed!=NULL && newRed->escape()==true ){
          newRed = NULL;
   }  
   if(newBlue!=NULL && newBlue->escape()==true) { 
       newBlue = NULL ; 
   } 
#ifdef TEST_MODE
   cout<<"city "<<num<<" lion escape "<<endl;
#endif 
}
void CCity::march(){
    oldRed = newRed;
    newRed = City[num-1]->getOldRed();
    if( newRed != NULL) newRed->marchToCity(this);
    newBlue = City[num+1]->getNewBlue();
    if( newBlue != NULL) newBlue->marchToCity(this);    
}
void CCity::releaseArrow(){
   CWarrior *p; 
   //红武士所在城市的右方是蓝军司令部，不需要放箭,因为敌人已经在10分时走掉，
   //但程序上没有写敌人走掉的逻辑，实际上此时程序运行的实际状态是有敌人
   //后续在中秋节后第一天写了加上敌人走掉的逻辑，但是这里有敌人的逻辑不更新了
   if( newRed != NULL && num != totalNum) //本城市的右方不是敌方司令部
   {
       p = City[num+1]->getNewBlue();  //取得下一步要到达城市的敌人地址
       if( p != NULL ) newRed->useArrow(p); 
   }  
   //蓝武士所在城市的左方如果是红军司令部，不需要放箭,因为敌人已经在10分时走掉
   if( newBlue != NULL && num!= 1) {
       p = City[num-1]->getNewRed(); //取得下一步要走到城市的敌人地址
       if( p != NULL ) newBlue->useArrow(p); 
   }
}
//射箭结果影响到后续缴获武器，旗帜更换等，所以必须要记录在这里
//另外的一个问题是，由于相邻的敌人可以用箭射死对方，在一个地点无法预知下一个
//地点的敌人是否会用箭射死自己，所以必须先输出射死，在这里记录newRed 或者
//newBLue = NULL的逻辑
// 这里记录战斗结果的逻辑如下：
// 1.没发生射击，NOFIGHT 
// 2.在无敌人的情况下被射死，NOFIGHT
// 3.有敌人的情况下被射死，分为两种情况：
// a两个都被射死---BOTHSHOTDEATH
// b一个被射死---REDSHOTTODEATH或者BLUESHOTTODEATH
// 4.发生了射击，但没有人被射死 NOFIGHT
void CCity::recordArrowResult(){
    //城市在被射之前整个城市无人，当然NOFIGHT 
    if( newRed == NULL && newBlue == NULL) return ;
    //城市在被射之前只有newRed一人的情况，NOFIGHT
    if( newRed != NULL && newBlue == NULL){
       // newRed在无人的情况下被射死，NOFIGHT
        if(newRed->getHp() <= 0) newRed = NULL;
        //这里没写的else相对应的在无人的情况下没被射死或者没被射，还是NOFIGHT
        return; 
    }
    //城市在被射之前只有newBlue一人的情况，NOFIGHT
    if( newBlue != NULL && newRed == NULL){ 
        //newBlue在无人的情况下被射死，NOFIGHT
        if(newBlue->getHp() <= 0) newBlue = NULL;
        return;  
    }
    //剩下的情况是被射之前城市有两个武士
    if( newBlue->getHp() <=0 ){ //蓝武士被射死 
        warriorShotByEnemy  = newBlue;
        newBlue = NULL;
        if( newRed ->getHp() <= 0) {//红武士也被射死，NOFIGHT
            newRed = NULL;
            return;
        } 
        //红武士没被射死
        actFightResult = BLUESHOTDEATH;
        return;
    }  
    if( newRed->getHp() <= 0) //红武士被射死 
    {
        //这里不存在蓝武士被射死的情况，因为有这种情况在之前已经return了，只存
        //在红武士被射死的情况
        warriorShotByEnemy = newRed;
        newRed = NULL;
        actFightResult = REDSHOTDEATH;
    }
    /*//newRed在经过release放箭后，生命值不大于0，说明被射死*/
    //if ( newRed!= NULL && newRed->getHp()<= 0 ) { 
        //newRed->setCity(NULL);
        //warriorShotByEnemy = newRed ;
        //newRed = NULL;
        //if( newBlue != NULL ){  //有敌人存在
            //if( newBlue->getHp() <=0 ) //两个都被射死 
                //actFightResult = BOTHSHOTDEATH;
            //else actFightResult = REDSHOTDEATH;
        //} //这里如果newBlue ==NULL，那么实际上就是没人的地方武士被射死，
       ////这种情况什么（包括旗帜更换，武士拿生命元，武士获得奖励等）也不会发生
       ////所以等同与战斗结果NOFIGHT  
    //}     
    //if (newBlue != NULL && newBlue->getHp()<= 0 ) { 
        //newBlue ->setCity(NULL);
        //warriorShotByEnemy = newBlue;
        //newBlue = NULL;  
        //if( newRed != NULL) actFightResult = BLUESHOTDEATH;
    /*}*/ 
}
//评估是否使用炸弹
void CCity::bombUsed(){
    int warriorDamage,swordDamage,hp;
    if( newRed != NULL && newBlue != NULL){  //有两个武士才评估是否使用炸弹
        CWarrior *attacker = newRed;
        CWarrior *target = newBlue;
        if( flag == BLUEFLAG || (flag == NOFLAG && num%2 ==0 )) {//蓝方主动攻击 
            attacker = newBlue;
            target = newRed ;
        }
        warriorDamage = attacker->getDamage();
        swordDamage = attacker->getSwordDamage() ;
        hp = target->getHp();  
        if( warriorDamage+swordDamage >= hp ){   //主动攻击者直接杀死目标
            //底层判断武士是否有炸弹，有使用，返回真，否则返回假
            if( target->useBomb(attacker) ){  
                newRed = NULL;
                newBlue = NULL;
            }
            return ;
        }  
        //else//主动攻击没有杀死对方，对方反击
        if( target->getType() != NINJA )  //NINJA挨打了也不反击
        {
            warriorDamage = target->getDamage()/2;
            swordDamage = target->getSwordDamage();
            hp = attacker->getHp();
            if( warriorDamage+swordDamage >= hp ){
                if( attacker->useBomb(target) == true){ 
                    newRed = NULL;
                    newBlue = NULL;
                    return  ;
                } 
            }  

        }
    }    
}
void CCity::fight() {
    if( newRed != NULL && newBlue != NULL){//只有两个武士的情况下才会战斗
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
        newRed = actFightResult == BLUEWIN? NULL:newRed;
        newBlue = actFightResult == REDWIN? NULL:newBlue;
    }
    //处理被剑射死的欢呼
    if( actFightResult == BLUESHOTDEATH){ 
        if( flag == REDFLAG || (flag == NOFLAG && num%2 ==1 )) newRed->cheerUp(); 
    }
    if( actFightResult == REDSHOTDEATH){
        if( flag == BLUEFLAG || (flag == NOFLAG && num%2 ==0 )) newBlue->cheerUp(); 
    } 
    //处理被箭射死情况下武器缴获,战斗情况下的武器缴获处理包含在attack 函数里
    if(actFightResult == BLUESHOTDEATH){  //蓝武士被杀死，红武士缴获兵器
        newRed->confiscated(warriorShotByEnemy); }
    if(actFightResult == REDSHOTDEATH){   //处理被剑射死时候的武器缴获
        newBlue->confiscated(warriorShotByEnemy); //红武士被射死，蓝武士缴获兵器
    }
    //拿生命元和升旗仪式需要一方胜利
    if( actFightResult == REDWIN || actFightResult == BLUESHOTDEATH){  //红方胜
        //红方武士取走生命元并暂存在司令部的earnedLifElement里
        newRed->earnLifeElement(lifeElement);
        lifeElement = 0; 
        if(preFightResult == REDWIN || preFightResult == BLUESHOTDEATH){ //连续两场红方胜
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
    //个人觉得如果两方都被箭射死，也算平局
    //武士使用bomb和敌人同归于尽的情况下，不算是一场战斗，双方都不能拿走城市
    //的生命元，也不影响城市的旗帜。
    //总结以上，只有NO FIGHT 、使用炸弹、或者箭未射死任何一方不影响旗帜，其他
    //情况需要将战斗结果记录到prefightResult里
    if( actFightResult != NOFIGHT ) 
        preFightResult = actFightResult;
}
//疑问对手被射死，获得不获得生命值奖励
//通过答案分析，获得生命值奖励
bool CCity::blueWarriorGetPrize(){
    if( actFightResult == BLUEWIN || actFightResult== REDSHOTDEATH ) {
        newBlue->addHp(8);
        return true;
    }
    return false;
}
bool CCity::redWarriorGetPrize(){
    if ( actFightResult == REDWIN || actFightResult== BLUESHOTDEATH ){
        newRed->addHp(8);
        return true;
    }
    return false;
}
/*void CCity::activeAttackInfoOutput(CWarrior* attacker,CWarrior* target){*/
    //Ctime::out();
    //attacker-> nameIdOutput(); 
    //cout<<" attacked ";
    //target-> nameIdOutput();
    //cout<<" in city "<<num<<" ";
    //attacker-> hpAndForceOutput(); cout<<endl;
//}
//void CCity::fightBackInfoOutput(CWarrior* attacker,CWarrior* target){
    //if( target->getHp()<=0) //被主动攻击直接杀死，没有反击
       //return ;
    //Ctime::out(); target-> nameIdOutput(); cout<<" fight against "; 
    //attacker->nameIdOutput(); cout<<" in city "<<num<<" "<<endl;
//}
//void CCity::killInfoOutput(){
    //if( actFightResult == REDWIN){
        //Ctime::out();
        //newBlue->nameIdOutput();
       //cout<<" was killed in city "<<num<<endl; 
    //}
    //if( actFightResult == BLUEWIN){
        //Ctime::out();
        //newRed->nameIdOutput();
       //cout<<" was killed in city "<<num<<endl; 
    //}
/*}*/

void CCity::redWarriorReportWeapon(){
    if( newRed == NULL ) return;
    newRed->weaponNmInfoOutput();     
}
void CCity::blueWarriorReportWeapon(){
    if( newBlue == NULL ) return;
    newBlue->weaponNmInfoOutput();     
}

int CHeadquator::consumption[TOTAL_WARRIOR_KIND]={0};
int CHeadquator::warriorDamage[TOTAL_WARRIOR_KIND]={0};
CHeadquator::CHeadquator(string name1):CCity(0),name(name1){
    produceResult = false ;
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
    arrivedEnemy = NULL;
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
//002:10 red headquarter was taken
void CHeadquator::setTaken(bool temp){
    taken = temp;
    Ctime::out();
    cout<<name<<" headquarter was taken"<<endl; 
}
/*bool CHeadquator::getArrived(){ return arrived;}*/
////设置司令部到达状态，如果有地方武士到达的话，将到达的敌方武士地址
////记录在arrivedEnemy变量里，方便55分输出武器
////为什么不将到达命令在这里处理的原因是已经在march里处理了
//void CHeadquator::setArrived(bool temp){ 
    //arrived = temp;
    //if (arrived == true) { 
        //if( name == "red") arrivedEnemy = newBlue;
        //else arrivedEnemy = newRed;
    //} 
/*}*/

void CHeadquator::setNewRedAndNewBlue(){
   int i = (act-1+TOTAL_WARRIOR_KIND)%TOTAL_WARRIOR_KIND;
   int actIndex = manufactorSequency[i];
   if( name == "red"){
       if( produceResult == false) newRed = NULL;                
       else newRed =  warriorP[actIndex][warriorCount[actIndex]-1];
       return;
   }
   else{
       if( produceResult == false) newBlue = NULL;                
       else newBlue =  warriorP[actIndex][warriorCount[actIndex]-1];
   }
}
//勇士排列顺序： DRAGON NINJA ICEMAN LION WOLF
//对应的数字：    0      1     2      3    4
int CHeadquator:: produceWarriors(){
    WARRIORKIND tempkind ;
    int actIndex;
    //act从0开始往4增加，按照在headquators设置好的制造顺序，得到当前应该制造的
    //武士种类,例如:act = 0时，红方司令部会得到
    //manufactorSequancy[act] = ICEMAN而蓝方会得到LION
    actIndex = manufactorSequency[act] ;      
    tempkind=(WARRIORKIND) actIndex;
    if( lifeElement >= consumption[tempkind])
    {
        dataId += 1;
        warriorCount[actIndex]++; //分类计数的勇士计数器
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
        /*if( name == "red") newRed = warriorP[actIndex][warriorCount[actIndex]-1];*/
        /*else newBlue = warriorP[actIndex][warriorCount[actIndex]-1];*/
        act = (act+1)%TOTAL_WARRIOR_KIND ;
        produceResult = true;
        return 1;
    }
    /*if( name == "red" ) newRed = NULL;*/
    /*else newBlue = NULL;*/
    //act = (act+1)%TOTAL_WARRIOR_KIND ;
    //}
    produceResult = false ;
    //cout<<' '<<name<<" headquarter stops making warriors"<<endl;//
    return -1;  
}
void  CHeadquator::lionEscape(){
        if(name == "red") { 
            if( newRed != NULL && newRed->escape() == true)
                newRed  = NULL;               
            return;
        } 
        if ( newBlue != NULL && newBlue->escape() == true )
            newBlue = NULL; 
}
/*if( RedCommand->getNewBlue() != NULL ){//红方司令部有新到的蓝武士*/
////是第一次到达的话，设定到达为真
//if(RedCommand->getArrived() == false)
//RedCommand->setArrived(true);  
////如果之前已经有武士到达，说明司令部被占领
//else RedCommand->setTaken(true);
/*}*/ 
/*if( BlueCommand->getNewRed() != NULL){//蓝方司令部有新到的红武士*/
////是第一次到达的话，设定到达为真
//if(BlueCommand->getArrived() == false)
//BlueCommand->setArrived(true);
////如果之前已经有武士到达，说明司令部被占领　　　
//else BlueCommand->setTaken(true) ;   
/*}*/ 
void CHeadquator::march(){ //march 之前必须保证newRed 和　newBlue是正确的
    if (name == "red" ) {
        oldRed = newRed;
        newRed = NULL;
        newBlue = City[num+1]-> getNewBlue();
        if(newBlue != NULL) {
            newBlue->marchToCity(this); 
            arrivedEnemy = newBlue;
            if( arrived == false ) {
                arrived = true;
                return;
            }    
            setTaken(true);
        }    
    }
    if( name == "blue"){
        newBlue = NULL;
        newRed = City[num-1]->getOldRed();
        if (newRed != NULL) {
            newRed-> marchToCity(this); 
            arrivedEnemy = newRed;
            if( arrived == false){
                arrived = true;
                return;
            }
            setTaken(true);
        }
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
    cout<<lifeElement<<" elements in "<<name<<" headquarter"<<endl;
}
void CHeadquator::redWarriorReportWeapon(){
    if( name == "blue" && arrivedEnemy != NULL)
    {   
        arrivedEnemy->weaponNmInfoOutput(); 
    }
}
void CHeadquator::blueWarriorReportWeapon(){
    if(name == "red" && arrivedEnemy != NULL){
        arrivedEnemy->weaponNmInfoOutput();
    }
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
        Ctime::resettime();
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
            temp[i].setNum(i+1);   //设定城市的编号
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
            //cout<<"5 minutes lionescape over"<<endl;        
            //１０分事件输出，包含武士前进到某一城市，城市被占领等
            if(Ctime::getSecond(10)>T) break; 
            for ( int i = 0; i < N+2; ++i)  City[i]->march();  //所有的武士前进
            //cout<<"ten minutes march over"<<endl;
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
            //记录射箭结果，方便缴获武器，旗帜更换等
            for ( int i = 0; i < N ; ++i)  City[i+1]->recordArrowResult(); 

            //38分事件输出（武士使用bomb),
            //这里存在的问题是评估死是否要带上武器的攻击力
            if( Ctime::getSecond(38) >T) break;
            for ( int i = 0; i < N ; ++i)  City[i+1]->bombUsed(); 

            //40分事件输出，包括主动进攻、反击、战死、欢呼、获取生命元、升旗
            if( Ctime::getSecond(40) >T) break;
            for ( int i = 0; i < N ; ++i)  City[i+1]->fight(); 
            //如果司令部的生命元不足以奖励所有的武士，则优先奖励距离敌方司令部近的武士。
            //遗留问题，对手被射死的武士获得不获得生命值奖励
            for ( int i = 0; i < N ; ++i) { //红方按N~1的顺序奖励
                if( RedCommand->getLifeElement() <8 ) break;  
                if(City[N-i]->redWarriorGetPrize() == true) 
                    RedCommand->addLifeElement(-8); 
            } 
            for ( int i = 0; i < N ; ++i) { //蓝方按1-N的顺序奖励
                if( BlueCommand->getLifeElement() <8 ) break;  
                if( City[i+1]->blueWarriorGetPrize() == true) 
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
            for ( int i = 0; i < N+2 ; ++i) { 
                City[i]->redWarriorReportWeapon(); 
            } 
            for ( int i = 0; i < N+2 ; ++i) { 
                City[i]->blueWarriorReportWeapon(); } 
            Ctime::timeincrease();
        }    
        delete RedCommand;
        delete BlueCommand;
        delete []temp;
        delete City;
    }
    return 0;
}
