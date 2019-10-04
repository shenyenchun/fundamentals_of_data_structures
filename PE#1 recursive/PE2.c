#include<stdio.h>
#include<stdlib.h>

int time,bin[100]={0};                                      //time做了幾次短除法的counter，bin是存放%-2的餘數
void Function(int n){
    time++;                                                 //每call一次 紀錄一次
    if (n==0||n==1){                                        //如果為1或0直接紀錄並結束
        bin[time-1]=abs(n);
    }
    else{
        if (n<0){                                           //針對待處理為負數
            if (n%(-2)!=0){                                 //針對餘數非零動作
                bin[time-1]=abs(n%(-2));                    //紀錄餘數
                Function(n/(-2)+1);
            }
            else{
                bin[time-1]=abs(n%(-2));                    //紀錄餘數
                Function(n/(-2));
            }
        }
        else{                                               //針對待處理為正數
            bin[time-1]=abs(n%(-2));                        //紀錄餘數
            Function(n/(-2));
        }
    }
}
int main(){
    int Case,num;
    scanf("%d",&Case);                                      //樣本總數

    for(int i=0;i<Case;i++){
        time=0;                                             //每做一筆測資歸零
        scanf("%d",&num);
        Function(num);
        for(int j=time-1;j>=0;j--){
            printf("%d",bin[j]);
        }
        printf("\n");
    }
    return 0;
}
