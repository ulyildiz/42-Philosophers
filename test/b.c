#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *thread_func(void *arg) {
    printf("Merhaba, Ben bir thread'im!\n");
    pthread_exit(NULL);
}

int main() {
    pthread_t tid;
    pthread_attr_t attr; 

    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    if (pthread_create(&tid, &attr, thread_func, NULL) != 0) {
        fprintf(stderr, "Thread oluşturma hatası\n");
        return 1;
    }
    pthread_attr_destroy(&attr);
    printf("Ana program devam ediyor...\n");
    return 0;
}