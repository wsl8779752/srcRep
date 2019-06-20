#include <signal.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
void myfun(int signNo)
{
   if (signNo == SIGINT ) { 
    printf("I have get SIGINT\n");
   }
   else if (signNo == SIGQUIT) { 
       printf("I have get SIGQUIT\n");
   } 
}

int main(int argc, char *argv[])
{
    printf("Waiting for signal SIGINT or SIGQUIT...\n");
    signal(SIGINT,myfun);
    signal(SIGQUIT,myfun);
    pause();
    exit(0);

}
