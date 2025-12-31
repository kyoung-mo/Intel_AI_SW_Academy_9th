날짜 : 2025-12-29
## chap14 - 다차원 배열

차원이 점점 늘어나는 형태.

#### 2차원 배열 선언과 요소 사용
- score1[4]; -> ~~~
- score2[4]; -> ~~~
- score3[4]; -> ~~~

- 복잡하니까, score[3][4]; 로 선언 (3행 4열)

ㅁㅁㅁㅁ 101번지 ~ 115번지
ㅁㅁㅁㅁ 116번지 ~ 131번지
ㅁㅁㅁㅁ 132번지 ~ 147번지

415page 중요한 부분 정리 
- 행 첨자 : 1차원 배열로 계산했을 때의 위치/열의 수 -> 6/4 = 1
- 열 첨자 : 1차원 배열로 계산했을 때의 위치 %열의 수 -> 6%4 = 2

2차원 배열에서 일부 초깃값 생략이 가능하다(자동으로 0으로 채워짐) int num[3][4] = {{1},{2,3},{4,5,6}};
행의 수 생략도 가능 int num[][4] = {{1},{2,3},{4,5,6}};
1차원 배열의 초기화 방식으로 초기화 가능 int num[3][4] = {1,2,3,4,5,6,7,8,9,10,11,12};
1차원 배열의 초기화 방식으로 초기화 가능(남은 칸은 자동으로 0 초기화) int num[3][4] = {1,2,3,4,5,6}; / int num[100][200] ={0}; // 20000개의 요소 모두 0으로 초기화






## 421p 14-3 여러 개의 동물 이름을 입출력하는 프로그램
```c
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>


int main() {

    char animal[5][20];
    int i, count;

    count = sizeof(animal) / sizeof(animal[0]);
    for (i = 0; i < count; i++) {
        scanf("%s", animal[i]);
    }
    for (i = 0; i < count; i++) {
        printf("%s \t", animal[i]);
    }

    return 0;
}


```

위 실행결과에서 
animal = &animal[0][0];
animal[0] = &animal[0][0];
animal[1] = &animal[1][0];
animal[2] = &animal[2][0];
animal[3] = &animal[3][0];
animal[4] = &animal[4][0];
과 같이 저장된다.

---

dog
tiger
rabbit
horse
cat
dog     tiger   rabbit  horse   cat
C:\Users\KCCISTC\source\repos\12-29\x64\Debug\12-29.exe(프로세스 7756)이(가) 0 코드(0x0)와 함께 종료되었습니다.
디버깅이 중지될 때 콘솔을 자동으로 닫으려면 [도구] -> [옵션] -> [디버깅] > [디버깅이 중지되면 자동으로 콘솔 닫기]를 사용하도록 설정합니다.
이 창을 닫으려면 아무 키나 누르세요...

---

# 14-2 포인터 배열

배열과 포인터 배열의 문법은 거의 같다?


---

## 432p - 14.6 / 포인터 배열로 여러 개의 문자열 출력

포인터는 
1. 주소를 저장하는 특별한 용도로 쓰이지만,
2. 일반 변수처럼 메모리에 저장 공간을 갖는 변수로도 쓰인다.


```c
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>


int main() {

    char* pary[5];
    int i;

    pary[0] = "dog";
    pary[1] = "elephant";
    pary[2] = "horse";
    pary[3] = "tiger";
    pary[4] = "lion";

    for (i = 0; i < 5; i++) {
        printf("%s\n", pary[i]);
    }
}

```

<img width="1086" height="265" alt="image" src="https://github.com/user-attachments/assets/ba271c47-ee6a-48fc-9c69-b54ad1961e70" />

무슨소릴까..

