#include <unistd.h> // 파이프 함수 존재함
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAX_BUF 1024
#define READ 0
#define WRITE 1

int main(){
    int fd[2]; // fd[0]은 읽기용 파이프, fd[1]은 쓰기용 파이프
    pid_t pid;
    char buf[MAX_BUF];

    //파이프 호출 성공시 0 반환, 아니면 -1 반환
    if(pipe(fd)<0){ 
        printf("pipe error !\n"); 
        exit(1);
    }

    if((pid=fork())<0){ 
        printf("fork error !\n");
        exit(1);
    }

    if(pid>0){
        // 자식 프로세스는 Write할꺼기에 Read fd는 닫아줌
        close(fd[READ]); 
        strcpy(buf, "message from parent\n");
        write(fd[WRITE], buf, strlen(buf));
    }

    else{
        // 부모 프로세스는 Read할꺼기에 Write fd는 닫아줌
        close(fd[WRITE]); 
        read(fd[READ], buf, MAX_BUF); // pipe에서 메세지 읽기
        printf("child got message : %s\n", buf);
    }

    exit(0);
}