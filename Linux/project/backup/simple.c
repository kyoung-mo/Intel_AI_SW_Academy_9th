
#include <stdio.h>


int sum(int a, int b);               // 두 정수를 더하는 함수
int mul(int a, int b);               // 두 정수를 곱하는 함수
int max(int a, int b);               // 두 정수 중에 큰 값을 구하는 함수

int main(void)
{
	int a, b;

	int (*fp)(int a, int b);
	scanf("%d %d",&a, &b );               // 메뉴 번호 입력

	fp = sum;
	int result = fp(a, b);
	printf("01 두 정수의 합: %d \n",result );   

	fp = mul;
	result = fp(a, b);
	printf("02 두 정수의 곱 : %d\n", result);

	fp = max;
	result = fp(a, b);
	printf("03 두 정수 중에서 큰 값 계산: %d\n", result);


	printf("원하는 연산을 선택하세요 : ");

	return 0;
}



int sum(int a, int b)        // 덧셈 함수
{
	return (a + b);
}

int mul(int a, int b)        // 곱셈 함수
{
	return (a * b);
}

int max(int a, int b)        // 큰 값을 구하는 함수
{
	if (a > b) return a;
	else return b;
}