#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define DATA_SIZE   10000000
#define THREADS     10
// DATASIZEはTHREADSの整数倍であると過程している

int data[DATA_SIZE];

// ランダムな数でdataの内容を初期化する
void setRandomData(){
    int i;

    for (i = 0; i < DATA_SIZE; i++) {
        data[i] = rand();
    }
}

// 一定範囲のデータの中の最大値を求める
int getMax(size_t startIndex, size_t endIndex) {
    int max = data[startIndex];
    size_t index;

    for (index = startIndex+1; index <= endIndex; index++) {
        if (max < data[index]){
            max = data[index];
        }
    }
    return max;
}

// 各スレッドのエントリー関数
void* threadFunc(void* arg) {
    int n = (int)arg;   // スレッド番号
    size_t startIndex = (DATA_SIZE / THREADS) * n;
    size_t endIndex = startIndex + (DATA_SIZE / THREADS) - 1;
    int max = getMax(startIndex, endIndex);
    return (void*)max; 
}

int main(void) {
    pthread_t threads[THREADS];
    int res[THREADS];
    int i, max;

    srand(time(NULL));
    setRandomData();

    // スレッドをTHREADS個作り、並列に処理を開始させる
    for (i = 0; i < THREADS; i++) {
        if (pthread_create(&threads[i], NULL, threadFunc, (void*)i) != 0) {
            printf("Error: Failed to create new thread.\n");
            exit(1);
        }
    }

    // 各スレッドの処理が完了するのを待つ
    for (i = 0; i < THREADS; i++) {
        if (pthread_join(threads[i], (void**)&res[i]) != 0) {
            printf("Error: Failed to wait for the thread termination.\n");
            exit(1);
        }
    }

    // 全スレッドの処理結果から最大値を探す
    max = res[0];
    for (i = 1; i < THREADS; i++) {
        printf("threads[%d] Max value is %d\n", i, max);
        if (max < res[i]) {
            if (max < res[i])
                max = res[i];
        }
    }

    printf("Max value is %d\n", max);

    return 0;
}