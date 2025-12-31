4장 : https://docs.google.com/presentation/d/1V1bjVgrihNcJ_4FaK6S2qolLYdmSefb_/edit?slide=id.p1#slide=id.p1

## 스택(stack)이란 ?
- 쌓아놓은 더미
- 후입선출(LIFO)
  - 가장 최근에 들어온 데이터가 먼저 나감

<img width="676" height="466" alt="image" src="https://github.com/user-attachments/assets/2889d3e5-0845-4dad-a95a-a8fd555e7fe3" />

## 스택 추상 데이터타입(ADT)
- 객체: 0개 이상의 원소를 가지는 유한 선형 리스트
- 연산:  
  - create(size) ::= 최대 크기가 size인 공백 스택을 생성한다.
  - is_full(s) ::= 
    - if(스택의 원소수 == size) return TRUE;
    - else return FALSE;
  - is_empty(s) ::= 
	  - if(스택의 원소수 == 0) return TRUE;
		- else return FALSE;

  - push(s, item) ::= 
    - if( is_full(s) ) return ERROR_STACKFULL;
    - else 스택의 맨 위에 item을 추가한다.
  - pop(s) ::= 
    - if( is_empty(s) ) return ERROR_STACKEMPTY;
    - else 스택의 맨 위의 원소를 제거해서 반환한다.
  - peek(s) ::= 
    - if( is_empty(s) ) return ERROR_STACKEMPTY;
    - else 스택의 맨 위의 원소를 제거하지 않고 반환한다. 

## 스택의 연산
- push(): 스택에 데이터를 추가
- pop(): 스택에서 데이터를 삭제

<img width="876" height="270" alt="image" src="https://github.com/user-attachments/assets/965e9dbd-e32f-4e6a-9428-bca534c08603" />

- is_empty(s): 스택이 공백상태인지 검사
- is_full(s): 스택이 포화상태인지 검사
- create(): 스택을 생성 
- peek(s): 요소를 스택에서 삭제하지 않고 보기만 하는 연산
    - (참고)pop 연산은 요소를 스택에서 완전히 삭제하면서 가져온다. 

## 배열을 이용한 스택의 구현
- 1차원 배열 stack[ ]
- 스택에서 가장 최근에 입력되었던 자료를 가리키는 top 변수
- 가장 먼저 들어온 요소는 stack[0]에, 가장 최근에 들어온 요소는 stack[top]에 저장
- 스택이 공백상태이면 top은 -1

## is_empty(S), is_full(S) 연산의 구현

<img width="869" height="525" alt="image" src="https://github.com/user-attachments/assets/a1b35e89-f97e-4e71-b098-0456835684e1" />

## push 연산
push(S, x): 
if is_full(S) 
     then error "overflow" 
     else top←top+1 
          stack[top]←x

<img width="500" height="298" alt="image" src="https://github.com/user-attachments/assets/a2ef262b-dd3f-4f49-9b7a-e3ce06d740d9" />

## pop 연산
pop(S, x): 
if is_empty(S) 
     then error "underflow" 
     else e←stack[top] 
          top←top-1 
          return e

<img width="560" height="309" alt="image" src="https://github.com/user-attachments/assets/07e96fe9-d729-4d53-b25b-e9bd68870ca8" />

## 전역 변수로 구현하는 방법

### p
```c
#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 100	// 스택의 최대 크기
typedef int element;		// 데이터의 자료형
element  stack[MAX_STACK_SIZE]; // 1차원 배열
int  top = -1;

// 공백 상태 검출 함수
int is_empty()
{
	return (top == -1);
}
// 포화 상태 검출 함수
int is_full()
{
	return (top == (MAX_STACK_SIZE - 1));
}
// 삽입 함수
void push(element item)
{
	if (is_full()) {
		fprintf(stderr, "스택 포화 에러\n");
		return;
	}
	else stack[++top] = item;
}
// 삭제 함수
element pop()
{
	if (is_empty()) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else return stack[top--];
}
int main(void)
{
	push(1);
	push(2);
	push(3);
	printf("%d\n", pop());
	printf("%d\n", pop());
	printf("%d\n", pop());
	return 0;
}
```

<img width="1102" height="204" alt="image" src="https://github.com/user-attachments/assets/f39f2d2f-5f5d-4148-b8de-36e080b8c85f" />

---

## 구조체 배열 사용하기

```c
#define MAX_STACK_SIZE 100
#include<stdio.h>

typedef int element;
typedef struct {
	element data[MAX_STACK_SIZE];
	int top;
} StackType;

// 스택 초기화 함수
void init_stack(StackType* s)
{
	s->top = -1;
}

// 공백 상태 검출 함수
int is_empty(StackType* s)
{
	return (s->top == -1);
}
// 포화 상태 검출 함수
int is_full(StackType* s)
{
	return (s->top == (MAX_STACK_SIZE - 1));
}
// 삽입함수
void push(StackType* s, element item)
{
	if (is_full(s)) {
		fprintf(stderr, "스택 포화 에러\n");
		return;
	}
	else s->data[++(s->top)] = item;
}
// 삭제함수
element pop(StackType* s)
{
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else return s->data[(s->top)--];
}
int main(void)
{
	StackType s;

	init_stack(&s);
	push(&s, 1);
	push(&s, 2);
	push(&s, 3);
	printf("%d\n", pop(&s));
	printf("%d\n", pop(&s));
	printf("%d\n", pop(&s));
}

```

<img width="1105" height="204" alt="image" src="https://github.com/user-attachments/assets/7d711e30-88c4-43b5-89cd-df7faa4f922e" />

---


## 동적 배열 스택

```c
#define MAX_STACK_SIZE 100
#include<stdio.h>
#include<stdlib.h>

typedef int element;
typedef struct {
	element data[MAX_STACK_SIZE];
	int top;
} StackType;


// 스택 초기화 함수
void init_stack(StackType* s)
{
	s->top = -1;
}

// 공백 상태 검출 함수
int is_empty(StackType* s)
{
	return (s->top == -1);
}
// 포화 상태 검출 함수
int is_full(StackType* s)
{
	return (s->top == (MAX_STACK_SIZE - 1));
}
// 삽입함수
void push(StackType* s, element item)
{
	if (is_full(s)) {
		fprintf(stderr, "스택 포화 에러\n");
		return;
	}
	else s->data[++(s->top)] = item;
}

// 삭제함수
element pop(StackType* s)
{
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else return s->data[(s->top)--];
}
int main(void)
{
	StackType s;
	init_stack(&s);
	push(&s, 1);
	push(&s, 2);
	push(&s, 3);
	printf("%d\n", pop(&s));
	printf("%d\n", pop(&s));
	printf("%d\n", pop(&s));
	return 0;
}


```

<img width="1106" height="195" alt="image" src="https://github.com/user-attachments/assets/26ef4f2c-d239-463c-b0c8-2fa66518f62a" />

---

# 수식의 계산
- 수식 표기 방법 : 전위(prefix), 중위(infix), 후위(postfix)

  <img width="975" height="187" alt="image" src="https://github.com/user-attachments/assets/dd5b1394-a449-4f5a-9e55-444e7914419c" />

- 컴퓨터에서의 수식 계산 순서
  - 중위 표기식 -> 후위 표기식 -> 계산
  - 2+3*4 -> 234*+ -> 14
  - 모두 스택을 사용
  - 먼저 후위표기식의 계산법을 알아보자
 		- 수식을 왼쪽에서 오른쪽으로 스캔하여 피연산자이면 스택에 저장하고 연산자이면 필요한 수만큼의 피연산자를 스택에서 꺼내 연산을 실행하고 연산의 결과를 다시 스택에 저장

		- 예) 82/3-32*+

<img width="340" height="312" alt="image" src="https://github.com/user-attachments/assets/e33f47ed-6ff4-4b9f-afcf-5b525d1fec29" />

<img width="718" height="690" alt="image" src="https://github.com/user-attachments/assets/6a6fdd64-eb9f-49d0-8eab-9966daca9082" />

## 후위표기식 계산 알고리즘

<img width="802" height="351" alt="image" src="https://github.com/user-attachments/assets/abce7851-be04-44d7-b81c-811ea5b5704b" />

<후위 표기식 계산>
```c
#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 100

typedef char element;	
typedef struct {
	element* data;
	int capacity;
	int top;
} StackType;

int eval(char exp[])
{
	int op1, op2, value, i = 0;
	int len = strlen(exp);
	char ch;
	StackType s;
	init_stack(&s);
	for (i = 0; i < len; i++) {
		ch = exp[i];
		if (ch != '+' && ch != '-' && ch != '*' && ch != '/') {
			value = ch - '0';	// 입력이 피연산자이면
			push(&s, value);
		}
		else {	//연산자이면 피연산자를 스택에서 제거
			op2 = pop(&s);
			op1 = pop(&s);
			switch (ch) { //연산을 수행하고 스택에 저장 
			case '+': push(&s, op1 + op2); break;
			case '-': push(&s, op1 - op2); break;
			case '*': push(&s, op1 * op2); break;
			case '/': push(&s, op1 / op2); break;
			}
		}
	}
	return pop(&s);
}
int main(void)
{
	int result;
	printf("후위표기식은 82/3-32*+\n");
	result = eval("82/3-32*+");
	printf("결과값은 %d\n", result);
	return 0;
}
```

<img width="1111" height="188" alt="image" src="https://github.com/user-attachments/assets/eeb36280-f6b5-4452-98c9-987248781212" />



