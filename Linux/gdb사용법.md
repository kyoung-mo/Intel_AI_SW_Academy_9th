# GDB 디버깅 실습 정리 (Hello World 예제)

본 문서는 `hello.c` 예제를 대상으로 GDB를 사용해 디버깅한 과정을 정리한 문서이다.  
지역 변수 초기화 시점, 스택 메모리 배치, GDB 명령어의 의미를 이해하는 것을 목표로 한다.

---

## 1. 디버깅 환경

- OS: Ubuntu (x86_64)
- Compiler: gcc
- Debugger: GNU gdb 15.x
- 컴파일 옵션:

```bash
gcc -g -O0 -o hello_d hello.c
```

- `-g`: 디버그 심볼 포함
- `-O0`: 최적화 비활성화 (디버깅 정확도 향상)

---

## 2. GDB 실행 및 main 진입

```gdb
gdb ./hello_d
(gdb) start
```

출력:

```text
Temporary breakpoint 1, main () at hello.c:4
4    int a = 10;
```

- `start` 명령은 `main()` 진입 직후에서 멈춘다.
- 이 시점에서는 아직 해당 라인의 코드가 **실행되지 않았다**.

---

## 3. 지역 변수와 초기화 시점

### 3.1 초기화 전 변수 값 (쓰레기 값)

```gdb
(gdb) p a
$1 = -8160
```

- `int a = 10;` 라인이 **아직 실행되지 않았기 때문**
- 스택 메모리에 할당만 되었고 값은 초기화되지 않음

### 3.2 next 실행 후

```gdb
(gdb) next
(gdb) p a
$2 = 10
```

- `next` 실행으로 해당 라인이 수행됨
- 정상적인 초기값 확인 가능

---

## 4. 콤마 연산자 주의 (`p b, c`)

```gdb
(gdb) p b, c
$3 = -8088
```

이는 다음과 동일한 의미이다:

```c
(b, c)
```

- `b`는 평가만 되고
- **출력 결과는 `c`**
- `c`는 아직 초기화되지 않아 쓰레기 값 출력

정확한 확인 방법:

```gdb
p b
p c
```

---

## 5. char / float 변수도 동일한 원리

### char 변수

```gdb
(gdb) p d
$4 = 0 '\0'
```

```gdb
(gdb) next
(gdb) p d
$5 = 97 'a'
```

### float 변수

```gdb
(gdb) p e
$6 = 4.59e-41   // 초기화 전
```

```gdb
(gdb) next
(gdb) p e
$7 = 3.14159012
```

- 모든 지역 변수는 **실행되기 전까지는 값이 보장되지 않음**

---

## 6. 스택 메모리 주소 배치

```gdb
&a = 0x7fffffffdf30
&b = 0x7fffffffdf34
&c = 0x7fffffffdf38
&d = 0x7fffffffdf2f
&e = 0x7fffffffdf3c
```

| 변수 | 타입  | 크기 | 주소 예시 |
|----|----|----|----|
| d | char  | 1B | df2f |
| a | int   | 4B | df30 |
| b | int   | 4B | df34 |
| c | int   | 4B | df38 |
| e | float | 4B | df3c |

- 스택은 **주소 감소 방향**으로 성장
- 정렬(alignment) 규칙에 따라 배치됨

---

## 7. libc 관련 경고 메시지

```text
__libc_start_call_main ...
No such file or directory
```

- 프로그램 종료 이후 libc 내부 코드 진입
- glibc 소스가 로컬에 없어서 발생하는 경고
- **디버깅 대상 아님**
- 무시해도 무방

---

## 8. 핵심 정리

- `start`는 main 진입 시점에서 멈춘다
- 지역 변수는 **실행 전에는 쓰레기 값**
- `next`는 한 줄 실행
- GDB의 `p`는 C 문법을 그대로 따른다
- 스택 주소를 통해 메모리 구조를 직관적으로 확인 가능
- 현재 디버깅 상태는 **완전히 정상**

---

## 9. 다음 단계 추천

- 포인터 변수 선언 후 `*p`, `&p` 추적
- 배열 선언 후 주소 증가 확인
- 함수 호출 + `step` 진입
- `info locals`, `info frame` 사용
- `x/` 명령으로 메모리 직접 확인

---

이 문서는 **C 언어 + GDB + 메모리 구조 이해**를 위한 기초 정리 자료로 활용 가능하다.
