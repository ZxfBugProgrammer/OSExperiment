#include <errno.h>
#include <fcntl.h>
#include <linux/sem.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#define MAXSEM 5
//声明三个信号灯 ID
int fullid;
int emptyid;
int mutxid;
int main() {
    struct sembuf P, V;
    union semun arg;
    //声明共享主存
    int *array;
    int *sum;
    int *set;
    int *get;
    //映射共享主存
    array = (int *)mmap(NULL, sizeof(int) * MAXSEM, PROT_READ | PROT_WRITE,
                        MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    sum = (int *)mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE,
                      MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    get = (int *)mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE,
                      MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    set = (int *)mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE,
                      MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    *sum = 0;
    *get = 0;
    *set = 0;
    //生成信号灯
    fullid = semget(IPC_PRIVATE, 1, IPC_CREAT | 00666);
    emptyid = semget(IPC_PRIVATE, 1, IPC_CREAT | 00666);
    mutxid = semget(IPC_PRIVATE, 1, IPC_CREAT | 00666);
    //为信号灯赋值
    arg.val = 0;
    if (semctl(fullid, 0, SETVAL, arg) == -1) perror("semctl setval error");
    arg.val = MAXSEM;
    if (semctl(emptyid, 0, SETVAL, arg) == -1) perror("semctl setval error");
    arg.val = 1;
    if (semctl(mutxid, 0, SETVAL, arg) == -1) perror("setctl setval error");
    //初始化 P,V 操作
    V.sem_num = 0;
    V.sem_op = 1;
    V.sem_flg = SEM_UNDO;
    P.sem_num = 0;
    P.sem_op = -1;
    P.sem_flg = SEM_UNDO;
    //生产者进程
    if (fork() == 0) {
        int i = 0;
        while (i < 100) {
            semop(emptyid, &P, 1);
            semop(mutxid, &P, 1);
            array[*(set) % MAXSEM] = i + 1;
            printf("Producer %d\n", array[(*set) % MAXSEM]);
            (*set)++;
            semop(mutxid, &V, 1);
            semop(fullid, &V, 1);
            i++;
        }
        sleep(15);
        printf("Producer is over\n");
        exit(0);
    } else {
        // ConsumerA 进程
        if (fork() == 0) {
            while (1) {
                if (*get == 100) break;
                semop(fullid, &P, 1);
                semop(mutxid, &P, 1);
                *sum += array[(*get) % MAXSEM];
                printf("The ComsumerA Get Number %d\n", array[(*get) % MAXSEM]);
                (*get)++;
                if (*get == 100) printf("The sum is %d \n ", *sum);
                semop(mutxid, &V, 1);
                semop(emptyid, &V, 1);
                sleep(1);
            }
            printf("ConsumerA is over\n");
            exit(0);
        } else {
            // Consumer B 进程
            while (1) {
                if (*get == 100) break;
                semop(fullid, &P, 1);
                semop(mutxid, &P, 1);
                *sum += array[(*get) % MAXSEM];
                printf("The ComsumerB Get Number %d\n", array[(*get) % MAXSEM]);
                (*get)++;
                if (*get == 100) printf("The sum is %d \n ", *sum);
                semop(mutxid, &V, 1);
                semop(emptyid, &V, 1);
                sleep(1);
            }
            printf("ConsumerB is over\n");
            exit(0);
        }
    }
    return 0;
}
