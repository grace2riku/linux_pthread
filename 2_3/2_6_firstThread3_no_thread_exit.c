#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void *threadFunc(void* arg) {
    int n = (int)arg;
    int i;

    for (i = 0; i < n;i++){
        printf("I'm threadFunc: %d\n", i);
        sleep(1);
    }
    return NULL;
}


int main(int argc, char* argv[]){
    pthread_t thread;
    int n, i;

    if (argc > 1)
        n = atoi(argv[1]);
    else
        n = 1;

    if(pthread_create(&thread, NULL, threadFunc, (void*)n) != 0){
        printf("Error: Faild to createb new thread.\n");
        exit(1);
    }

    for (i = 0; i < 5; i++) {
        printf("I'm main: %d\n", i);
        sleep(1);
    }

    printf("Bye.\n");

    return 0;
}