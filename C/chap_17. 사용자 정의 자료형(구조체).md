## chap 17. 사용자 정의 자료형(구조체)
2025.12.30

구조체 패딩바이트
맴버의 순서에 따라 구조체의 크기가 달라질 수 있다.
패딩바이트가 가장 작도록 구조체를 선언하면 메모리를 아낄 수 있다.

---
## 메모리 관리 - 구조체 맴버 순서에 따라
```c
#include <stdio.h>

// 총 32바이트
struct student1 {
	char ch1;
	short num;
	char ch2;
	int score;
	double grade;
	char ch3;
};

// 총 24바이트
struct student2 {
	char ch1;
	char ch2;
	short num;
	int score;
	double grade;
	char ch3;
};

int main() {
	//구조체 선언
	struct student1 s1;
	struct student2 s2;

	printf("구조체의 크기 : %d, %d\n", sizeof(s1), sizeof(s2));
}
```

<img width="1108" height="190" alt="image" src="https://github.com/user-attachments/assets/fe67664f-fca3-43b8-982b-cecf9ba33980" />

---

- 전역 변수같은 경우 추후에 개발 시 구조체 안에 전부 넣는 방식으로 관리하기 쉽다.
- 구조체 내 구조체 내 구조체 적극 활용

<img width="707" height="546" alt="image" src="https://github.com/user-attachments/assets/095919e4-c9e0-476e-a65b-3d4988b06aab" />

<img width="684" height="693" alt="image" src="https://github.com/user-attachments/assets/6e7ae99f-b433-4a09-9f1a-a204128ebbd0" />

---

구조체의 장점으로 

- struct student max
- struct student s1
- max = s1 이런 식으로 복사가 가능하다.

## 17.2 구조체 포인터

## 확인문제 1번 540p
```c
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

struct marriage {
	char name[20];
	int age;
	char gender;
	double height;
};

struct marriage m1 = { "Andy", 22, 'm', 187.5 };
struct marriage* mp = &m1;

// 확인문제 1
// mp를 이용해 m1에 저장된 값을 출력하시오.

int main() {
	
	printf("%s\n%d\n%c\n%.1lf", mp->name, mp->age, mp->gender, mp->height);
	
	return 0;
}
```

---
---


## p
```c

```

---
---


## p
```c

```

---
---


## p
```c

```

---
---


## p
```c

```

---
