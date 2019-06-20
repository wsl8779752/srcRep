#include <string>
#include <cmath>
#include <iostream>
using namespace std;

/******保存帐号类***************************************************************************************/
class SavingAccount{

private:

    int id,lastdate;
    double balance;
    double rate;
    double accumulation;
    void record(int date,double account);



public:

    SavingAccount( int newid,double newrate,int lastDate );
    int getID() { return id ; }
    double getBalance() { return balance ; };
    double getRate() { return rate ; }
    void show();
    void deposit( int date, double account );
    void withdraw( int date, double amount );
    void settle( int date );


};

SavingAccount::SavingAccount(int newid,double newrate,int lastDate):id(newid),lastdate(lastDate),balance(0),rate(newrate),accumulation(0)
{
    cout<<"id:"<<id<<"  at date:"<<lastdate<<" is created"<< endl;
};

/*************显示帐号信息的共用方法**************************/
void SavingAccount::show(){
    cout<<"id:"<<id;
    cout<<"  balance:"<<balance<<endl;
}

/*************存钱方法**************************************/
void SavingAccount::deposit(int date ,double amount){

    record(date,amount);
}
/**************记录帐号信息，该方法保存一个日均余额*************/
void SavingAccount::record(int date, double amount){

    accumulation+=(date-lastdate)*balance;
    balance += amount;
    lastdate = date;
    cout<<"id:"<<id<<'\t'<<"date:"<<date<<'\t'<<amount<<'\t'<<balance<<endl;
}
/***************取钱方法************************************/
void SavingAccount::withdraw(int date, double amount){
    if(balance<amount)
        cout<<"not enough money"<<endl;
    else
        record(date, amount);
}
/**************计算利息*************************************/
void SavingAccount::settle(int date){

    accumulation+=(date-lastdate)*balance;
    double amount1 = accumulation/365*rate;
    balance+=amount1;
    cout<<"id:"<<id<<'\t'<<"date:"<<date<<'\t'<<amount1<<'\t'<<balance<<endl;
}
int main(){

    /*
    SavingAccount wei (123456,0.0035,1);
    wei.deposit(1,10000);
    wei.settle(366);
    wei.show();
    */
    SavingAccount sa0(121325302,0.015,1);
    sa0.deposit(5,5000);
    sa0.deposit(45,5500);
    sa0.settle(90);
    sa0.show(); cout<<endl;
    return 0;

}
