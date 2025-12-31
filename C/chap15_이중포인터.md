## chap15 이중포인터
2025-12-29

---
## 445p 포인터와 이중 포인터의 관계

1. 포인터를 변수명으로 쓰면 그 안의 값이 된다.
2. 포인터에 &연산을 하면 포인터 변수의 주소가 된다.
3. 포인터의 *연산은 화살표를 따라간다.


```c
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>


int main() {

    int a = 10;
    int* pi;
    int** ppi;
    pi = &a;
    ppi = &pi;

    printf("a %12d %12u\n", a, &a);
    printf("pi %12u %12u %12d\n", pi, &pi, *pi);
    printf("ppi %12u %12u %12u %12u\n", ppi, &ppi, *ppi, **ppi);

    
    return 0;
}


```

---
a           10   1032844884
pi   1032844884   1032844920           10
ppi   1032844920   1032844952   1032844884           10

C:\Users\KCCISTC\source\repos\12-29\x64\Debug\12-29.exe(프로세스 6748)이(가) 0 코드(0x0)와 함께 종료되었습니다.
디버깅이 중지될 때 콘솔을 자동으로 닫으려면 [도구] -> [옵션] -> [디버깅] > [디버깅이 중지되면 자동으로 콘솔 닫기]를 사용하도록 설정합니다.
이 창을 닫으려면 아무 키나 누르세요...

- a = 10
- &a = x100번지

- *pi = a = 10
- pi = &a = x100번지
- &pi = x200번지

- **ppi = *pi = a = 10
- *ppi = pi = &a - x100번지
- ppi = & pi = x200번지
- &ppi = x300번지

---

## 450p - 이중 포인터를 사용한 포인터 교환
```c

```

---


## 453p - 포인터 배열을 매개변수로 받는 함수
```c


```

---
---

## 457p - 강사님 코드 : 배열 포인터로 2차원 배열의 값 출력
```c
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>


int main() {

    int x = 10, y = 20, z = 30;
    // 포인터 배열 : 배열 안에 포인터형으로 저장
    int* ptrArr[3];
    ptrArr[0] = &x;
    ptrArr[1] = &y;
    ptrArr[2] = &z;
    printf("ptrArr[0] points to %d\n", *ptrArr[0]);
    printf("ptrArr[1] points to %d\n", *ptrArr[1]);
    printf("ptrArr[2] points to %d\n", *ptrArr[2]);

    // 배열 포인터 : 포인터를 배열로 나열
    int arr[3] = { 1,2,3 };
    int (*pArr)[3] = &arr;
    printf("(*pArr)[0] is %d\n", (*pArr)[0]);
    printf("(*pArr)[1] is %d\n", (*pArr)[1]);
    printf("(*pArr)[2] is %d\n", (*pArr)[2]);

    
    return 0;
}

```
ptrArr[0] points to 10
ptrArr[1] points to 20
ptrArr[2] points to 30
(*pArr)[0] is 1
(*pArr)[1] is 2
(*pArr)[2] is 3

C:\Users\KCCISTC\source\repos\12-29\x64\Debug\12-29.exe(프로세스 28032)이(가) 0 코드(0x0)와 함께 종료되었습니다.
디버깅이 중지될 때 콘솔을 자동으로 닫으려면 [도구] -> [옵션] -> [디버깅] > [디버깅이 중지되면 자동으로 콘솔 닫기]를 사용하도록 설정합니다.
이 창을 닫으려면 아무 키나 누르세요...

---


## p
```c
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>


int main() {

    int ary[3][4];
    printf("%d\n", sizeof(&ary));
    printf("%d\n", sizeof(ary));
    printf("%d\n", sizeof(&ary[0]));
    printf("%d\n", sizeof(ary[0]));
    printf("%d\n", sizeof(ary[0][0]));


    
    return 0;
}


```
8
48
8
16
4

C:\Users\KCCISTC\source\repos\12-29\x64\Debug\12-29.exe(프로세스 10712)이(가) 0 코드(0x0)와 함께 종료되었습니다.
디버깅이 중지될 때 콘솔을 자동으로 닫으려면 [도구] -> [옵션] -> [디버깅] > [디버깅이 중지되면 자동으로 콘솔 닫기]를 사용하도록 설정합니다.
이 창을 닫으려면 아무 키나 누르세요...


---
---

## 469p - 15-8예제 대신 강사님 코드
```c
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

// 함수 구현
int add(int x, int y) { return x + y; }
int sub(int x, int y) { return x - y; }
int mul(int x, int y) { return x * y; }
int div(int x, int y) { return y != 0 ? x / y : 0; }

// 함수 포인터 타입 정의 type define
typedef int (*operation_t)(int, int);

// 구조체 ?
typedef struct {
	char name[10];
	operation_t func;
} Command;

int main() {
	Command commands[] = {
		{"add",add},
		{"sub",sub},
		{"mul",mul},
		{"div",div},
		{"",NULL}
	};

	char command[20];
	int a, b;
	printf("원하는 명령을 입력하세요 (예 : add 3 5) :");
	scanf("%s %d %d", command, &a, &b);

	//명령어 검색 후 실행
	for (int i = 0; commands[i].func != NULL; i++) {
		if (strcmp(command, commands[i].name) == 0) {
			int result = commands[i].func(a, b);
			printf("결과: %d\n", result);
			return 0;
		}
	}

	printf("잘못된 명령입니다. \n");
	return 1;
	


	return 0;
}
```
---
원하는 명령을 입력하세요 (예 : add 3 5) :add 3 5
결과: 8

C:\Users\KCCISTC\source\repos\251230\x64\Debug\251230.exe(프로세스 516)이(가) 0 코드(0x0)와 함께 종료되었습니다.
디버깅이 중지될 때 콘솔을 자동으로 닫으려면 [도구] -> [옵션] -> [디버깅] > [디버깅이 중지되면 자동으로 콘솔 닫기]를 사용하도록 설정합니다.
이 창을 닫으려면 아무 키나 누르세요...

---


## p
```c
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

// ASCII code 7 bit
// ANSI code 8bit
//ANSI ESCAPE code

int main() {
	putc(0x1b, stdout);
	printf("[38;5;10mHello world\n");

	return 0;
}
```

<img width="1112" height="168" alt="image" src="https://github.com/user-attachments/assets/564acb74-9432-4a1e-91bd-5d8d88517e27" />

---
