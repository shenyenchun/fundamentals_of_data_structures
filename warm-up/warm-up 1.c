#include <stdio.h>
#include <stdlib.h>


void Swap(int *a,int *b){
    int tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;

}
int main()
{
    int num[1000]={},i=0;
    while(scanf("%d",&num[i])!=EOF){
        i++;
    }


    for(int j=0;j<i-1;j++){
        for(int k=0;k<i-j-1;k++){
            if(num[k]>num[k+1]){
                Swap(&num[k],&num[k+1]);
            }
        }
    }

    for(int q=0;q<i;q++){
        printf("%d ",num[q]);
    }

    return 0;
}
