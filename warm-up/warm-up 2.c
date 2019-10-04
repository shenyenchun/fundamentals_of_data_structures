#include <stdio.h>
#include <stdlib.h>

struct node{
    int num;
    struct node *next;
};

int main(){
    int n;
    struct node*nptr=(struct node *) malloc(sizeof(struct node));
    struct node*first=(struct node *) malloc(sizeof(struct node));
    scanf("%d",&n);

    first->next=NULL;
    first->num=1;
    nptr = first;
    for(int i=2;i<=n;i++){
        struct node *newnode = (struct node *) malloc(sizeof(struct node));
        newnode->num=i;
        newnode->next=NULL;
        first->next=newnode;
        first=first->next;
    }
    first->next = nptr;
    for(int i=1;n!=1;i++){
        if (i==2){
            struct node *tmp = (struct node *) malloc(sizeof(struct node));
            nptr->next=nptr->next->next;
            i=0;
            n-=1;
        }
        nptr = nptr->next;
    }
    printf("%d",nptr->num);
    return 0;
}
