#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int matrix[0x400][0x400]; //store the path
int ans[0x400];//store answer
int queue[0x400];
int head,curr,flag;
void toZero()
{
    flag = 0;
    head = 0;
    curr = 0;
    memset(ans,0,sizeof(ans));
    memset(queue,0,sizeof(queue));
    memset(matrix,0,sizeof(matrix));
}

int main()
{
    int case_num,case_counter,people,dance_num,p1,p2,dance_counter;
    printf("%%>");
    scanf("%d",&case_num);
    for(case_counter = 0; case_counter < case_num; case_counter++)
    {
        toZero();
        printf("\n%%>");
        scanf("%d %d",&people,&dance_num);
        for(dance_counter = 0; dance_counter < dance_num; dance_counter++)
        {
            printf("%%>");
            scanf("%d %d",&p1,&p2);
            matrix[p1][p2]=1;//store the path
            matrix[p2][p1]=1;
        }
        for(int i = 1; i < people; i++)
        {
            if (matrix[i][0]) //if have a path,then record
            {
                ans[i] += 1;
                queue[head] = i;
                head += 1;
            }
        }
        while(curr != head)
        {
            flag = queue[curr];//pop
            curr += 1;
            for(int i = 1; i < people; i++)
            {
                if (matrix[i][flag])
                {
                    if(!ans[i]||ans[flag] + 1 < ans[i]) //if the path isn't travel or the new path is shorter than older one
                    {
                        ans[i] = ans[flag]+1;//replace the older path
                        queue[head] = i;
                        head += 1;
                    }
                }
            }
        }
        printf("\n");
        for(int i = 1; i < people; i++)
        {
            printf("%%>%d\n",ans[i]);
        }
    }
    return 0;
}
