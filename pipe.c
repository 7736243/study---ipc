#include <unistd.h> // ������ �Լ� ������
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAX_BUF 1024
#define READ 0
#define WRITE 1

int main(){
    int fd[2]; // fd[0]�� �б�� ������, fd[1]�� ����� ������
    pid_t pid;
    char buf[MAX_BUF];

    if(pipe(fd)<0){ //������ ȣ�� ������ 0 ��ȯ, �ƴϸ� -1 ��ȯ
        printf("pipe error !\n"); 
        exit(1);
    }
    if((pid=fork())<0){ 
        printf("fork error !\n");
        exit(1);
    }

    if(pid>0){
        close(fd[READ]); // �ڽ� ���μ����� Write�Ҳ��⿡ Read fd�� �ݾ���
        strcpy(buf, "message from parent\n");
        write(fd[WRITE], buf, strlen(buf));
    }
    else{
        close(fd[WRITE]); // �θ� ���μ����� Read�Ҳ��⿡ Write fd�� �ݾ���
        read(fd[READ], buf, MAX_BUF); // pipe���� �޼��� �б�
        printf("child got message : %s\n", buf);
    }
    exit(0);
}