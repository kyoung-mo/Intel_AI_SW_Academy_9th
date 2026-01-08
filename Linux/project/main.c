#include <stdio.h>
#include <stdlib.h>

// main_args abc + cde   argv[0]
// argv [1] => abc
// argv [2] => +    1 / 2
// argv [3] => cde
int main (int argc, char** argv){
    if(argc<4){
        printf("Usage abc + cde\n");
        printf("총 인자 개수(argc): %d\n",argc);  
        
        return 0;
    }
    printf("총 인자 개수(argc): %d\n",argc);
    for(int i=0;i<argc;i++){
        printf("argv[%d] = %s\n",i,argv[i]);
    }
    int a = atoi(argv[1]);

    return 0;

    // 형변환이후 함수 다시 만들고 동작하게
}
