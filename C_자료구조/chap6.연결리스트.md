6장 : https://docs.google.com/presentation/d/1u_nU70NpE-6rVfz1ErC--drGG4BLK30w/edit?slide=id.p1#slide=id.p1

## 리스트란 ?
- 리스트에 새로운 항목 추가(삽입)
- 항목 삭제(삭제)
- 항목 찾기(탐색)

## 리스트 ADT

<img width="912" height="378" alt="image" src="https://github.com/user-attachments/assets/f1b50f3d-09ed-4430-ac14-9361ea572d0c" />

## 리스트 구현 방법

<img width="810" height="280" alt="image" src="https://github.com/user-attachments/assets/041335c7-5ce9-4270-98f2-2e4f9900c428" />

## 배열로 구현된 리스트

- 배열을 이용하여 리스트를 구현하면 순차적인 메모리 공간이 할당된다 : 순차적 표현(Sequential representation)

  <img width="341" height="121" alt="image" src="https://github.com/user-attachments/assets/365efa13-b595-48e3-9d5c-f62abd82c3bf" />


## 프로그램

```c
#include <stdio.h>
#define MAX_LIST_SIZE 100 // 리스트의 최대크기

typedef int element; // 항목의 정의

typedef struct {
	element array[MAX_LIST_SIZE]; // 배열 정의
	int size; // 현재 리스트에 저장된 항목들의 개수
} ArrayListType;
// 오류 처리 함수
void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}
// 리스트 초기화 함수
void init(ArrayListType* L)
{
	L->size = 0;
}
// 리스트가 비어 있으면 1을 반환
// 그렇지 않으면 0을 반환
int is_empty(ArrayListType* L)
{
	return L->size == 0;
}
// 리스트가 가득 차 있으면 1을 반환
// 그렇지 많으면 1을 반환
int is_full(ArrayListType* L)
{
	return L->size == MAX_LIST_SIZE;
}
element get_entry(ArrayListType* L, int pos)
{
	if (pos < 0 || pos >= L->size)
		error("위치 오류");
	return L->array[pos];
}
// 리스트 출력
void print_list(ArrayListType* L)
{
	int i;
	for (i = 0; i < L->size; i++)
		printf("%d->", L->array[i]);
	printf("\n");
}
void insert_last(ArrayListType* L, element item)
{
	if (L->size >= MAX_LIST_SIZE) {
		error("리스트 오버플로우");
	}
	L->array[L->size++] = item;
}
void insert(ArrayListType* L, int pos, element item)
{
	if (!is_full(L) && (pos >= 0) && (pos <= L->size)) {
		for (int i = (L->size - 1); i >= pos; i--)
			L->array[i + 1] = L->array[i];
		L->array[pos] = item;
		L->size++;
	}
}
element delete(ArrayListType* L, int pos)
{
	element item;

	if (pos < 0 || pos >= L->size)
		error("위치 오류");
	item = L->array[pos];
	for (int i = pos; i < (L->size - 1); i++)
		L->array[i] = L->array[i + 1];
	L->size--;
	return item;
}
int main(void)
{
	// ArrayListType를 정적으로 생성하고 ArrayListType를 	
	// 가리키는 포인터를 함수의 매개변수로 전달한다.
	ArrayListType list;

	init(&list);
	insert(&list, 0, 10);	print_list(&list);	// 0번째 위치에 10 추가
	insert(&list, 0, 20);	print_list(&list);	// 0번째 위치에 20 추가
	insert(&list, 0, 30);	print_list(&list);	// 0번째 위치에 30 추가
	insert_last(&list, 40);	print_list(&list);	// 맨 끝에 40 추가
	delete(&list, 0);		print_list(&list);	// 0번째 항목 삭제
	return 0;
}
```

<img width="1112" height="247" alt="image" src="https://github.com/user-attachments/assets/518eed98-6618-45b6-be9d-686fd88bb7cf" />

---

## 연결된 표현
- 리스트의 항목들을 노드(node)라고 하는 곳에 분산하여 저장
- 노드는 데이터 필드 / 링크 필드로 구성
  - 데이터 필드 : 리스트의 원소, 즉 데이터 값 저장하는 곳
  - 링크 필드 : 다른 노드의 주소값을 저장하는 곳(포인터)
 
## 특징
- 장점
  - 삽입, 삭제가 보다 용이하다.
  - 연속된 메모리 공간이 필요 없다.
  - 크기 제한이 없다.
- 단점
  - 구현이 어렵다.
  - 오류가 발생하기 쉽다.
 
## 노드의 구조
- 노드 = 데이터 필드 + 링크 필드

<img width="528" height="116" alt="image" src="https://github.com/user-attachments/assets/1afd8d7b-3eb3-437b-a3ab-d879f157fb34" />

## 연결 리스트의 종류
- 단순 연결 리스트
- 원형 연결 리스트
- 이중 연결 리스트

<img width="881" height="417" alt="image" src="https://github.com/user-attachments/assets/891b27dd-9bb8-452b-aa97-e481215dbf44" />

## 단순 연결 리스트
- 하나의 링크 필드를 이용하여 연결
- 마지막 노드의 링크 값은 NULL

<img width="876" height="143" alt="image" src="https://github.com/user-attachments/assets/a6de0c48-2bcf-4aa5-bc9b-70d84d559c9d" />

1) 노드의 정의

<img width="251" height="90" alt="image" src="https://github.com/user-attachments/assets/e9c28ff4-b94e-425d-b7c8-ff6ccaef341e" />

```c
typedef int element;

typedef struct ListNode { 	// 노드 타입을 구조체로 정의한다.
	element data;
	struct ListNode *link;
} ListNode;
```

2) 리스트의 생성

<img width="334" height="107" alt="image" src="https://github.com/user-attachments/assets/becbc23b-9f0a-4d77-99c3-b0882b7ed724" />

```c
ListNode *head = NULL;

head = (ListNode *)malloc(sizeof(ListNode)); 

head->data = 10;
head->link = NULL;
```

3) 2번째 노드 생성

<img width="664" height="98" alt="image" src="https://github.com/user-attachments/assets/5f8080f7-4c22-4a5d-bb0e-beb62039a891" />

```c
ListNode *p;
p = (ListNode *)malloc(sizeof(ListNode)); 
p->data = 20;
p->link = NULL; 
```

4) 노드의 연결 `head->link=p;`

<img width="473" height="72" alt="image" src="https://github.com/user-attachments/assets/0d959d6f-1d74-4dc9-b251-054c4c9e9c1c" />

## 단순 연결 리스트의 연산
- insert_first(): 리스트의 시작 부분에 항목을 삽입하는 함수
- insert(): 리스트의 중간 부분에 항목을 삽입하는 함수
- delete_first(): 리스트의 첫 번째 항목을 삭제하는 함수
- delete(): 리스트의 중간 항목을 삭제하는 함수
- print_list(): 리스트를 방문하여 모든 항목을 출력하는 함수

## 단순 연결리스트 (삽입 연산)

<img width="476" height="553" alt="image" src="https://github.com/user-attachments/assets/615016ee-149b-4124-82a4-98ecdd15d6d8" />

```c
ListNode* insert_first(ListNode *head, int value)
{
	ListNode *p =
	 (ListNode *)malloc(sizeof(ListNode));//(1)
	p->data = value;					// (2)
	p->link = head;		//(3)
	head = p;	//(4)
	return head;
}
// 노드 pre 뒤에 새로운 노드 삽입
ListNode*  insert(ListNode *head, ListNode *pre, element value)
{
	ListNode *p = (ListNode *)malloc(sizeof(ListNode));	//(1)
	p->data = value;		//(2)
	p->link = pre->link;	//(3)	
	pre->link = p;		//(4)	
	return head;		//(5)	
}
```

## 단순 연결리스트 (삭제 연산)

<img width="537" height="354" alt="image" src="https://github.com/user-attachments/assets/705da408-02a9-4d2d-8ea7-085c623ce2cb" />

```c
ListNode* delete_first(ListNode *head)
{
	ListNode *removed;
	if (head == NULL) return NULL;
	removed = head;	// (1)
	head = removed->link;	// (2)
	free(removed);		// (3)
	return head;		// (4)
}
// pre가 가리키는 노드의 다음 노드를 삭제한다. 
ListNode* delete(ListNode *head, ListNode *pre)
{
	ListNode *removed;
	removed = pre->link;
	pre->link = removed->link;		// (2)
	free(removed);			// (3)
	return head;			// (4)
}
```

## 방문 연산 코드

```c
void print_list(ListNode *head)
{
	for (ListNode *p = head; p != NULL; p = p->link)
		printf("%d->", p->data);
	printf("NULL \n");
}
```
