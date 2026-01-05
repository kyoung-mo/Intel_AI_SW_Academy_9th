날짜 : 2026-01-05(월)

```c
#include <stdio.h>

int main(){
	int a=100;
	int b=200;
	int c=a+b;
	char d='a';
	float e= 3.14159;

	printf("%c\n",d);
	
	return 0;
}
```

위 코드에서 gdb를 통한 디버깅을 진행해보았다.  
vscode에서 아래와 같은 Extentions를 깔아주었다.  

<img width="266" height="400" alt="image" src="https://github.com/user-attachments/assets/30ef2f0c-ee58-4faf-bea1-2588d4cc2203" />

C/C++ Extention Pack을 깔고, vscode에서 c코드를 작성, 디버깅 하는 과정을 거쳤다.  
아래와 같이 break point를 설정하고, F5 -> gdb를 이용하여 디버깅을 진행하였다.  

<img width="685" height="303" alt="image" src="https://github.com/user-attachments/assets/9d67c0ea-7f9d-4777-af37-d95d1fe29b97" />

break point를 지날때마다, 변수가 쓰레기값에서 할당하고자 하는 값으로 넣어지며 초기화 되는  확인

<img width="272" height="195" alt="image" src="https://github.com/user-attachments/assets/44d7e696-a36a-45bc-bbc0-67aa98539650" />

각 변수가 저장된 주소, `sizeof(변수)` 명령어를 통해 각 변수의 크기를 확인하였다.

<img width="259" height="296" alt="image" src="https://github.com/user-attachments/assets/f75d4e15-d85c-439e-8b59-52502c60fd48" />

아래 사진은 변수 a가 저장된 주소 `&a=0x7fffffffdc80` 를 오프셋으로 한, Hex Editor 이다.

<img width="800" height="891" alt="image" src="https://github.com/user-attachments/assets/8cac580d-161f-4bb1-b7ff-38f96d6ffff2" />

아래 사진은 변수 d가 저장된 주소 `&d=0x7fffffffdc7f` 를 오프셋으로 한, Hex Editor 이다.

<img width="732" height="893" alt="image" src="https://github.com/user-attachments/assets/2065b25b-aa23-4c7e-a465-0299a6e64ebb" />

여기서 들었던 의문이였던 점은, 변수는 a, b, c, d, e 순서로 저장을 했는데
주소의 시작 값은 아래와 같았다.

```bash
&a = 0x7fffffffdc80
&b = 0x7fffffffdc84
&c = 0x7fffffffdc88
&d = 0x7fffffffdc7f
&e = 0x7fffffffdc8c
```

왜 d가 제일 먼저 저장되고, a, b, c, e 순으로 저장되었을까? 고민을 해보았다.  

a, b, c 는 int형 변수, d는 char형 변수, e는 float형 변수로,

각각의 크기는 다음과 같다.

```c
sizeof(a) = 4  // 4btye
sizeof(b) = 4  // 4btye
sizeof(c) = 4  // 4btye
sizeof(d) = 1  // 1byte
sizeof(e) = 4  // 4btye
```

int와 float형 변수의 경우 4byte 정렬을 맞추기 위해 연속된 4의 배수 주소에 배치되는 것이 유리하다.  
만약 char형 변수 d가 int나 float 사이에 소스 코드 순서대로 배치된다면, 이후에 오는 4바이트 정렬이 필요한 변수의 정렬을 맞추기 위해   
바이트 단위의 패딩이 추가될 수 있다. 그러나 본 실험에서는 컴파일러가 정렬 효율을 고려하여 char형 변수 d를 4바이트 경계 바로 앞에 배치하고,    
int와 float형 변수들을 4바이트 정렬된 영역에 연속적으로 배치함으로써 불필요한 패딩을 최소화하였다.

- 정렬(alignment)이란?
  - CPU는 특정 타입을 특정 주소 배수에서 접근할 때 가장 효율적이다.
  - char형은 어디에 있어도 상관 없음
  - int/float는 주소가 4의 배수여야 효율적
 




