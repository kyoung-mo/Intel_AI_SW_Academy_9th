5장 : [https://docs.google.com/presentation/d/1Xg4BNFt5drinjFWmprxzgoptJuVlEx0N/edit?slide=id.p5#slide=id.p5](https://docs.google.com/presentation/d/1Xg4BNFt5drinjFWmprxzgoptJuVlEx0N/edit?slide=id.p3#slide=id.p3)

## 큐(QUEUE)
- 먼저 들어온 데이터가 먼저 나가는 자료구조
- 선입선출(FIFO)

## 큐 ADT

<img width="919" height="620" alt="image" src="https://github.com/user-attachments/assets/7372b450-d314-4b06-88bf-7263330fd254" />

## 큐의 삽입, 삭제 연산

<img width="570" height="609" alt="image" src="https://github.com/user-attachments/assets/3e98731c-577e-4ac6-9b4e-a0a2aced607e" />

## 선형 큐
- 배열을 선형으로 사용하여 큐를 구현
  - 삽입을 계속하기 위해서는 요소들을 이동시켜야 함
 
<img width="822" height="338" alt="image" src="https://github.com/user-attachments/assets/45a1ac2b-a64b-4bd9-891e-66ee9f426ddb" />

# 선형 큐의 응용 : 작업 스케줄링

<img width="880" height="502" alt="image" src="https://github.com/user-attachments/assets/97b36131-9208-4122-bc85-a59ffa2fcdb6" />

# 원형 큐
- 선형 큐에서는 큐의 최대 크기에 도달하면 더이상 저장할 수 없다는 단점이 있어서 나옴
- 원형 큐 또한 전단과 후단을 관리하기 위해 2개의 변수(주로 front, rear) 존재

  <img width="769" height="537" alt="image" src="https://github.com/user-attachments/assets/49e0a842-ffa5-40ed-9d32-1df87978aa90" />명

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
일반적으로 규모가 큰 프로젝트를 설계할때는 기능에 따라 여러 쓰레드 사용

멀티 스레드를 사용할때도 Queue를 사용하는데, 전역변수를 이용할때는 1초에 한번, 0.5초에 한 번씩 받지만
QUEUE를 사용하면 데이터를 차곡차곡 쌓기 때문에 데이터를 놓칠 일이 없다.






