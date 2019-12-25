#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int matrix[200][200];
int distance[200];
int found[200];
int pathmap[200][200];
int num_planet;
int choose()
{
    int min = 0xDEAD, min_num = -1;
    for(int i = 1; i <= num_planet; i++)
    {
        if(distance[i] < min && !found[i])
        {
            min = distance[i];
            min_num = i;
        }
    }
    return min_num;
}
void shortestpath(int start)
{
    int min_num;
    for(int i = 1; i <= num_planet; i++)
    {
        found[i] = 0;
        distance[i] = matrix[start][i];
    }
    found[start] = 1;
    distance[start] = 0;
    for(int i = 1; i <= num_planet - 2; i++)
    {
        min_num = choose();
        found[min_num] = 1;
        for(int j = 1; j <= num_planet; j++)
        {
            if (!found[j])
            {
                if (distance[min_num] + matrix[min_num][j] < distance[j])
                    distance[j] = distance[min_num] + matrix[min_num][j];
            }
        }
    }
}
void tozero()
{
    for(int i=0; i<200; i++)
        for(int j=0; j<200; j++)
            matrix[i][j]=1000;
    memset(distance,0,sizeof(distance));
    memset(found,0,sizeof(found));
}
int main()
{
    int num_case,counter_case,num_egde,counter_edge,p1,p2,edge,max,answer=0;
    printf("%%>");
    scanf("%d",&num_case);
    for(counter_case = 0; counter_case < num_case; counter_case++)
    {
        tozero();
        printf("%%>");
        scanf("%d %d",&num_planet,&num_egde);
        for(counter_edge = 0; counter_edge < num_egde; counter_edge++)
        {
            printf("%%>");
            scanf("%d %d %d",&p1,&p2,&edge);
            matrix[p1][p2] = edge;
            matrix[p2][p1] = edge;
        }
        for(int i = 1; i <= num_planet; i++)
        {
            shortestpath(i);
            for(int j = 1; j <= num_planet; j++)
            {
                pathmap[i][j] = distance[j];
            }
        }
        for(int i = 1; i <= num_planet; i++){
            for(int j = 1; j <= num_planet; j++){
                    max = 0;
                    if(i == j)continue;
                for(int counter = 1; counter <= num_planet; counter++){
                    if(pathmap[i][counter] >= pathmap[j][counter])
                        max += 1;
                }
                if(answer < max)
                    answer = max;
            }
        }
        printf("\n%%>%d\n",answer);
    }
    return;
}
