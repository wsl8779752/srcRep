#include <add.h>
#include <common.h> 
#include <fun.h> 
#include <stdio.h> 
#include <xdefine.h> 

int main(int argc, char *argv[])
{
    printf("this is Add printing>>add(1,0):%d,add(2,0):%d\n",add(1,0),add(2,0));
    common_print(); 
    printf("this is main print name:%s\n",MYNAME);
    return 0;
}

