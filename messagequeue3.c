#include <stdio.h>
#include <sys/msg.h>
#include <stdlib.h>

int main(void){
    key_t key;
    int msgid;

    key = ftok("keyfile", 1); // 키 생성
    msgid = msgget(key, IPC_CREAT|0644);
    if(msgid==-1){
        perror("msgget");
        exit(1);
    }

    printf("Before IPC_RMID\n");
    system("ipcs -q");

    // 메세지 큐 식별자를 IPC_RMID 명령으로 제거
    msgctl(msgid, IPC_RMID, (struct msqid_ds *)NULL);
    printf("After IPC_RMID\n");
    system("ipcs -q");

    return 0;
}