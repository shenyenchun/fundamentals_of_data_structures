#include<stdio.h>
#include<stdlib.h>

int Function(int n){
    if (n==1) return 1;
    else return n * Function(n-1); //call n-1�����h
}
int main(){
    char n[2];
    int num;

    while(scanf("%s",&n)!=EOF){
        if(n[0]=='#'){
            break;
        }
        else{
            num = atoi(n); //��r�괫���
        }

        if(num > 10||num <1){
            printf("Error!\n");
            continue;
        }

    printf("%d\n",Function(num));
    }
    return 0;
}
