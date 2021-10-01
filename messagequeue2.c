#include <stdio.h>
#include <sys/msg.h>
#include <string.h>
#include <stdlib.h>

// 메세지 버퍼로 사용할 구조체 정의
// 메세지를 저장할 배열의 크기 -> 송수신할 메세지의 크기에 따라 조절
typedef struct mymsgbuf{
    long mtype;
    char mtext[80];
}   mymsgbuf;

int main(void){
    mymsgbuf inmsg;
    key_t key;
    int msgid, len;

    key = ftok("keyfile", 1); // 키 생성
    if((msgid=msgget(key, 0))<0){
        // msgget의 두번째 인자를 0으로 지정 -> 기존 메세지 큐의 식별자 리턴
        perror("msgget");
        exit(1);
    }

    // 메세지 읽어옴
    // 버퍼크기 80 지정, 큐가 비었을 경우 기다리도록 지정
    len=msgrcv(msgid, &inmsg, 80, 0, 0); 
    printf("Received Msg = %s, Len = %d\n", inmsg.mtext, len); 

    return 0;
}