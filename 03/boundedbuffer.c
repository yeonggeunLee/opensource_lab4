#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define BUFFER_SIZE 20
#define NUMITEMS 30

#define NUM_PRODUCERS 2
#define NUM_CONSUMERS 2

typedef struct {
    int item[BUFFER_SIZE];
    int totalitems;
    int in, out;
    pthread_mutex_t mutex;
    pthread_cond_t full;
    pthread_cond_t empty;
} buffer_t;

buffer_t bb = { {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 0, 0, 0,
    PTHREAD_MUTEX_INITIALIZER,
    PTHREAD_COND_INITIALIZER,
    PTHREAD_COND_INITIALIZER};

int produce_item () {
    int item = (int) (100.0*rand()/(RAND_MAX+1.0));
    sleep((unsigned long) (5.0*rand()/(RAND_MAX+1.0)));
    printf("produce_item: item=%d\n", item);
    return item;
}

insert_item (int item) {
    int status;
    
    status = pthread_mutex_lock (&bb.mutex);
    if (status != 0)
        return status;
    
    while (bb.totalitems >= BUFFER_SIZE && status == NULL)
        status = pthread_cond_wait (&bb.empty, &bb.mutex);
    if (status != 0) {
        pthread_mutex_unlock(&bb.mutex);
        return status;
    }
    
    bb.item[bb.in] = item;
    bb.in = (bb.in + 1) % BUFFER_SIZE;
    bb.totalitems++;

    if (status = pthread_cond_signal(&bb.full)) {
        pthread_mutex_unlock (&bb.mutex);
        return status;
    }
    return pthread_mutex_unlock (&bb.mutex);
}

consume_item (int item) {
    sleep((unsigned long) (5.0*rand()/(RAND_MAX+1.0)));
    printf("\t\tconsume_item: item=%d\n", item);
}

remove_item (int *temp) {
    int status;
    status = pthread_mutex_lock (&bb.mutex);
    if (status != 0)
        return status;
    
    while (bb.totalitems <= 0 && status == NULL)
        status = pthread_cond_wait (&bb.full, &bb.mutex);
    if (status != 0) {
        pthread_mutex_unlock(&bb.mutex);
        return status;
    }
    
    *temp = bb.item[bb.out];
    bb.out = (bb.out + 1) % BUFFER_SIZE;
    bb.totalitems--;
    if (status = pthread_cond_signal(&bb.empty)) {
        pthread_mutex_unlock (&bb.mutex);
        return status;
    }
    return pthread_mutex_unlock (&bb.mutex);
}

void * producer(void *arg) {
    int item;
    while (1) {
        item = produce_item ();
        insert_item(item);
    }
}

void * consumer(void *arg) {
    int item;
    while (1) {
        remove_item (&item);
        consume_item (item);
    }

}

int main () {
    int status;
    void *result;

    pthread_t producer_tid[NUM_PRODUCERS], consumer_tid[NUM_CONSUMERS];
    for (int i = 0; i < NUM_PRODUCERS; i++) {
        pthread_create(&producer_tid[i], NULL, producer, NULL);
    }
    for (int i = 0; i < NUM_CONSUMERS; i++) {
        pthread_create(&consumer_tid[i], NULL, consumer, NULL);
    }
    
    status = pthread_create (&producer_tid, NULL, producer, NULL);
    if (status != 0)
        perror ("Create producer thread");
    status = pthread_create (&consumer_tid, NULL, consumer, NULL);
    if (status != 0)
        perror ("Create consumer thread");
    status = pthread_join (producer_tid, NULL);
    if (status != 0)
        perror ("Join producer thread");
    status = pthread_join (consumer_tid, NULL);
    if (status != 0)
        perror ("Join consumer thread");
}
