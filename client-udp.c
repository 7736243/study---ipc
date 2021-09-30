#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE 30

int main(int argc, char *argv[]){
    int sock;
    struct sockaddr_in serv_addr, from_addr;
    char message[BUF_SIZE];
    int str_len;
    socklen_t adr_size;

    if(argc!=3){
        printf("%s <IP> <port>\n", argv[0]);
        exit(1);
    }

    // 家南 积己
    sock = socket(PF_INET, SOCK_DGRAM, 0);
    if(sock==-1){
        printf("socket() error\n");
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_addr.s_addr=inet_addr(argv[1]);
    serv_addr.sin_port=htons(atoi(argv[2]));

    while(1){
        fputs("Insert message : ", stdout);
        fgets(message, sizeof(message), stdin); // 皋技瘤 涝仿
        ./*if(message == 'q\n'){
            break;
        }*/
        sendto(sock, message, strlen(message), 0, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
        adr_size = sizeof(from_addr);
        str_len=recvfrom(sock, message, BUF_SIZE, 0, (struct sockaddr*)&from_addr, &adr_size);
        message[str_len]=0;
        printf("Message from server : %s", message);
    }
    close(sock);
    return 0;
}