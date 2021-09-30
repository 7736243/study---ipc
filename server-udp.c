#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE 30

int main(int argc, char *argv[]){
    int serv_sock;
    int str_len;
    struct sockaddr_in serv_addr, clnt_addr;
    socklen_t clnt_addr_size;
    char message[BUF_SIZE];

    if(argc!=2){
        printf("%s <port>\n", argv[0]);
        exit(1);
    }

    // 家南 积己
    serv_sock = socket(PF_INET, SOCK_DGRAM, 0); 
    if(serv_sock==-1){
        printf("socket() error\n");
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
    serv_addr.sin_port=htons(atoi(argv[1]));

    // 家南 官牢爹
    if(bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr))==-1){ 
        printf("bind() error\n");
    }

    while(1){
        clnt_addr_size = sizeof(serv_addr);
        str_len=recvfrom(serv_sock, message, BUF_SIZE, 0, (struct sockaddr*)&clnt_addr, &clnt_addr_size);
        sendto(serv_sock, message, str_len, 0, (struct sockaddr*)&clnt_addr, clnt_addr_size);
    }
    close(serv_sock);
    return 0;
}