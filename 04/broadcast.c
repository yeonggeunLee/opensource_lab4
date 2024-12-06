#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

#define NUM_CLIENTS 5
#define MAX_MESSAGE_LENGTH 100
#define QUEUE_SIZE 10

typedef struct {
    char messages[QUEUE_SIZE][MAX_MESSAGE_LENGTH];
    int front;
    int rear;
    int count;
} MessageQueue;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_var = PTHREAD_COND_INITIALIZER;

MessageQueue message_queue = {{0}, 0, 0, 0};

void enqueue_message(const char *msg) {
    strncpy(message_queue.messages[message_queue.rear], msg, MAX_MESSAGE_LENGTH);
    message_queue.rear = (message_queue.rear + 1) % QUEUE_SIZE;
    message_queue.count++;
}

void dequeue_message(char *msg) {
    strncpy(msg, message_queue.messages[message_queue.front], MAX_MESSAGE_LENGTH);
    message_queue.front = (message_queue.front + 1) % QUEUE_SIZE;
    message_queue.count--;
}

void *client_thread(void *arg) {
    int client_id = *(int *)arg;
    char client_message[MAX_MESSAGE_LENGTH];

    snprintf(client_message, MAX_MESSAGE_LENGTH, "클라이언트의 메시지 %d", client_id);

    pthread_mutex_lock(&mutex);
    while (message_queue.count == QUEUE_SIZE) {
        pthread_cond_wait(&cond_var, &mutex);
    }
    
    enqueue_message(client_message);
    printf("클라이언트 - %d: 서버에 메시지 전송!\n", client_id);

    pthread_cond_signal(&cond_var);
    pthread_mutex_unlock(&mutex);

    return NULL;
}

void *server_thread(void *arg) {
    char msg[MAX_MESSAGE_LENGTH];

    while (1) {
        pthread_mutex_lock(&mutex);

        while (message_queue.count == 0) {
            pthread_cond_wait(&cond_var, &mutex);
        }

        dequeue_message(msg);
        printf("서버 - Broadcasting message: '%s'\n", msg);

        pthread_cond_signal(&cond_var);
        pthread_mutex_unlock(&mutex);
    }

    return NULL;
}

int main() {
    pthread_t server_tid;
    pthread_t client_tids[NUM_CLIENTS];
    int client_ids[NUM_CLIENTS];

    if (pthread_create(&server_tid, NULL, server_thread, NULL) != 0) {
        perror("서버 쓰레드 생성 실패");
        exit(1);
    }

    for (int i = 0; i < NUM_CLIENTS; i++) {
        client_ids[i] = i + 1;
        if (pthread_create(&client_tids[i], NULL, client_thread, &client_ids[i]) != 0) {
            perror("클라이언트 쓰레드 생성 실패");
            exit(1);
        }
        usleep(100000);
    }

    for (int i = 0; i < NUM_CLIENTS; i++) {
        pthread_join(client_tids[i], NULL);
    }

    pthread_cancel(server_tid);
    pthread_join(server_tid, NULL);

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond_var);

    return 0;
}
