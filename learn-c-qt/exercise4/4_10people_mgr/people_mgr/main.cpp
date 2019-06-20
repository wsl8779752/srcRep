#include "wodetian.h"
#include <iostream>
#include <stdio.h>

int main(){

   date_time new_birthday(1992,2,3);
   date_time my_birthday;
   char id_num[19]="342425198610122415";
   wodetian wei(2,female,new_birthday, id_num);
   wei.show_inform();
   wei.check_inform();
   wei.show_inform();

   return 0;

}
