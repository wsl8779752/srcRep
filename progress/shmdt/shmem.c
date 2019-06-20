#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h> 
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <sys/wait.h> 
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
    pid_t pid;
    int shmid;
    char *shm_addr = 0;
    char flag1[]="WROTE";
    char buff[20];
    if( (shmid =  shmget(IPC_PRIVATE,1024,0666)) ==-1){ //创建一片共享内存
        perror( "share memory error\n");
       exit(1); 
    }
    else { 
        printf("share memory is created.\n"); 
    } 
    system("ipcs -m");
    pid = fork(); 
    if (pid<0) { 
        perror( "Fork error occured\n");  
    } 
    else if (pid == 0) { //子进程
        if ((shm_addr = shmat(shmid,0,0))== (char *)(-1)) { 
            perror( "shmat error\n");  
            exit(1);
        } 
        else { 
            printf("Child:Attach shared-memory:%p\n",shm_addr ); 
        } 
        system("ipcs -m");
        while( strncmp(shm_addr,flag1,strlen(flag1))){
            printf("Child:Wait for enable data...\n");
            sleep(5);
        }
        strcpy(buff,shm_addr+strlen(flag1));
        printf("Chilad:Shared-meory:%s\n",buff);
        if(shmdt(shm_addr)==-1){  //解除共享内存映射
            perror("shmdt");
            exit(1);
        }
        else{
            printf("Child: Deattach shared-memory:\n");
        }
        system( "ipcs -m");   //报告此时进程间的通信机制状态 
        if( shmctl(shmid,IPC_RMID,NULL)==-1){ 
            perror( "child:shmctl(IPC_RMID\n");
            exit(1);  
        }  
        else{
            printf("Delete shared-memory\n");
        }
        system( "ipcs -m"); 
    } 
    else { 
        if((shm_addr = shmat(shmid,0,0))==-1){ 
            perror( "Parent: shmat error\n");
            exit(1);  
        }       
        else { 
            printf("Parent Attached  memory shared:%p\n",shmid); 
        } 
        sleep(1);

        printf("\n Input some string:\n");
        fgets(buff,1024,stdin);
        strncpy(shm_addr+strlen(flag1),buff,strlen(buff));
        strncpy(shm_addr,flag1,strlen(flag1));
        if( shmdt(shm_addr)==-1){
            perror("Parent:shmdt");
            exit(1);
        } 
        else{ 
            printf("Parent:Detached shared memory\n"); 
        } 
        system("ipcs -m");
        waitpid(pid,NULL,0);
        printf("Finished\n");
    } 
    exit(0);
}
