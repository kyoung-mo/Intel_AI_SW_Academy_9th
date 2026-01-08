#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    int id;
    char name[20];
    double score;
}Student;

// 비교 로직을 함수 포인터로 전달

int compare_id(const void *a, const void *b) {
    const Student* aa=(const Student*)a;
    const Student* bb=(const Student*)b;
    
    return(aa->id-bb->id);
}

int compare_name(const void *a, const void *b) {
    
    const Student* aa=(const Student*)a;
    const Student* bb=(const Student*)b;
    
    return(strcmp(aa->name,bb->name));
    
}

int compare_score(const void *a, const void *b) {
    
    const Student* aa=(const Student*)a;
    const Student* bb=(const Student*)b;

    // double형 형변환->비교시 1보다 작은 값이 0으로 처리될 수 있음을 주의
    // 안 좋은예 : return(bb->score-aa->score);
    if(aa->score > bb->score) return -1;
    else if(aa->score < bb->score) return 1;
    else return 0;
}

int main() {
    
    Student students[5]={
        {101, "김철수", 85.5},
        {102, "이영희", 92.0},
        {103, "박민수", 78.5},
        {104, "최지우", 95.0},
        {105, "정수민", 88.5}
    };
    
    int n = sizeof(students) / sizeof(students[0]);
    int i;



    printf("\n");

    qsort(students,n,sizeof(Student),compare_id);
    printf("ID \t 이름 \t 점수 \n");
    for(i=0;i<n;i++){
        printf("%d\t%s\t %.1lf\n",students[i].id,students[i].name,students[i].score);
    }
    
    printf("\n");

    qsort(students,n,sizeof(Student),compare_name);
    printf("ID \t 이름 \t 점수 \n");
    for(i=0;i<n;i++){
        printf("%d\t%s\t %.1lf\n",students[i].id,students[i].name,students[i].score);
    }
    
    printf("\n");

    qsort(students,n,sizeof(Student),compare_score);
    printf("ID \t 이름 \t 점수 \n");
    for(i=0;i<n;i++){
        printf("%d\t%s\t %.1lf\n",students[i].id,students[i].name,students[i].score);
    }

   
    return 0;
}