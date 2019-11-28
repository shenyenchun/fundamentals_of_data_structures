#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char name[20]; //名字
    int arr_time; //到達時間
    int ser_time; //需要時間
    int leave_time;// 離開時間
    int windows;//窗口
    struct ppl *next; //next pointer
} ppl;


int counter_num;
int flag_time=0;


typedef struct
{
    ppl *head; //
    ppl *bottom;
    int line_people;
    int work;
    int process_time;
} counter;

counter worker[10];

void new_counter()
{
    for(int i = 0; i<10; i++)
    {
        worker[i].bottom = NULL;
        worker[i].head = NULL;
        worker[i].line_people = 0;
        worker[i].process_time = 0;
        worker[i].work = 0;
    }
    for(int j =0;j<counter_num;j++)
        worker[j].work = 1;
    //printf("counter setup\n");
}
void counter_open(int windows)
{
    worker[windows].work = 1;

}

void remove_customer(ppl *customer,FILE *outptr)
{
    printf("%s %d %d\n",customer->name,worker[customer->windows].process_time,customer->windows);

    worker[customer->windows].head = worker[customer->windows].head->next;
    //printf("%s",worker[customer->windows].head->name);
    if (worker[customer->windows].head)
    {
        customer->leave_time = worker[customer->windows].process_time;
        //printf("%d + %d \n",worker[customer->windows].process_time,worker[customer->windows].head->ser_time);
        worker[customer->windows].process_time += worker[customer->windows].head->ser_time;

    }
    worker[customer->windows].line_people-=1;
}

void timing(int time_point,FILE *outptr)
{

    for(; flag_time < time_point; flag_time++)
    {
        for(int i=0; i<10; i++)
        {
            if (worker[i].line_people!=0 && flag_time == worker[i].process_time)
                remove_customer(worker[i].head,outptr);
               // printf("1\n");
        }
    }
}

void counter_close(int windows)
{
    ppl *ptr;
    worker[windows].work = 0;
    if(worker[windows].head){

        ptr = worker[windows].head->next;
        worker[windows].bottom = worker[windows].head;
        worker[windows].bottom->next=NULL;
        if (worker[windows].line_people>1)
        {
            while(ptr)
            {
                check_counter(ptr);
                worker[windows].line_people-=1;

                //printf("%s",ptr->name);
                //if (ptr->next!=NULL)
                ptr = ptr->next;
                //else break;

            }
        }

    }

}

void check_counter(ppl *customer)  // check work -> line people
{
    int min = worker[0].line_people;
    int index = 0;
    for(int i=0; i<10; i++)
    {
        if (worker[i].work)
        {
            if (worker[i].line_people < min)
            {
                min = worker[i].line_people;
                index = i;
            }
        }
    }
    customer->windows = index;
    worker[index].line_people+=1;

    if (worker[index].head == NULL)
    {
        worker[index].head = customer;
        worker[index].bottom = customer;
        worker[index].process_time = customer->ser_time + customer->arr_time;
    }
    else
    {
        worker[index].bottom->next = customer;
        worker[index].bottom = worker[index].bottom->next;
        //worker[index].process_time = worker[index].process_time + customer->ser_time;
    }
    //printf("windows:%d\n",customer->windows);
    //printf("check sucess\n");

}

void add_customer(char *name,int arr_time,int ser_time)
{
    ppl *add_new;
    add_new = malloc(sizeof(ppl));
    add_new->arr_time = arr_time;
    add_new->leave_time = 0;
    strcpy(add_new->name,name);
    add_new->ser_time = ser_time;
    add_new->windows = 0;
    add_new->next = NULL;
    //printf("name: %s arr_time:%d ser_time:%d\n",add_new->name,add_new->arr_time,add_new->ser_time);


    check_counter(add_new);

}

void counter_situtation(int windows)
{
    //printf("check counter");
    ppl *customer;
    customer = worker[windows].head;

    while(customer!=worker[windows].bottom->next)
    {
        printf("%s\n",customer->name);
        customer = customer->next;
    }

}


int main()
{
    char file[10];
    int time_point,windows,ser_time;
    char commamd[20];
    scanf("%s",file);
    FILE *ptr = fopen(file,"r");
    FILE *outptr = fopen("out.txt","w");
    fscanf(ptr,"%d",&counter_num);
    new_counter();

    while(fscanf(ptr,"%s",commamd)!=EOF)
    {
        if (commamd[0]=='@')
        {
            fscanf(ptr,"%d %d",&time_point,&windows);
            timing(time_point,outptr);
            counter_open(windows);
        }
        else if (commamd[0]=='$')
        {
            fscanf(ptr,"%d",&windows);
            counter_situtation(windows);
        }
        else if (commamd[0]=='#')
        {
            fscanf(ptr,"%d %d",&time_point,&windows);
            timing(time_point,outptr);
            counter_close(windows);
        }
        else
        {
            fscanf(ptr,"%d %d",&time_point,&ser_time);
            timing(time_point,outptr);
            add_customer(commamd,time_point,ser_time);

        }

    }
    timing(100000,outptr);

    return 0;
}
