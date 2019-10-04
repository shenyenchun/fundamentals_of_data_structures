#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    /*
    m,n�O�x�}�j�p
    start_i,start_j�O��l��m
    counter�O���ʪ��p�ƾ�
    way�O�H����V
    x,y�O�ثe��m
    ptr�O�}�Cindex
    not0flag�ˬd�D�s���p�ƾ�
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
    if (n<2||n>40||m<2||m>20) //���b
    {
        printf("ERROR");
        return 0;
    }

    int *arr = calloc((m*n),sizeof(int)); //�w�q�}�C�j�p

    x = start_i;
    y = start_j;

    arr[x*m+y]+=1;//��l��m���I

    while(counter<50000)
    {
        way =(rand()%8);

        switch (way) //�ھ��H����V�ӥ[���m
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

        if (x<0||x>=n||y<0||y>=m) //�p�G�W�L�}�C�^��W�@�Ӧ�m
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
            ptr=x*m+y; //�p��index
            if (arr[ptr]==0)
                not0flag+=1;//�D�s�p��
            arr[ptr]+=1;//��m���ʦ���
            counter+=1;//�`���ʦ���
        }



        if (not0flag==m*n) //�p�G��������m���D�s�N��������
            break;
    }

    fprintf(fp,"Total number of legal moves: %d\n", counter);

    for(int a=0;a<m*n;a++)
        fprintf(fp,"%d,%s",arr[a],(a%m==m-1)?"\n":"");

    fclose(fp);
    return 0;
}
