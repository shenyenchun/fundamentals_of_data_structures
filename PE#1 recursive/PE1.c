#include<stdio.h>
#include<stdlib.h>

int Function(int n){
    if (n==1) return 1;
    else return n * Function(n-1); //call n-1的階層
}
int main(){
    char n[2];
    int num;

    while(scanf("%s",&n)!=EOF){
        if(n[0]=='#'){
            break;
        }
        else{
            num = atoi(n); //把字串換整數
        }

        if(num > 10||num <1){
            printf("Error!\n");
            continue;
        }

    printf("%d\n",Function(num));
    }
    return 0;
}
