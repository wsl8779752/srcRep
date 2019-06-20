#include <sys/types.h> 
#include <sys/ipc.h> 
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h> 

#define BUFFER_SIZE 512
struct message{ 
    long msgType;
   char msgText[BUFFER_SIZE]; 
}; 
int  main(int argc, char *argv[])
{
    key_t key;
    int qid;
    struct message msg;
    key = ftok(".",'a');
    if( key == -1){ 
        perror( "ftork\n");
        exit(1); 
    }  
    qid = msgget(key,IPC_CREAT|0666);
    if( qid == -1) { 
        perror( "error msgget\n");  
        exit(1);
    } 
    printf("Open queue %d\n",qid );
    do { 
        memset(msg.msgText,0,BUFFER_SIZE);
        if (msgrcv(qid,(void *)&msg,BUFFER_SIZE,0,0)<0) { 
            perror("msgrcv");
            exit(1);
        } 
        printf("the message form process %ld :%s and form quene:%d\n",msg.msgType,msg.msgText,qid);
    } while (strncmp(msg.msgText,"quit",4)); 
    printf("I will remove the queue %d from kernel!\n\n",qid );
    if ( msgctl(qid,IPC_RMID,NULL)<0) { 
        perror("msgctl error\n");
        exit(1);
    } 
    return 0;
}
