#include <stdio.h>

int main() {
    // Content-Type 헤더에 UTF-8 인코딩 명시
    printf("Content-Type: text/html; charset=UTF-8\n\n");

    // HTML 콘텐츠 출력
    printf("<!DOCTYPE html>\n");
    printf("<html lang=\"ko\">\n");
    printf("<head>\n");
    printf("    <meta charset=\"UTF-8\">\n");
    printf("    <title>CGI 테스트</title>\n");
    printf("</head>\n");
    printf("<body>\n");
    printf("    <h1>안녕하세요, CGI 프로그램입니다!</h1>\n");
    printf("    <p>한글이 제대로 표시됩니다.</p>\n");
    printf("</body>\n");
    printf("</html>\n");

    return 0;
}

