#include "add.h" 
#include <add1.h> 
#include <add2.h> 

int add(int type,int i){
    if( type ==1){
       return add1(i);
    }
    if ( type ==2) return add2(i);
}
