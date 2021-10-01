#include <stdio.h>
#include <sys/msg.h>
#include <string.h>
#include <stdlib.h>

// �޼��� ���۷� ����� ����ü ����
// �޼����� ������ �迭�� ũ�� -> �ۼ����� �޼����� ũ�⿡ ���� ����
typedef struct mymsgbuf{
    long mtype;
    char mtext[80];
}   MyMsgBuf;

int main(void){
    key_t key;
    int msgid;
    MyMsgBuf mesg;

    key = ftok("keyfile", 1); // Ű ����
    msgid = msgget(key, IPC_CREAT|0644); // �޼��� �ĺ��� ����
    if(msgid==-1){
        perror("msgget");
        exit(1);
    }
    // ������ �޼��� ���� ����
    mesg.mtype=1; // �޼��� ���� = 1
    strcpy(mesg.mtext, "Message Q Test\n"); // �޼��� ������ �迭�� ���ڿ� ����

    // �޼��� ����
    if(msgsnd(msgid, (void *)&mesg, 80, IPC_NOWAIT)==-1){
        perror("msgsnd");
        exit(1);
    }
    return 0;
}