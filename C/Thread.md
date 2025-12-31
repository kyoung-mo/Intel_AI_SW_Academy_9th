```c
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

DWORD WINAPI ThreadFunction(LPVOID param) {
    int id = *(int*)param;
    for (int i = 0; i < 5; i++) {
        printf("Thread %d 실행 중... %d\n", id, i);
        Sleep(1000);  // 1초 대기
    }
    return 0;
}

int main() {
    HANDLE threads[2];
    int threadIDs[2] = { 1, 2 };

    // 두 개의 스레드 생성
    for (int i = 0; i < 2; i++) {
        threads[i] = CreateThread(
            NULL, 0, ThreadFunction, &threadIDs[i], 0, NULL);
        if (threads[i] == NULL) {
            printf("스레드 생성 실패\n");
            return 1;
        }
    }

    // 모든 스레드가 종료될 때까지 대기
    WaitForMultipleObjects(2, threads, TRUE, INFINITE);

    // 스레드 핸들 닫기
for (int i = 0; i < 2; i++) {
        CloseHandle(threads[i]);
    }

    printf("메인 스레드 종료\n");
    return 0;
}
```
쓰레드별로 개념을 나눠서 설계
일반적으로 규모가 큰 프로젝트를 설계할때는
