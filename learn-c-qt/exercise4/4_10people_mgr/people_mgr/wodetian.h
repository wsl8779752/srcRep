#ifndef WODETIAN_H
#define WODETIAN_H
#include <string.h>
#include <stdio.h>
#include <iostream>
using namespace std;

enum Gender {
    male,
    female
} ;

class date_time{

private:
    int year,month,date;
public:
    date_time(int ,int ,int);
    date_time(){
        year=1992;
        month=3;
        date=4;
    }

    date_time(date_time & new_date);

    void show(){
       // cout<<"the date is:"<<endl;
        cout<<"the birthday is:"<<year<<" "<<month<<" "<<date;
    }
    void modifiy(int x,int y,int z){
        year = x;
        month = y;
        date = z;
    }


};

class wodetian
{

private:
    int id;
    Gender gender;
    date_time birthday;
    char Id_card_num[19];

public:
    wodetian(int id, Gender gender , date_time new_birthday, char idnum[19] );
    void check_inform();
    void show_inform();
    ~wodetian(){};

};



#endif // WODETIAN_H
