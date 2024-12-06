#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/wait.h>

#define MYPORT 3490
#define BACKLOG 10
#define MAXDATASIZE 100

void handle_client(int client_fd) {
    char buf[MAXDATASIZE];
    int numbytes;

    printf("클라이언트와 연결되었습니다. 클라이언트 소켓: %d\n", client_fd);

    while (1) {
        memset(buf, 0, MAXDATASIZE);
        if ((numbytes = recv(client_fd, buf, MAXDATASIZE, 0)) <= 0) {
            if (numbytes == 0) {
                printf("클라이언트 소켓 %d가 연결을 종료했습니다.\n", client_fd);
            } else {
                perror("recv");
            }
            close(client_fd);
            exit(0);
        }

        printf("클라이언트(%d): %s\n", client_fd, buf);

        if (strcmp(buf, "exit") == 0) {
            printf("클라이언트 소켓 %d와의 연결 종료.\n", client_fd);
            close(client_fd);
            exit(0);
        }
        strcat(buf, " (서버 응답)");
        if (send(client_fd, buf, strlen(buf), 0) == -1) {
            perror("send");
            close(client_fd);
            exit(0);
        }
    }
}

int main() {
    int sockfd, new_fd;
    struct sockaddr_in my_addr, their_addr;
    socklen_t sin_size;

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(MYPORT);
    my_addr.sin_addr.s_addr = INADDR_ANY;
    memset(&(my_addr.sin_zero), 0, 8);

    if (bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) == -1) {
        perror("bind");
        exit(1);
    }

    if (listen(sockfd, BACKLOG) == -1) {
        perror("listen");
        exit(1);
    }

    printf("서버가 시작되었습니다. 클라이언트의 접속을 기다립니다...\n");

    while (1) {
        sin_size = sizeof(struct sockaddr_in);
        if ((new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size)) == -1) {
            perror("accept");
            continue;
        }

        printf("서버: %s에서 연결 요청을 받았습니다.\n", inet_ntoa(their_addr.sin_addr));

        pid_t pid = fork();
        if (pid == 0) {
            close(sockfd);
            handle_client(new_fd);
        } else if (pid < 0) {
            perror("fork");
        }
        close(new_fd);
        while (waitpid(-1, NULL, WNOHANG) > 0);
    }

    close(sockfd);
    return 0;
}
