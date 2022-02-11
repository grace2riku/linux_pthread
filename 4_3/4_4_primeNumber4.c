#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N_THREAD 1000

#define MAX_PRIME_NUMBERS 100000

int primeNumber[MAX_PRIME_NUMBERS];
int nPrimeNumber;
int usingPrimeNumber;

int isPrimeNumber(int m) {
    int i;
    for (i = 0; i < nPrimeNumber; i++) {
        if (m % primeNumber[i] == 0) {
            return 0;
        }
    }
    return 1;
}

void microSleep() {
    struct timespec ts;
    ts.tv_sec = 0;
    ts.tv_nsec = 1000;
    nanosleep(&ts, NULL);
}

int countPrimeNumber(int n) {
    int i;

    while (usingPrimeNumber)
        microSleep();
    usingPrimeNumber = 1;

    nPrimeNumber = 0;

    for (i = 2; i <= n; i++) {
        if (isPrimeNumber(i)) {
            if (nPrimeNumber >= MAX_PRIME_NUMBERS) {
                printf("Oops, too many prime numbers.\n");
                exit(1);
            }
            primeNumber[nPrimeNumber] = i;
            nPrimeNumber++;
        }
    }
    i = nPrimeNumber;

    usingPrimeNumber = 0;
    return i;
}


void* threadFunc(void* arg) {
    int n = (int)arg;
    int x;

    x = countPrimeNumber(n);
//    if (x != 25) { // 100以下の素数の数
    if (x != 168) { // 1000以下の素数の数
        printf("Number of prime numbers under %d is %d\n", n, x);
    }

    return NULL;
}


int main() {
    pthread_t threads[N_THREAD];
    int i;

    usingPrimeNumber = 0;

    for (i = 0; i < N_THREAD; i++) {
//        if (pthread_create(&threads[i], NULL, threadFunc, (void*)100) != 0) { // 100以下の素数
        if (pthread_create(&threads[i], NULL, threadFunc, (void*)1000) != 0) {   // 1000以下の素数
            printf("Can't create thread (%d)\n", i);
            exit(1);
        }
    }

    for (i = 0; i < N_THREAD; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Done\n");

    return 0;
}