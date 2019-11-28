#include <stdio.h>
#include <stdlib.h>
#define max 1000
int num[100],index=0;

typedef struct node
{
    int value;
} node;
node heap[max];

void insert(int num)
{
    int i;
    i = ++(index);
    if(!heap[1].value)
    {
        heap[1].value=num;
        return;
    }
    while((i != 1)&&(num < heap[i/2].value))
    {
        heap[i]=heap[i/2];
        i /= 2;
    }
    heap[i].value=num;
}

int delete_min_heap()
{
    int padre,nino;
    node item,tmp;
    item = heap[1];
    tmp = heap[index--];
    padre = 1;
    nino = 2;
    while(nino<=index)
    {
        if((nino<index)&&heap[nino].value>heap[nino+1].value)
            nino++;
        if(tmp.value<=heap[nino].value)
            break;
        heap[padre] = heap[nino];
        padre = nino;
        nino *= 2;
    }
    heap[padre] = tmp;
    return item.value;
}
int main()
{
    FILE *fptr;
    fptr = fopen("myInput.txt","r");
    int Case,min1,min2,cost=0,total_cost=0;
    while(fscanf(fptr,"%d",&Case)!=EOF)
    {
        cost=0;
        total_cost=0;
        index=0;

        for(int i=1; i<=Case; i++)
            fscanf(fptr,"%d",&num[i]);

        for(int i=1; i<=Case; i++)
            insert(num[i]);

        while(index>1)
        {
            min1 = delete_min_heap();
            min2 = delete_min_heap();
            cost = min1+min2;
            total_cost += cost;
            insert(min1+min2);
        }

        printf("%d\n",total_cost);
    }
}
