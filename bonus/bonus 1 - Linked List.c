#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int value;
    struct node *next;
}node;

node* createList(int num){
    int i;
    struct node *head=NULL,*tmp,*curr;

    for(i = 0;i < num;i++){
        tmp = (node*)malloc(sizeof(node));
        tmp->value = i;
        tmp->next = NULL;
        if (!head){
            head = tmp;
            curr = head;
            head->next = NULL;

        }
        else{
            curr->next = tmp;
            curr = tmp;

        }
    }

    return head;
}
void printList(node*head){
    node *ptr;
    for(ptr = head; ptr ; ptr = ptr->next){
        printf("%d ",ptr->value);
    }
    printf("\n");
}
node*insertList(node*head,int tag,int add,int num){
    struct node *tmp,*ptr;

    ptr = (node*)malloc(sizeof(node));
    ptr = head;
    if (tag>=num){
        printf("error");
        return;
    }
    else{
        tmp = (node*)malloc(sizeof(node));
        tmp->value = add;
        tmp->next = NULL;
        printf("");
        for(int i = 0;i < tag-2; i++){
            printf("%d ",ptr->value);
            ptr = ptr->next;
        }
        tmp->next=ptr->next;
        ptr->next=tmp;
    }
}
int main(){
    struct node *head;
    int num,add,tag;
    scanf("%d",&num);
    head = createList(num);
    printList(head);
    scanf("%d %d",&tag,&add);
    head = insertList(head,tag,add,num);
    printList(head);
    return 0;
}
