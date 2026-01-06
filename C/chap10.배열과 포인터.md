```c
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(){
	
	int arr[6];
	int i,j=0;

	for(i=0;i<6;i++){
		printf("[%d번째] 번호 입력 : ",i+1);
		scanf("%d",&arr[i]);

		while(1){
			if(arr[i]<1 || arr[i]>45){
				printf("1~45 사이의 숫자 입력하세요.\n");
				printf("[%d번째] 번호 입력 : ",i+1);
				scanf("%d",&arr[i]);
			}

			else break;
		}
		for(j=0;j<i;j++){
			
			if(arr[i]==arr[j]){
				printf("같은 번호가 있습니다!\n");

				while(1){
					printf("[%d번째] 번호 입력 : ",i+1);
					scanf("%d",&arr[i]);

					if(arr[i]!=arr[j]) break;
				}
			}
		}
	}

	printf("로또 번호 : ");
	for(i=0;i<6;i++) {
		printf("%d ",arr[i]);
		
	}
	
	
	return 0;
}

```

