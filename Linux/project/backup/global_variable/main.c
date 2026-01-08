#include <stdio.h>
void show_status();
extern int g_max_level; // extern으로 할때는 초기화하면 안됌. 어딘가 있다는 의미로만

void main(){
    show_status();
    printf("현재 레벨 : %d\n",g_max_level);

    return;
}