#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/epoll.h>

#define MYPORT 3490
#define BACKLOG 10
#define MAXDATASIZE 100
#define MAX_EVENTS 10

int main() {
    int sockfd, new_fd, epoll_fd;
    struct sockaddr_in my_addr, their_addr;
    struct epoll_event ev, events[MAX_EVENTS];
    socklen_t sin_size;
    char buf[MAXDATASIZE];
    int numbytes;

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

    epoll_fd = epoll_create1(0);
    if (epoll_fd == -1) {
        perror("epoll_create1");
        exit(1);
    }

    ev.events = EPOLLIN;
    ev.data.fd = sockfd;
    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, sockfd, &ev) == -1) {
        perror("epoll_ctl: listen_sock");
        exit(1);
    }

    printf("서버가 시작되었습니다. 클라이언트의 접속을 기다립니다...\n");

    while (1) {
        int nfds = epoll_wait(epoll_fd, events, MAX_EVENTS, -1);
        for (int n = 0; n < nfds; n++) {
            if (events[n].data.fd == sockfd) {
                sin_size = sizeof(struct sockaddr_in);
                if ((new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size)) == -1) {
                    perror("accept");
                    continue;
                }
                ev.events = EPOLLIN;
                ev.data.fd = new_fd;
                if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, new_fd, &ev) == -1) {
                    perror("epoll_ctl: new_fd");
                    exit(1);
                }
                printf("서버: %s에서 연결 요청을 받았습니다.\n", inet_ntoa(their_addr.sin_addr));
            } else {
                memset(buf, 0, MAXDATASIZE);
                if ((numbytes = recv(events[n].data.fd, buf, MAXDATASIZE, 0)) <= 0) {
                    if (numbytes == 0) {
                        printf("클라이언트 %d가 연결을 종료했습니다.\n", events[n].data.fd);
                    } else {
                        perror("recv");
                    }
                    close(events[n].data.fd);
                    epoll_ctl(epoll_fd, EPOLL_CTL_DEL, events[n].data.fd, NULL);
                } else {
                    printf("클라이언트(%d): %s\n", events[n].data.fd, buf);
                    strcat(buf, " (서버 응답)");
                    if (send(events[n].data.fd, buf, strlen(buf), 0) == -1) {
                        perror("send");
                    }
                }
            }
        }
    }

    close(sockfd);
    return 0;
}

