2장 : https://docs.google.com/presentation/d/12SCbli6VnP98cxGHsJpy-113KRj9xpjS/edit?slide=id.p19#slide=id.p19

## 순환(recursion)이란?
- 알고리즘이나 함수가 수행 도중에 자기 자신을 다시 호출하여 문제를 해결하는 기법
- 정의 자체가 순환적으로 되어 있는 경우에 적합

<img width="675" height="218" alt="image" src="https://github.com/user-attachments/assets/4e29102b-6243-4566-8934-c1c1d5b53311" />

### 팩토리얼 1
int factorial(int n)
{
    if( n<= 1 ) return(1);
    else return (n * factorial_n_1(n-1) );
}

### 팩토리얼 2
int factorial(int n)
{
    if( n <= 1 ) return(1);
    else return (n * factorial(n-1) );
}

- 순환을 멈추는 부분이 있어야 한다.
- 대부분의 순환은 "반복" 으로 바꿔 작성 가능하다.

<img width="858" height="411" alt="image" src="https://github.com/user-attachments/assets/d42b729c-db6a-4299-98d8-514cdd970e15" />

- 숫자 x의 n제곱 값을 구하는 문제: x^n

double slow_power(double x, int n)
{
	int i;
	double result = 1.0;
	for(i=0; i<n; i++)
		result = result * x;
	return(result);
}

- 순환적인 알고리즘
power(x, n)

if n==0 
	then return 1;
else if n이 짝수 
	then return power(x2, n/2);
else if n이 홀수  
	then return x*power(x2, (n-1)/2);
  
double power(double x, int n)
{
	if( n==0 ) return 1;
	else if ( (n%2)==0 ) 
		return power(x*x, n/2);
	else return x*power(x*x, (n-1)/2);
}

### 거듭제곱 값 프로그래밍 분석
- 시간 복잡도
  - 반복적인 방법과 순환적인 방법의 비교

    <img width="704" height="109" alt="image" src="https://github.com/user-attachments/assets/972b4266-bb9a-4245-807d-aaa5daafbedd" />

### 피보나치 수열 계산 1)
- 순환 호출시 비효율적인 예시이다.
int fib(int n)
{
    if( n==0 ) return 0;
    if( n==1 ) return 1;
    return (fib(n-1) + fib(n-2));
}
- 순환 호출을 사용했을 경우의 비효율성 
  - 같은 항이 중복해서 계산됨 
  - 예를 들어 fib(6)을 호출하게 되면 fib(3)이 4번이나 중복되어서 계산됨
  - 이러한 현상은 n이 커지면 더 심해짐

### 피보나치 수열의 반복 구현

int fib_iter(int n)
{
    if (n == 0) return 0;
    if (n == 1) return 1;
        
    int pp = 0;	
    int p = 1;
    int result = 0;
        
    for (int i = 2; i <= n; i++) {
        result = p + pp;
        pp = p;
        p = result;
    }
    return result;
} 


### 하노이 탑 문제

- 문제는 막대 A에 쌓여있는 원판 n개를 막대 C로 옮기는 것이다. 
  - 한 번에 하나의 원판만 이동할 수 있다 
  - 맨 위에 있는 원판만 이동할 수 있다 
  - 크기가 작은 원판 위에 큰 원판이 쌓일 수 없다. 
  - 중간의 막대를 임시적으로 이용할 수 있으나 앞의 조건들을 지켜야 한다.
 
  <img width="521" height="190" alt="image" src="https://github.com/user-attachments/assets/a322aba8-e03a-48af-a09f-f69e046249c6" />



