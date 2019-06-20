#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


#define DELAY_TIME 3

union semun{
    int val;
    struct semid_ds *buff;
    unsigned short *array;
};
int semP(int semId);
int semV(int semId);
int del_sem(int semId);
int main(int argc, char *argv[])
{
    
    pid_t result;
    int kk;
    union semun tem;
    tem.val = 0; 
    kk = semget(ftok(".",'a'),1,0666|IPC_CREAT);
    if(semctl(kk,0,SETVAL,0)==-1){
        perror( "semaphore init error") ;
        exit(1);
    }
    result = fork();
    if (result ==-1) {
       perror( "error fork\n");  
       exit(1);
    } 
    else if ( result == 0) { 
        printf("I am son progress ,and I am goint to sleep\n");
        sleep(5);
        printf("I am son and I waked up\n");
        if(semV(kk) == -1) exit(1);
    } 
    else { 
        if(semP(kk)==-1){
            exit(1);    
        }
        printf("I am fatehr progreess, and I will wait for son\n"); 
        if(semV(kk) ==-1) exit(1);
        del_sem(kk);
    } 
    return 0;
}
int semP(int semId){ 
    struct sembuf semB;
    semB.sem_num = 0;
    semB.sem_op = -1;
    semB.sem_flg=SEM_UNDO;
    if (semop(semId,&semB,1)==-1) { 
        perror("P operation");
        return -1;
    } 
    return 0;
}
int semV(int semId){ 
    struct sembuf semB;
    semB.sem_num = 0;
    semB.sem_op = 1;
    semB.sem_flg=SEM_UNDO;
    if (semop(semId,&semB,1)==-1) { 
        perror("V operation");
        return -1;
    } 
    return 0;
}  
int del_sem(int semId){ 
    if( semctl(semId,0,IPC_RMID,0)==-1){ 
        perror( "Delete semaphore") ; 
        return -1;
    }  
    return 0;
}  
