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
int  main()
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
    while(1) { 
        printf("Enter some message to queue:%d",qid);
        if (fgets(msg.msgText,BUFFER_SIZE,stdin)==0 ){ 
            puts( "no message");
            exit(1);  
        } 
        /* 将发送的消息类型设置韦但钱进程的进程号×*/
        msg.msgType = getpid();
        if (msgsnd(qid,&msg,strlen(msg.msgText),0)<0) { 
            perror( "message posted error");
            exit(1);  
        } 
        if (strncmp(msg.msgText,"quit",4)==0) { 
           break;
        }  
    } 
}
