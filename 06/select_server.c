#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/select.h>

#define MYPORT 3490
#define BACKLOG 10
#define MAXDATASIZE 100
#define MAX_CLIENTS 10

int main() {
    int sockfd, new_fd;
    struct sockaddr_in my_addr, their_addr;
    socklen_t sin_size;
    char buf[MAXDATASIZE];
    int fd_max, i, numbytes;
    fd_set master;
    fd_set read_fds;

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

    FD_ZERO(&master);
    FD_ZERO(&read_fds);
    FD_SET(sockfd, &master);
    fd_max = sockfd;

    printf("서버가 시작되었습니다. 클라이언트의 접속을 기다립니다...\n");

    while (1) {
        read_fds = master;

        if (select(fd_max + 1, &read_fds, NULL, NULL, NULL) == -1) {
            perror("select");
            exit(1);
        }

        for (i = 0; i <= fd_max; i++) {
            if (FD_ISSET(i, &read_fds)) {
                if (i == sockfd) {
                    sin_size = sizeof(struct sockaddr_in);
                    if ((new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size)) == -1) {
                        perror("accept");
                        continue;
                    }
                    FD_SET(new_fd, &master);
                    if (new_fd > fd_max) {
                        fd_max = new_fd;
                    }
                    printf("서버: %s에서 연결 요청을 받았습니다.\n", inet_ntoa(their_addr.sin_addr));
                } else {
                    memset(buf, 0, MAXDATASIZE);
                    if ((numbytes = recv(i, buf, MAXDATASIZE, 0)) <= 0) {
                        if (numbytes == 0) {
                            printf("클라이언트 %d가 연결을 종료했습니다.\n", i);
                        } else {
                            perror("recv");
                        }
                        close(i);
                        FD_CLR(i, &master);
                    } else {
                        printf("클라이언트(%d): %s\n", i, buf);

                        if (strcmp(buf, "exit") == 0) {
                            printf("클라이언트 %d와의 연결 종료.\n", i);
                            close(i);
                            FD_CLR(i, &master);
                        } else {
                            strcat(buf, " (서버 응답)");
                            if (send(i, buf, strlen(buf), 0) == -1) {
                                perror("send");
                            }
                        }
                    }
                }
            }
        }
    }

    close(sockfd);
    return 0;
}

