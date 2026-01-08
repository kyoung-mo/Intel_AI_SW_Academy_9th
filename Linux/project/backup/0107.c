#include <stdio.h>

int main(){

    int arr[5][6]={0};
    int sum_row[4]={0};
    int sum_col[5]={0};
    int result=0;
    int cnt=1;
    int i,j;

    for(i=0;i<5;i++){
        
    }

    for(i =0;i<5;i++){
        for(j=0;j<6;j++){
            
            if((j>=0&&j<=4)&&(i>=0&&i<=3)){
                arr[i][j]=cnt;
                cnt++;
                sum_row[i]+=arr[i][j];
                sum_col[j]+=arr[i][j];
                result+=arr[i][j];
            }

            else if(j==5&&(i>=0&&i<=3)){  // 행 합 저장
                arr[i][j]=sum_row[i];
            }

            else if(i==4&&(j>=0&&j<=4)){
                arr[i][j]=sum_col[j];
            }

            else if(i==4&&j==5){
                arr[i][j]=result;
            }
            printf("%5d",arr[i][j]);
        }
        

        printf("\n");
    }



    return 0;
}