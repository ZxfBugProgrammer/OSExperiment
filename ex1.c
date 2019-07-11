#include <ctype.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

pthread_mutex_t f_mutex;  //互斥信号量
int count = 0;            //计数变量

void *pthread_function_countWord(void *arg)  //第一个子线程
{
    FILE *fp;  //文件指针
    char ch, prech;
    char *fileName = (char *)arg;
    fp = fopen(fileName, "r");
    if (!fp) {
        perror(fileName);
        return NULL;
    }
    prech = '\0';
    while ((ch = fgetc(fp)) != EOF)  //以字符为单位读文件
    {
        if (!isalnum(ch) && isalnum(prech)) {
            // TEST
            printf("%s WORKING!!!   %c %c\n", fileName, ch, prech);
            pthread_mutex_lock(&f_mutex);
            count++;
            pthread_mutex_unlock(&f_mutex);
        }
        prech = ch;
    }
    if (isalnum(prech)) {
        pthread_mutex_lock(&f_mutex);
        count++;
        pthread_mutex_unlock(&f_mutex);
    }
    fclose(fp);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Need two file!\n");
        exit(EXIT_FAILURE);
    }
    pthread_t a, b;
    int res;
    res = pthread_mutex_init(&f_mutex, NULL);  //初始化临界区
    if (res != 0) {
        perror("Mutex initialization failed\n");
        exit(EXIT_FAILURE);
    }
    //创建第一个子线程
    res = pthread_create(&a, NULL, pthread_function_countWord, argv[1]);
    if (res != 0) {
        perror("Thread1 creation failed\n");
        exit(EXIT_FAILURE);
    }
    //创建第二个子线程
    res = pthread_create(&b, NULL, pthread_function_countWord, argv[2]);
    if (res != 0) {
        perror("Thread2 creation failed\n");
        exit(EXIT_FAILURE);
    }
    res = pthread_join(a, NULL);  //等待第一个线程结束
    if (res != 0) {
        perror("Thread1 join failed\n");
        exit(EXIT_FAILURE);
    }
    res = pthread_join(b, NULL);  //等待第二个线程结束
    if (res != 0) {
        perror("Thread2 join failed\n");
        exit(EXIT_FAILURE);
    }
    printf("There have %d words in two files\n", count);  //父线程运行结束
    pthread_mutex_destroy(&f_mutex);
    return 0;
}
