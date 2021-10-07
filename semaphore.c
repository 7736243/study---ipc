#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

//세마포터 공용체 정의
union semun{
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

int initsem(key_t semkey){
    union semun semunarg;
    int status=0, semid;
    
    // 인자로 받은 키를 지정해 세마포어 식별자 생성
    // 리턴값 -1, errnoe값 EEXIST -> 이미 존재하는 세마포어 식별자(기존 식별자 읽어옴)
    semid=semget(semkey, 1, IPC_CREAT|IPC_EXCL|0600);
    if(semid==-1){
        if(errno==EEXIST){
            semid=semget(semkey, 1, 0);
        }
    }
    else{
        semunarg.val=1;
        status = semctl(semid, 0, SETVAL, semunarg);
    }

    if(semid==-1 || status==-1){
        perror("initsem");
        return (-1);
    }
    return semid;
}

int semlock(int semid){
    struct sembuf buf;

    // sem_op 값을 -1로 설정 -> 공유 자원 얻고  잠금 기능 수행
    // 처음 함수 호출 시 세마포어 값에서 1 빼면 0 -> 잠금 기능 수행
    buf.sem_num = 0;
    buf.sem_op = 1;
    buf.sem_flg = SEM_UNDO; // 문제 발생시 동작 취소
    if(semop(semid, &buf, 1)==-1){
        perror("semunlock failed");
        exit(1);
    }
    return 0;
}

int semunlock(int semid){
    struct sembuf buf;

    // sem_op값을 1로 설정 -> 사용중인 공유 자원의 잠금 기능 해제하고 되돌려줌
    // 처음 함수 호출 시 세마포어 값 0 -> 1 더하면 세마포어 값 양수가 되고 잠금 해제
    buf.sem_num=0;
    buf.sem_op=1;
    buf.sem_flg=SEM_UNDO; // 문제 발생시 동작 취소
    if(semop(semid, &buf, 1)==-1){
        perror("semunlock failed\n");
        exit(1);
    }
    return 0;
}

// 세마포어 생성 및 잠금 수행 -> 작업 수행한 뒤 잠금 해제
void semhandle(){
    int semid;
    pid_t pid = getpid();

    if((semid=initsem(1))<0)    exit(1);

    semlock(semid); // 잠금

    printf("Lock Process : %d\n", (int)pid);
    printf("** Lock Mode : Critical Section\n");

    //sleep(1);
    printf("Unlock Process : %d\n", (int)pid);

    semunlock(semid); // 해제

    exit(0);
}

// fork 함수를 3번 호출 -> 자식 프로세스 3개 생성
// 각 자식 프로세스들이 semhandle() 함수 실행
int main(void){
    int a;
    for(a=0;a<3;a++){
        if(fork()==0)   semhandle();
    }
    return 0;
}