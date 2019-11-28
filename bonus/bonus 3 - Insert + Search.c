#include <stdio.h>
#include <stdlib.h>
/*
100 150 130 120 110 200 0 100
100 150 130 120 110 200 0 123
*/
typedef struct node
{
    int value;
    struct node *left;
    struct node *right;
} node;

node* Insert(node* head,int num)
{
    node *tmp;
    tmp = (node*)malloc(sizeof(node));
    tmp->value = num;
    tmp->left = tmp->right = NULL;

    if (!head)
    {
        head = tmp;
    }
    else
    {
        if(head->value < num)
        {
            head->right = Insert(head->right,num);
        }
        else
        {
            head->left = Insert(head->left,num);
        }
    }
    return head;
}
void print(node* ptr)
{
    if (ptr)
    {
        printf("%d ",ptr->value);
        print(ptr->left);
        print(ptr->right);
    }
}
int main()
{
    int num,search_num,err_flag=1;
    node *head,*curr;

    while(1)
    {
        head = curr = NULL;
        while((scanf("%d",&num)!=EOF)&&num)
        {
            head=Insert(head,num);
        }
        printf("\nPreorder print tree:\n");
        print(head);
        printf("\n-------------------\n\n");

        scanf("%d",&search_num);

        curr = head;
        err_flag = 1;

        if (!head)
            printf("NO BINARY SEARCH TREE\n\n");
        else
        {
            while(curr)
            {
                if (curr->value > search_num)
                {
                    curr = curr->left;
                }
                else if (curr->value <search_num)
                {
                    curr = curr->right;
                }
                else{
                    printf("FOUND:%d\n",curr->value);
                    err_flag = 0;
                    break;
                }
            }
            if(err_flag)printf("NOT FOUND\n\n");
        }
        printf("\n-------------------\n\n");
    }
    return;
}


