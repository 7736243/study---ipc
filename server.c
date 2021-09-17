#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){
    int serv_sock;
    int clnt_sock;

    struct sockaddr_in serv_addr;
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size;

    char message[]="hello client !";

    if(argc!=2){
        printf("%s <port>\n", argv[0]);
        exit(1);
    }

    // 소켓 생성
    serv_sock = socket(PF_INET, SOCK_STREAM, 0); 
    if(serv_sock==-1){
        printf("socket() error\n");
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
    serv_addr.sin_port=htons(atoi(argv[1]));

    // 소켓 바인딩
    if(bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr))==-1){ 
        printf("bind() error\n");
    }

    // 소켓을 통해 들어오는 연결 듣기(성공 시 0, 오류 시 -1 반환)
    if(listen(serv_sock, 5)==-1){
        printf("listen() error\n");
    }

    clnt_addr_size=sizeof(clnt_addr);
    // 연결 수락
    clnt_sock=accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);
    if(clnt_sock==-1){
        printf("accept() error\n");
    }

    write(clnt_sock, message, sizeof(message));
    close(clnt_sock);
    close(serv_sock);
    return 0;
}