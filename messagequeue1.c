#include <stdio.h>
#include <sys/msg.h>
#include <string.h>
#include <stdlib.h>

// 메세지 버퍼로 사용할 구조체 정의
// 메세지를 저장할 배열의 크기 -> 송수신할 메세지의 크기에 따라 조절
typedef struct mymsgbuf{
    long mtype;
    char mtext[80];
}   MyMsgBuf;

int main(void){
    key_t key;
    int msgid;
    MyMsgBuf mesg;

    key = ftok("keyfile", 1); // 키 정의
    msgid = msgget(key, IPC_CREAT|0644); // 메세지 식별자 생성
    if(msgid==-1){
        perror("msgget");
        exit(1);
    }
    // 전송할 메세지 버퍼 설정
    mesg.mtype=1; // 메세지 유형 = 1
    strcpy(mesg.mtext, "Message Q Test\n"); // 메세지 버퍼의 배열에 문자열 복사

    // 메세지 전송
    if(msgsnd(msgid, (void *)&mesg, 80, IPC_NOWAIT)==-1){
        perror("msgsnd");
        exit(1);
    }
    return 0;
}