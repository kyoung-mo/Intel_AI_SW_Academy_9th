6장 : [https://docs.google.com/presentation/d/1Xg4BNFt5drinjFWmprxzgoptJuVlEx0N/edit?slide=id.p5#slide=id.p5](https://docs.google.com/presentation/d/1Xg4BNFt5drinjFWmprxzgoptJuVlEx0N/edit?slide=id.p3#slide=id.p3)

## 큐(QUEUE)
- 먼저 들어온 데이터가 먼저 나가는 자료구조
- 선입선출(FIFO)

## 큐 ADT

<img width="919" height="620" alt="image" src="https://github.com/user-attachments/assets/7372b450-d314-4b06-88bf-7263330fd254" />

## 큐의 삽입, 삭제 연산

<img width="570" height="609" alt="image" src="https://github.com/user-attachments/assets/3e98731c-577e-4ac6-9b4e-a0a2aced607e" />

## 선형 큐
- 배열을 선형으로 사용하여 큐를 구현
  - 삽입을 계속하기 위해서는 요소들을 이동시켜야 함
 
<img width="822" height="338" alt="image" src="https://github.com/user-attachments/assets/45a1ac2b-a64b-4bd9-891e-66ee9f426ddb" />

# 선형 큐의 응용 : 작업 스케줄링

<img width="880" height="502" alt="image" src="https://github.com/user-attachments/assets/97b36131-9208-4122-bc85-a59ffa2fcdb6" />

# 원형 큐
- 선형 큐에서는 큐의 최대 크기에 도달하면 더이상 저장할 수 없다는 단점이 있어서 나옴
- 원형 큐 또한 전단과 후단을 관리하기 위해 2개의 변수(주로 front, rear) 존재

  <img width="769" height="537" alt="image" src="https://github.com/user-attachments/assets/49e0a842-ffa5-40ed-9d32-1df87978aa90" />

  - 공백 상태 : front == rear;
  - 포화 상태 : front % M == (rear+1) % M

```c
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

// ===== 원형큐 코드 시작 ======
#define MAX_QUEUE_SIZE 5
typedef int element;
typedef struct { // 큐 타입
	element  data[MAX_QUEUE_SIZE];
	int  front, rear;
} QueueType;

// 오류 함수
void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}
// 공백 상태 검출 함수
void init_queue(QueueType* q)
{
	q->front = q->rear = 0;
}

// 공백 상태 검출 함수
int is_empty(QueueType* q)
{
	return (q->front == q->rear);
}

// 포화 상태 검출 함수
int is_full(QueueType* q)
{
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}
// 원형큐 출력 함수
void queue_print(QueueType* q)
{
	printf("QUEUE(front=%d rear=%d) = ", q->front, q->rear);
	if (!is_empty(q)) {
		int i = q->front;
		do {
			i = (i + 1) % (MAX_QUEUE_SIZE);
			printf("%d | ", q->data[i]);
			if (i == q->rear)
				break;
		} while (i != q->front);
	}
	printf("\n");
}
// 삽입 함수
void enqueue(QueueType* q, element item)
{
	if (is_full(q))
		error("큐가 포화상태입니다");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
}

// 삭제 함수
element dequeue(QueueType* q)
{
	if (is_empty(q))
		error("큐가 공백상태입니다");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}
int main(void)
{
	QueueType queue;
	int element;

	init_queue(&queue);
	printf("--데이터 추가 단계--\n");
	while (!is_full(&queue))
	{
		printf("정수를 입력하시오: ");
		scanf("%d", &element);
		enqueue(&queue, element);
		queue_print(&queue);
	}
	printf("큐는 포화상태입니다.\n\n");

	printf("--데이터 삭제 단계--\n");
	while (!is_empty(&queue))
	{
		element = dequeue(&queue);
		printf("꺼내진 정수: %d \n", element);
		queue_print(&queue);
	}
	printf("큐는 공백상태입니다.\n");
	return 0;
}
```

<img width="1107" height="561" alt="image" src="https://github.com/user-attachments/assets/5b3f84d2-3f10-4882-bc97-1d40066d91f4" />

---

## 덱? (deque)
- deque는 double-ended queue의 줄임말로, 큐의 전단(front)과 후단(rear)에서 모두 삽입과 삭제가 가능한 큐

<img width="822" height="213" alt="image" src="https://github.com/user-attachments/assets/8385c298-b9f4-4210-8d74-469489d3998a" />

## 덱 ADT

<img width="901" height="366" alt="image" src="https://github.com/user-attachments/assets/3c6babbc-b23a-4f68-b5b7-0b69502b9c6e" />

## 덱의 연산

<img width="608" height="508" alt="image" src="https://github.com/user-attachments/assets/7c0d58b7-b842-4f53-8339-39fb98e3ecea" />

## 배열을 이용한 덱의 구현

<img width="907" height="425" alt="image" src="https://github.com/user-attachments/assets/8313c34b-ceb0-46c2-85da-2e3e2e607765" />

## 프로그램

```c
#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 5
typedef int element;
typedef struct { // 큐 타입
	element  data[MAX_QUEUE_SIZE];
	int  front, rear;
} DequeType;

// 오류 함수
void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

// 초기화 
void init_deque(DequeType* q)
{
	q->front = q->rear = 0;
}
// 공백 상태 검출 함수
int is_empty(DequeType* q)
{
	return (q->front == q->rear);
}
// 포화 상태 검출 함수
int is_full(DequeType* q)
{
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}
// 원형큐 출력 함수
void deque_print(DequeType* q)
{
	printf("DEQUE(front=%d rear=%d) = ", q->front, q->rear);
	if (!is_empty(q)) {
		int i = q->front;
		do {
			i = (i + 1) % (MAX_QUEUE_SIZE);
			printf("%d | ", q->data[i]);
			if (i == q->rear)
				break;
		} while (i != q->front);
	}
	printf("\n");
}
// 삽입 함수
void add_rear(DequeType* q, element item)
{
	if (is_full(q))
		error("큐가 포화상태입니다");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
}

// 삭제 함수
element delete_front(DequeType* q)
{
	if (is_empty(q))
		error("큐가 공백상태입니다");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}
// 삭제 함수
element get_front(DequeType* q)
{
	if (is_empty(q))
		error("큐가 공백상태입니다");
	return q->data[(q->front + 1) % MAX_QUEUE_SIZE];
}

void add_front(DequeType* q, element val)
{
	if (is_full(q))
		error("큐가 포화상태입니다");
	q->data[q->front] = val;
	q->front = (q->front - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
}
element delete_rear(DequeType* q)
{
	int prev = q->rear;
	if (is_empty(q))
		error("큐가 공백상태입니다");
	q->rear = (q->rear - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
	return q->data[prev];
}

element get_rear(DequeType* q)
{
	if (is_empty(q))
		error("큐가 공백상태입니다");
	return q->data[q->rear];
}
int main(void)
{
	DequeType queue;

	init_deque(&queue);
	for (int i = 0; i < 3; i++) {
		add_front(&queue, i);
		deque_print(&queue);
	}
	for (int i = 0; i < 3; i++) {
		delete_rear(&queue);
		deque_print(&queue);
	}
	return 0;
}
```

<img width="1112" height="259" alt="image" src="https://github.com/user-attachments/assets/8f4ae30c-2e14-43c2-837a-9fa879c8dc68" />






