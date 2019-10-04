#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    /*
    m,n是矩陣大小
    start_i,start_j是初始位置
    counter是移動的計數器
    way是隨機方向
    x,y是目前位置
    ptr是陣列index
    not0flag檢查非零的計數器
    */
    int m,n,start_i,start_j,counter=0,way,x=0,y=0,ptr=0,not0flag=1;
    FILE *fp;
    fp = fopen("D0776694_PE2.csv","w");
    srand(time(NULL));
    { //input
    scanf("%d",&n);
    scanf("%d",&m);
    scanf("%d",&start_i);
    scanf("%d",&start_j);
    }
    if (n<2||n>40||m<2||m>20) //防呆
    {
        printf("ERROR");
        return 0;
    }

    int *arr = calloc((m*n),sizeof(int)); //定義陣列大小

    x = start_i;
    y = start_j;

    arr[x*m+y]+=1;//初始位置採點

    while(counter<50000)
    {
        way =(rand()%8);

        switch (way) //根據隨機方向來加減位置
        {
        case 0:
            x+=1;
            y+=1;
            break;
        case 1:
            x+=1;
            break;
        case 2:
            x+=1;
            y-=1;
            break;
        case 3:
            y-=1;
            break;
        case 4:
            x-=1;
            y-=1;
            break;
        case 5:
            x-=1;
            break;
        case 6:
            x-=1;
            y+=1;
            break;
        case 7:
            y+=1;
            break;
        }

        if (x<0||x>=n||y<0||y>=m) //如果超過陣列回到上一個位置
        {
            switch(way)
            {
            case 0:
                x-=1;
                y-=1;
                break;
            case 1:
                x-=1;
                break;
            case 2:
                x-=1;
                y+=1;
                break;
            case 3:
                y+=1;
                break;
            case 4:
                x+=1;
                y+=1;
                break;
            case 5:
                x+=1;
                break;
            case 6:
                x+=1;
                y-=1;
                break;
            case 7:
                y-=1;
                break;
            }

        }
        else
        {
            ptr=x*m+y; //計算index
            if (arr[ptr]==0)
                not0flag+=1;//非零計數
            arr[ptr]+=1;//位置移動次數
            counter+=1;//總移動次數
        }



        if (not0flag==m*n) //如果全部的位置都非零就結束移動
            break;
    }

    fprintf(fp,"Total number of legal moves: %d\n", counter);

    for(int a=0;a<m*n;a++)
        fprintf(fp,"%d,%s",arr[a],(a%m==m-1)?"\n":"");

    fclose(fp);
    return 0;
}
