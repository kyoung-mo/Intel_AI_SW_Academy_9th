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
---


## p
```c

```

---
