#include <stdio.h>

typedef struct _Student{
    int id; // 4
    char name[20]; // 20
    double score; // 8
    struct _Student *s; // 8

}Student; // 32

// 주소는 항상 8바이트 ?

int main(){

    Student ary[3];
    printf("배열 전체 크기: %d\n", sizeof(ary));
    printf("구조체 한 개의 크기: %d\n", sizeof(Student));

    printf("배열의 요소 개수: %d\n",sizeof(ary)/sizeof(ary[0]));

    return 0;
}