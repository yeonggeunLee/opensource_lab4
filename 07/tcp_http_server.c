#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/wait.h> // For waitpid()

#define PORT 8080
#define BUFFER_SIZE 1024

// 기본 HTML 페이지 템플릿
const char* html_template = 
"HTTP/1.1 200 OK\r\n"
"Content-Type: text/html; charset=UTF-8\r\n\r\n"
"<!DOCTYPE html>\n"
"<html>\n"
"<head>\n"
"    <title>웹서버 테스트</title>\n"
"    <meta charset=\"UTF-8\">\n"
"</head>\n"
"<body>\n"
"    <h1>웹서버 테스트</h1>\n"
"    <p>%s</p>\n" // 메시지가 삽입될 자리
"    <form action=\"/post\" method=\"POST\">\n"
"        <input type=\"text\" name=\"message\" placeholder=\"메시지 입력\">\n"
"        <button type=\"submit\">POST 요청</button>\n"
"    </form>\n"
"    <form action=\"/get\" method=\"GET\">\n"
"        <button type=\"submit\">GET 요청</button>\n"
"    </form>\n"
"</body>\n"
"</html>\n";

// POST 요청에서 메시지 추출
void extract_post_message(const char* request, char* message) {
    const char* key = "message=";
    char* start = strstr(request, key);
    if (start) {
        start += strlen(key); // "message=" 이후의 문자열로 이동
        char* end = strchr(start, '&'); // 다른 파라미터가 있을 경우 처리
        if (!end) {
            end = strchr(start, '\0'); // 문자열 끝까지 읽음
        }
        strncpy(message, start, end - start);
        message[end - start] = '\0'; // 널 문자 추가
    } else {
        strcpy(message, "메시지가 없습니다.");
    }
}

// 요청 처리 함수
void handle_request(int client_socket) {
    char buffer[BUFFER_SIZE];
    ssize_t bytes_received = recv(client_socket, buffer, BUFFER_SIZE - 1, 0);

    if (bytes_received > 0) {
        buffer[bytes_received] = '\0';
        printf("요청 받음:\n%s\n", buffer);

        char response[BUFFER_SIZE * 2];
        char message[BUFFER_SIZE] = "메시지를 입력하세요."; // 기본 메시지

        if (strncmp(buffer, "POST /post", 10) == 0) {
            // POST 요청 처리
            extract_post_message(buffer, message);
            snprintf(response, sizeof(response), html_template, message);
            send(client_socket, response, strlen(response), 0);
        } else if (strncmp(buffer, "GET /cgi-bin/", 13) == 0) {
            // CGI 요청 처리
            char cgi_program[BUFFER_SIZE];
            sscanf(buffer + 4, "/cgi-bin/%s", cgi_program); // CGI 프로그램 이름 추출

            char cgi_path[BUFFER_SIZE];
            snprintf(cgi_path, sizeof(cgi_path), "./cgi-bin/%s", cgi_program);

            int pipe_fd[2];
            pipe(pipe_fd);

            pid_t pid = fork();
            if (pid == 0) {
                // 자식 프로세스: CGI 프로그램 실행
                dup2(pipe_fd[1], STDOUT_FILENO); // 표준 출력을 파이프로 연결
                close(pipe_fd[0]);
                close(pipe_fd[1]);
                execl(cgi_path, cgi_path, NULL);
                perror("CGI 실행 실패");
                exit(1);
            } else if (pid > 0) {
                // 부모 프로세스: CGI 출력 읽기
                close(pipe_fd[1]);
                waitpid(pid, NULL, 0); // 자식 프로세스 종료 대기

                char cgi_output[BUFFER_SIZE];
                read(pipe_fd[0], cgi_output, sizeof(cgi_output));
                close(pipe_fd[0]);

                snprintf(response, sizeof(response), "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n%s", cgi_output);
                send(client_socket, response, strlen(response), 0);
            } else {
                perror("fork 실패");
            }
        } else {
            snprintf(response, sizeof(response), html_template, message);
            send(client_socket, response, strlen(response), 0);
        }
    }
}

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);

    // 소켓 생성
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("소켓 생성 실패");
        exit(1);
    }

    // 서버 주소 설정
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // 바인딩
    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("바인딩 실패");
        exit(1);
    }

    // 리스닝
    if (listen(server_socket, 5) == -1) {
        perror("리스닝 실패");
        exit(1);
    }

    printf("서버가 포트 %d에서 실행 중...\n", PORT);

    while (1) {
        client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &client_len);
        if (client_socket == -1) {
            perror("연결 수락 실패");
            continue;
        }

        handle_request(client_socket);
        close(client_socket);
    }

    close(server_socket);
    return 0;
}

