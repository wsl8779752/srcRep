#include "wodetian.h"

using namespace std;

date_time::date_time(int year1,int month1,int date1){
year =year1;
month = month1 ;
date = date1;
};
date_time::date_time(date_time &new_date){

    year = new_date.year;
    month = new_date.month;
    date = new_date.date;
}

wodetian::wodetian(int id1, Gender gender1, date_time new_birthday, char idnum[19]):birthday(new_birthday){

   id=id1;
   gender=gender1;
   strncpy(Id_card_num,idnum,sizeof(Id_card_num));

}

void wodetian::check_inform(){

    cout<<"please enter the id:"<<endl;
    cin >>id;
    cout<<"please enter Gender:";
    cin >>(int&)gender;
    cout<<"please enter Id_num";
    cin >>Id_card_num;
    cout<<"please enter the date:";
    int x,y,z;
    cin >>x>>y>>z;
    birthday.modifiy(x,y,z);

}
void wodetian::show_inform(){

    cout<<"the id is:"<<id<<endl;
    cout<<"the gender is:"<<gender<<endl;
    cout<<"the iden_num is: "<<Id_card_num<<endl;
    birthday.show();
}
