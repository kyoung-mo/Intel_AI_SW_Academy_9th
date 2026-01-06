날짜 : 2025-12-31

## chap 9_포인터

[헷갈리는 부분 정리]

```c
int a = 10;
int *p = &a;
```

---

- a == 10;
- p == &a;
- *p == a == 10;

---

여기서 `int *p = &a` 로 선언하는 부분을 보면,
- `*p = &a` 아니야? 이렇게 생각할 수 있음.
  - `int *p;` : int 값을 가리키는 포인터 변수를 선언하는 방식
  - 즉, `int *p` 는 " 타입 선언의 일부 " 이다.
 
- 정리 :
  - 1. `포인터 변수 p` 에는 주소가 저장된다.
  - 2. `*p = a 주소에 저장된 값` 이다.

## Const를 사용한 포인터
- const 예약어를 포인터에 사용하면 이는 가리키는 변수의 값을 바꿀 수 없다는 의미
- 변수에 사용하는 것과는 다른 의미

- 미니 정렬 프로그램 -**도전 실전 예제**
    
     키보드로 실수 3개를 입력한 후 큰 숫자부터 작은 숫자로 정렬한 뒤 출력하는 프로그램
    
    ```c
    실수값 3개 입력 : 2.7 1.5 3.4
    정렬된 값 출력 : 3.4, 2.7, 1.5
    ```
    
     중간값과 최소값, 중간값과 최대값, 최소값과 최대값을 비교해서 swap() 진행
    
    실행결과
  
```c
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void swap(float *pa, float *pb, float *pc);
int main() {

	float a=0.0, b=0.0, c=0.0;
	float* pa;
	float* pb;
	float* pc;

	pa = &a;
	pb = &b;
	pc = &c;

	printf("실수값 3개 입력 : ");
	scanf("%f %f %f", &a, &b, &c);

	swap(pa, pb, pc);

	printf("%.1f, %.1f, %.1f", *pa, *pb, *pc);

	return 0;

}

void swap(float* pa, float* pb, float* pc) {

	float temp;

	if (*pa < *pb) {
		temp = *pa;
		*pa = *pb;
		*pb = temp;
	}

	if (*pa < *pc) {
		temp = *pa;
		*pa = *pc;
		*pc = temp;
	}
	
	if (*pb < *pc) {
		temp = *pb;
		*pb = *pc;
		*pc = temp;
	}

}
```
