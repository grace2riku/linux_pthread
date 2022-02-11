#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define DATA_SIZE   10000000
#define THREADS     10
// DATASIZEはTHREADSの整数倍であると過程している

int data[DATA_SIZE];

// pthread_getspecificなどで使うキー番号
pthread_key_t startIndexKey;
pthread_key_t endIndexKey;

// ランダムな数でdataの内容を初期化する
void setRandomData(){
    int i;

    for (i = 0; i < DATA_SIZE; i++) {
        data[i] = rand();
    }
}

// 一定範囲のデータの中の最大値を求める
int getMax() {
    // スレッドローカル変数を読み取る
    size_t startIndex = (size_t)pthread_getspecific(startIndexKey);
    size_t endIndex = (size_t)pthread_getspecific(endIndexKey);

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

    // スレッドローカル変数をセット
    pthread_setspecific(startIndexKey, (void*)((DATA_SIZE / THREADS) * n));
    pthread_setspecific(endIndexKey, (void*)((pthread_getspecific(startIndexKey) + (DATA_SIZE / THREADS) - 1)));

    int max = getMax();
    return (void*)max; 
}

int main(void) {
    pthread_t threads[THREADS];
    int res[THREADS];
    int i, max;

    srand(time(NULL));
    setRandomData();

    // スレッドローカル変数を用意する
    pthread_key_create(&startIndexKey, NULL);
    pthread_key_create(&endIndexKey, NULL);

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