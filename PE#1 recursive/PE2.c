#include<stdio.h>
#include<stdlib.h>

int time,bin[100]={0};                                      //time���F�X���u���k��counter�Abin�O�s��%-2���l��
void Function(int n){
    time++;                                                 //�Ccall�@�� �����@��
    if (n==0||n==1){                                        //�p�G��1��0���������õ���
        bin[time-1]=abs(n);
    }
    else{
        if (n<0){                                           //�w��ݳB�z���t��
            if (n%(-2)!=0){                                 //�w��l�ƫD�s�ʧ@
                bin[time-1]=abs(n%(-2));                    //�����l��
                Function(n/(-2)+1);
            }
            else{
                bin[time-1]=abs(n%(-2));                    //�����l��
                Function(n/(-2));
            }
        }
        else{                                               //�w��ݳB�z������
            bin[time-1]=abs(n%(-2));                        //�����l��
            Function(n/(-2));
        }
    }
}
int main(){
    int Case,num;
    scanf("%d",&Case);                                      //�˥��`��

    for(int i=0;i<Case;i++){
        time=0;                                             //�C���@�������k�s
        scanf("%d",&num);
        Function(num);
        for(int j=time-1;j>=0;j--){
            printf("%d",bin[j]);
        }
        printf("\n");
    }
    return 0;
}
