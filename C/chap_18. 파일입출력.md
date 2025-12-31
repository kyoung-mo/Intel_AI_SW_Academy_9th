## chap18. 파일입출력

### 18-1 파일 개방과 입출력


---



## 543p 18-1 파일 열고 닫는 프로그램
```c
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>


// 확인문제 1
// mp를 이용해 m1에 저장된 값을 출력하시오.

int main() {
	
	FILE* fp = fopen("c:\\Temp\\a.txt", "r"); // 역슬레시(\\)는 두 번 써줌
	if (fp == NULL) {
		printf("파일이 열리지 않았습니다.");
		return 1;
	}

	printf("파일이 열렸습니다.");
	fclose(fp);
	

	return 0;
}
```

---
---


## 549p 18-2
```c
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>


// 확인문제 1
// mp를 이용해 m1에 저장된 값을 출력하시오.

int main() {
	
	int ch;

	FILE* fp = fopen("a.txt", "r"); 
	if (fp == NULL) {
		printf("파일이 열리지 않았습니다.");
		return 1;
	}

	//printf("파일이 열렸습니다.");
	while (1) {
		ch = fgetc(fp);
		if (ch == EOF) {
			break;
		}
		putchar(ch);
	}

	fclose(fp);
	

	return 0;
}
```

---
---


## 558p 18-6
```c
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main() {
	
	int ary[10] = {13,10,13,13,10,26,13,10,13,10};
	int res;
	int i;

	FILE* fp = fopen("aa.txt", "wb"); 
	if (fp == NULL) {
		printf("파일이 만들지 못했습니다.");
		return 1;
	}
	for (i = 0; i < 10; i++) {
		fputc(ary[i], fp);
	}

	fclose(fp);

	fp = fopen("aa.txt", "rt");
	while (1) {
		res = fgetc(fp);
		if (res == EOF) break;
		printf("%4d", res);
	}
	fclose(fp);
	

	return 0;
}
```

<img width="1109" height="162" alt="image" src="https://github.com/user-attachments/assets/3dea13e2-1695-406d-ac06-3962463e5aa7" />

---

<img width="1904" height="919" alt="image" src="https://github.com/user-attachments/assets/58f7e2de-1424-406a-832b-3ccbd53309f6" />

헥사 에디터에서 자동차 사진 넣은상황

---

https://ko.wikipedia.org/wiki/BMP_%ED%8C%8C%EC%9D%BC_%ED%8F%AC%EB%A7%B7

## bmp 헤더구조 읽는 과정 [0], [1]
```c
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

typedef unsigned char unit8_t;
typedef struct {
	unit8_t bmpType[2];
	unit8_t bmpSize[4];
	unit8_t bmpOffset[4];
	unit8_t bidSize[4];
	unit8_t bidWidth[4];
	unit8_t bidHeight[4];
	unit8_t bidColorPlane[2];
	unit8_t bidBitPerPixel[2];

} bmpHeader;

int main() {
	
	bmpHeader bh;

	FILE* fp = fopen("C:\\Users\\KCCISTC\\source\\repos\\251230\\251230\\car.bmp", "rb"); 
	if (fp == NULL) {
		printf("파일을 읽지 못했습니다.");
		return 1;
	}
	bh.bmpType[0] = fgetc(fp);
	bh.bmpType[1] = fgetc(fp);
	printf("Header : %c%c\n", bh.bmpType[0], bh.bmpType[1]);

	fgetc(fp);

	fclose(fp);


	return 0;
}
```

---
<img width="1111" height="179" alt="image" src="https://github.com/user-attachments/assets/751857ec-6051-485b-b378-8fca84de86d9" />

---


## fseek하고 rewind 함수
```c
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

typedef unsigned char unit8_t;
typedef struct {
	unit8_t bmpType[2];
	unit8_t bmpSize[4];
	unit8_t bmpOffset[4];
	unit8_t bidSize[4];
	unit8_t bidWidth[4];
	unit8_t bidHeight[4];
	unit8_t bidColorPlane[2];
	unit8_t bidBitPerPixel[2];

} bmpHeader;

int main() {
	
	bmpHeader bh;

	FILE* fp = fopen("C:\\Users\\KCCISTC\\source\\repos\\251230\\251230\\car.bmp", "rb"); 
	if (fp == NULL) {
		printf("파일을 읽지 못했습니다.");
		return 1;
	}
	

	//fseek와 rewind? 
	fseek(fp, 2, SEEK_SET);
	bh.bmpSize[0] = fgetc(fp);
	bh.bmpSize[1] = fgetc(fp);
	bh.bmpSize[2] = fgetc(fp);
	bh.bmpSize[3] = fgetc(fp);
	rewind(fp);

	bh.bmpType[0] = fgetc(fp);
	bh.bmpType[1] = fgetc(fp);

	// 결합
	int size;
	memcpy(&size, bh.bmpSize, 4);

	printf("Header : %c%c\n", bh.bmpType[0], bh.bmpType[1]);
	printf("Size : %d\n", bh.bmpSize);

	fgetc(fp);

	fclose(fp);


	return 0;
}
```

---

---


## p
```c

```

---

