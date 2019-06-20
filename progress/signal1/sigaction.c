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
    struct sigaction action;
    printf("Waiting for signal SIGINT or SIGQUIT...\n");
    action.sa_handler=myfun;
    sigemptyset(&action.sa_mask);
    action.sa_flags = SA_RESETHAND;
    sigaction(SIGINT,&action,0);
    sigaction(SIGQUIT,&action,0);
    printf("the first pause\n");
    pause();
    /*signal(SIGINT,SIG_IGN);*/
    /*signal(SIGQUIT,myfun);*/
    pause();
    exit(0);
}
