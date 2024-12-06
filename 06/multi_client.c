#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 3490
#define MAXDATASIZE 100

void *receive_messages(void *sock) {
    int csock = *(int *)sock;
    char buf[MAXDATASIZE];
    int numbytes;

    while (1) {
        memset(buf, 0, MAXDATASIZE);
        if ((numbytes = recv(csock, buf, MAXDATASIZE, 0)) == -1) {
            perror("recv");
            exit(1);
        }
        if (numbytes == 0) {
            printf("서버와의 연결이 종료되었습니다.\n");
            close(csock);
            exit(0);
        }
        printf("서버: %s\n", buf);
    }
}

int main(int argc, char *argv[]) {
    int csock;
    struct sockaddr_in serv_addr;
    pthread_t recv_thread;

    if (argc != 2) {
        fprintf(stderr, "사용법: %s <서버 IP>\n", argv[0]);
        exit(1);
    }

    if ((csock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(PORT);

    if (connect(csock, (struct sockaddr *)&serv_addr, sizeof(struct sockaddr)) == -1) {
        perror("connect");
        close(csock);
        exit(1);
    }
    printf("서버에 연결되었습니다. 메시지를 입력하세요.\n");
    if (pthread_create(&recv_thread, NULL, receive_messages, &csock) != 0) {
        perror("pthread_create");
        close(csock);
        exit(1);
    }

    char msg[MAXDATASIZE];
    while (1) {
        memset(msg, 0, MAXDATASIZE);
        fgets(msg, MAXDATASIZE, stdin);
        msg[strcspn(msg, "\n")] = '\0';

        if (send(csock, msg, strlen(msg), 0) == -1) {
            perror("send");
            close(csock);
            exit(1);
        }
        if (strcmp(msg, "exit") == 0) {
            printf("종료 명령어 입력. 프로그램을 종료합니다.\n");
            close(csock);
            exit(0);
        }
    }

    return 0;
}
