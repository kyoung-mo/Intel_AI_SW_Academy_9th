날짜 : 2025-12-29  
---
수정 : 2025-12-31  
    - 전역변수 및 지역변수에 대한 설명 추가  
    - 예제 1~3에 따른 비교 추가  
    - 전역변수 대신 포인터를 쓸 때 장점 추가   
    - 함수에서 포인터 쓰는 이유 추가  
    - call-by-value / call-by-address / call-by-reference 정리 추가  
    - 메모리 구조 및 포인터의 역할 추가  
    
---
    
## chap13 - 변수의 영역과 데이터 공유

- 전역 변수(global)
`int g = 10;
void func(){ g = 20; }`
    - 함수 밖에서 선언됨
    - 프로그램이 끝날 때까지 존재
        - (수명 : 전체 실행 시간)
    - 어디서든 접근 가능
        - (범위 : 전체 파일 or extern 연결)
    - 데이터 영역에 저장됨
 
- 지역 변수(local)
`void func() {
    int x = 10;
}
`
    - 함수 안에서 선언됨
    - 함수가 끝나면 사라짐
        - (수명 : 함수 실행 중)
    - 함수 밖에서는 접근 불가
        - (범위 제한.. 중괄호 안에서 실행됐으면 중괄호 끝날때까지라고 생각!)
    - 스택(Stack) 영역에 저장됨
 
### 지역 변수는 함수 밖에서 바꿀 수 없다!

1번 예제)
```c
void change(int x) {
    x = 20;
}

int main() {
    int a = 10;
    change(a);
    printf("%d", a);
}
```

- 위 코드에서 `change(int x)` 함수는 `main()`함수에서 `변수 a`의 값을 바꿀 수 없음.
  - `change(int x)` 함수 호출 시 `a의 값(10)`만 복사됨
  - x는 a가 아니라 " 복사된 다른 변수 "
  - `call by value(값 전달)`
 
따라서 함수가 지역 변수만 수정할 수 있고, 메인 함수의 변수는 바꿀 수 없다.

하지만? 아래 2번 예제는 다르다.
2번 예제)
```c
int change(int x) {
    x = 20;
    return x;
}
int main() {
    int a = 10;
    a = change(a);
    printf("%d", a);
}
```
- `change(a)`는 반환값이 20이라는 정수이다.
- 그 값을 `a=change(a);` 를 통해 변수 a에 저장을 해주기 때문에 1번의 예제와는 다른 상황이나, 헷갈려서 정리해두었다.

이제 포인터를 왜 쓰는지에 대해 확인해보면,

3번 예제)
```c
void change(int *p){
    *p = 20;
}
int main(){
    int a = 10;
    change(&a);
    printf("%d",a);
}
```
- `포인터 변수 p`안에는 `a의 주소`가 들어있음.
- *p는 실제 a
- 즉, 함수가 직접 a를 수정함
- 정리하면, 함수를 통해 지역 변수만이 아니라 호출한 함수의 변수까지 수정할 수 있게 하기 위해 사용한다.

---

### 전역변수 vs 포인터

- 전역 변수 또한 값을 공유 가능하지만, 단점이 있음
  - 어디서나 접근 가능하기 때문에 버그 추적이 어렵다. (협업 시 위험, 유지보수 어려움)
- 따라서 전역변수 대신 포인터로 주소를 넘겨서 지역변수를 수정한다.

- 포인터를 사용하게 되면 장점:
  - 함수끼리 데이터 공유 가능
  - 동시에 변수의 수명은 원래 주인(main함수)의 것 유지
  - 코드 구조가 안전하고 명확

### 함수에서 포인터를 쓰는 이유
- 호출자의 변수 값을 수정하고 싶을 때
    `swap(a,b);`
- 배열을 함수에 넘길 때(배열 = 포인터)
    `void func(int arr[]);`
- 동적 메모리 사용
    `malloc()`

- main 함수의 수명, 지역 변수 수명
    - main 함수의 수명 : 프로그램 시작 ~ 프로그램 종료

- main 함수의 지역 변수 수명
```c
int main(){
    int a=10;
}
```
    - a는 지역 변수
    - 스택(Stack)에 저장됨

### call-by-value / call-by-address / call-by-reference

1. Call-by-value(값 전달)
`change(a);`
   - 값만 복사
   - 원본 변수는 안전
   - 함수 안에서만 영향

2. Call-by-address(주소 전달)
`change(&a);`
    - 주소를 넘김
    - 포인터 사용
    - 함수가 직접 원본 변수 수정 가능
    - C에서 흔히 말하는 "reference처럼 동작하는 방법" (??)
  
(참고) Call-by-reference
    - C++ 혹은 다른 언어의 개념
    - C에는 주소를 넘겨서 reference처럼 흉내낼 뿐

## 메모리 구조 정리 (실행 중)
```css
[코드 영역]
[전역 변수 영역]
[힙 영역]
[스택 영역]
```
- C 프로그램이 실행되면 메모리는 이런 층 구조로 나뉜다.

- 코드 영역(Code Segment)
    - 프로그램의 기계어 코드가 저장되는 영역
    - 함수 내용, 명령어 등
    - 읽기 전용
      ex)
      ```c
      int main(){}
      void func(){}
      // 이런 코드들이 저장
      ```
- 전역 변수 영역(Data Segment)
    - 전역 변수 및 static 변수 저장
    - 프로그램 전체 실행되는 동안 유지
      ex)
      ```c
      int g = 10;    // 전역 변수
      static int s;  // 정적 변수
      ```

- 힙 영역(Heap)
    - `malloc()` 으로 할당한 메모리
    - 프로그래머가 직접 관리하는 영역
    - `free()` 진행하지 않으면 메모리 누수 발생
      ex) `int *p = malloc(sizeof(int));`

- 스택 영역(Stack)
    - 함수 실행할 때마다 생성
    - 지역 변수 저장
    - 함수가 끝나면 자동으로 삭제
      ex)
      ```c
      void func(){
      int x = 10;    // 스택 영역
      }
      // main 지역 변수도 여기에 저장된다.
      ```

- 위와같은 메모리 구조에서 포인터는 메모리 영역을 연결해주는 주소표 역할을 한다.
- 스택 지역 변수도 가리킬 수 있고, 힙에서 동적 메모리도 가리킬 수 있고, 전역 변수 또한 가리킬 수 있다.


### p
```c
#include <stdio.h>

int main() {
    int ch;
    int max_word_length = 0;
    int cnt = 0;
    int loop = 1;

    do {
        do {
            ch = getchar();
            if(ch != '\n') cnt++;
            if (ch == -1) loop = 0;
        } while (ch != '\n');
        if (cnt > max_word_length) max_word_length = cnt;
        cnt = 0;
    } while (loop);
    printf("가장 긴 단어의 길이 : %d", max_word_length);

    return 0;
}
```

---

### 381p
```c
#include <stdio.h>
#include <string.h>

char* cmp(char* inStr);

int main() {
    char str[16];

    printf("단어 입력 : ");
    scanf("%s", str);
    printf("입력한 단어 : %s, 생략한 단어 : %s", str, cmp(str));

    return 0;
}

char* cmp(char* inStr) {
    static char resp[16];
    int i = 0;
    while (*inStr != '\0') {
        if (i < 5) resp[i++] = *inStr;
        else resp[i++] = '*';
        inStr++;
    }
    resp[i] = '\0';

    return resp;
}
```

---

### 389p - 전역변수
```c
#include <stdio.h>

void assign10();
void assign20();

int a;

int main() {
    
    printf("함수 호출 전 a값 : %d\n", a);

    assign10();
    assign20();

    printf("함수 호출 후 a값 : %d\n", a);
    return 0;
}


void assign10() {
    a = 10;
}
void assign20() {
    int a;
    a = 20;
}
```
함수 호출 전 a값 : 0  
함수 호출 후 a값 : 10  
  
C:\Users\KCCISTC\source\repos\12-29\x64\Debug\12-29.exe(프로세스 22680)이(가) 0 코드(0x0)와 함께 종료되었습니다.  
디버깅이 중지될 때 콘솔을 자동으로 닫으려면 [도구] -> [옵션] -> [디버깅] > [디버깅이 중지되면 자동으로 콘솔 닫기]를 사용하도록 설정합니다.  
이 창을 닫으려면 아무 키나 누르세요...  

---
* 전역변수의 문제점  
1) 전역 변수의 이름을 바꾸면 그 변수를 사용하는 모든 함수를 찾아 수정해야 합니다.  
2) 전역 변수의 값이 잘못된 경우 접근 가능한 모든 함수를 의심해야 합니다.  
3) 코드 블록 내에 같은 이름의 지역변수를 선언하면 거기서는 전역 변수를 사용할 수 없습니다.  
---


### 393p - 정적 지역 변수 (static)
```c
#include <stdio.h>

void auto_func(void);
void static_func(void);

int main() {
    
    int i;
    printf("일반 지역 변수(auto)를 사용한 함수...\n");

    for (i = 0; i < 3; i++) {
        auto_func();
    }

    printf("정적 지역 변수(static)을 사용한 함수...\n");

    for (i = 0; i < 3; i++) {
        static_func();
    }

    return 0;
}


void auto_func(void) {
    auto int a = 0;

    a++;
    printf("%d\n", a);
}
void static_func(void) {
    static int a;

    a++;
    printf("%d\n", a);
}
```

---
일반 지역 변수(auto)를 사용한 함수...
1
1
1
정적 지역 변수(static)을 사용한 함수...
1
2
3

C:\Users\KCCISTC\source\repos\12-29\x64\Debug\12-29.exe(프로세스 23908)이(가) 0 코드(0x0)와 함께 종료되었습니다.    
디버깅이 중지될 때 콘솔을 자동으로 닫으려면 [도구] -> [옵션] -> [디버깅] > [디버깅이 중지되면 자동으로 콘솔 닫기]를 사용하도록 설정합니다.  
이 창을 닫으려면 아무 키나 누르세요...  

---

register(특수 목적의 기억 공간)1 - PC, SP 대표적인 레지스터. 어떤 역할을 하냐면 PC는 프로그램 카운터. 코드 영역의 주소를 가르키고 있는 포인터(지시자) 프로그램 실행하는경우 stack pointer는 책에 손가락 끼워두는 느낌. 북마크? 별도의 컴파일러를 통해 동작을 구현해볼예정  

cpu 내부에 위치  
cash memory(외부 메모리의 임시 버퍼) - 빈번하게 사용되는 데이터의 경우 캐시 메모리에 저장  
| SRAM(3) | DRAM(4) |  
|---------|---------|
| 속도가 좀 더 빠름 | 좀 더 느림 |  

---
13-2 함수의 데이터 공유 방법
1. 값을 복사해서 전달
2. 주소를 전달
3. 주소를 반환
### 400p
```c
#include <stdio.h>

void add_ten(int a);

int main() {
    
    int a = 10;
    add_ten(a);
    printf("%d", a);


    return 0;
}


void add_ten(int a) {
    a = a + 10;
}
```
---
10
C:\Users\KCCISTC\source\repos\12-29\x64\Debug\12-29.exe(프로세스 18340)이(가) 0 코드(0x0)와 함께 종료되었습니다.  
디버깅이 중지될 때 콘솔을 자동으로 닫으려면 [도구] -> [옵션] -> [디버깅] > [디버깅이 중지되면 자동으로 콘솔 닫기]를 사용하도록 설정합니다.  
이 창을 닫으려면 아무 키나 누르세요...  

---

```c
#include <stdio.h>

int add_ten(int a);

int main() {
    
    int a = 10;
    add_ten(a);
    printf("%d", a);


    return 0;
}


int add_ten(int a) {
    a = a + 10;
    return a;
}
```
---

C:\Users\KCCISTC\source\repos\12-29\x64\Debug\12-29.exe(프로세스 13584)이(가) 0 코드(0x0)와 함께 종료되었습니다.  
디버깅이 중지될 때 콘솔을 자동으로 닫으려면 [도구] -> [옵션] -> [디버깅] > [디버깅이 중지되면 자동으로 콘솔 닫기]를 사용하도록 설정합니다.  
이 창을 닫으려면 아무 키나 누르세요...  

---

---

###  포인터 사용
```c
#include <stdio.h>

int add_ten(int *a);

int main() {
    
    int a = 10;
    add_ten(&a);
    printf("%d", a);


    return 0;
}


int add_ten(int *a) {
    *a = *a + 10;
}
```
---

C:\Users\KCCISTC\source\repos\12-29\x64\Debug\12-29.exe(프로세스 4716)이(가) 0 코드(0x0)와 함께 종료되었습니다.  
디버깅이 중지될 때 콘솔을 자동으로 닫으려면 [도구] -> [옵션] -> [디버깅] > [디버깅이 중지되면 자동으로 콘솔 닫기]를 사용하도록 설정합니다.  
이 창을 닫으려면 아무 키나 누르세요...  


---


### 408p - 도전 실전 예제
```c
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void input_data(int* pa, int* pb);
void swap_data(void);
void print_data(int a, int b);

int a, b;

int main() {
    input_data(&a, &b);
    print_data(a, b);
    swap_data();
    printf("=====swap_data======\n");
    print_data(a, b);

    return 0;
}


void input_data(int* pa, int* pb) {
    printf("a값 입력: ");
    scanf("%d", pa);
    printf("b값 입력: ");
    scanf("%d", pb);
}
void swap_data(void) {
    int temp;
    temp = b;
    b = a;
    a = temp;
}
void print_data(int a, int b) {
    printf("========print_data==========\n");
    printf("a = %d\n", a);
    printf("b = %d\n", b);
}

```

---
a값 입력: 10  
b값 입력: 30  
========print_data==========  
a = 10  
b = 30  
=====swap_data======  
========print_data==========  
a = 30  
b = 10  

C:\Users\KCCISTC\source\repos\12-29\x64\Debug\12-29.exe(프로세스 18728)이(가) 0 코드(0x0)와 함께 종료되었습니다.  
디버깅이 중지될 때 콘솔을 자동으로 닫으려면 [도구] -> [옵션] -> [디버깅] > [디버깅이 중지되면 자동으로 콘솔 닫기]를 사용하도록 설정합니다.  
이 창을 닫으려면 아무 키나 누르세요...  

---
