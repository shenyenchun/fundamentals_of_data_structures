#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
    preOrder  = "ABCDEFGHI"

    inOrder   = "BCAEDGHFI"
    postOrder = "CBEHGIFDA"
*/

typedef struct node
{
    char word;
    struct node *left;
    struct node *right;
} node;

char inOrder[20],postOrder[20];
int count =0;

node* preOrder(int start,int end)
{
    node *tmp;
    tmp = (node*)malloc(sizeof(node));
    int i;
    tmp->left=NULL;
    tmp->right=NULL;

    if(start==end)return NULL;

    for(i=start; i<end; i++)
    {
        //printf("in %c,post %c \n",inOrder[i],postOrder[count]);
        if (postOrder[count]==inOrder[i])
        {
            count--;
            tmp->word = inOrder[i];
            //printf("i %d\nstart %d\nend %d\n",i,start,end);
            tmp->right = preOrder(i+1,end);//r
            tmp->left = preOrder(start,i);//l
            //printf("%c",inOrder[i]);
            break;
        }

    }
    return tmp;
}

void pre_print(node* ptr){
    if (ptr){
        printf("%c",ptr->word);
        pre_print(ptr->left);
        pre_print(ptr->right);
    }
}
int main()
{
    node *head;
    int in_len,post_len;
    scanf("%s",inOrder);
    scanf("%s",postOrder);
    in_len = strlen(inOrder);
    post_len = strlen(postOrder);
    count = post_len-1;
    head = preOrder(0,in_len);
    pre_print(head);
    return 0;
}
