#include <stdio.h>
#include <sys/msg.h>
#include <string.h>
#include <stdlib.h>

// �޼��� ���۷� ����� ����ü ����
// �޼����� ������ �迭�� ũ�� -> �ۼ����� �޼����� ũ�⿡ ���� ����
typedef struct mymsgbuf{
    long mtype;
    char mtext[80];
}   mymsgbuf;

int main(void){
    mymsgbuf inmsg;
    key_t key;
    int msgid, len;

    key = ftok("keyfile", 1); // Ű ����
    if((msgid=msgget(key, 0))<0){
        // msgget�� �ι�° ���ڸ� 0���� ���� -> ���� �޼��� ť�� �ĺ��� ����
        perror("msgget");
        exit(1);
    }

    // �޼��� �о��
    // ����ũ�� 80 ����, ť�� ����� ��� ��ٸ����� ����
    len=msgrcv(msgid, &inmsg, 80, 0, 0); 
    printf("Received Msg = %s, Len = %d\n", inmsg.mtext, len); 

    return 0;
}