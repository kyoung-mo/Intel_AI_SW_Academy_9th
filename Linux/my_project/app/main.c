// app/main.c
#include <stdio.h>
#include <mymath.h> // <>를 사용합니다 (빌드 시 -I 옵션으로 경로 지정 예정)

int main() {
    int x = 10, y = 5;
    printf("Add: %d\n", add(x, y));
    printf("Subtract: %d\n", subtract(x, y));
    return 0;
}
