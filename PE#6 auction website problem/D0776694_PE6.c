#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct seller
{
    char seller_name[30];
    int price;
} seller;

typedef struct goods
{
    char goods_name[30];
    char goods_id[30];
    struct goods *right;
    struct goods *left;
    seller seller_heap[8];
    int seller_index;
} goods;

char commamd[10],goods_name[30],seller_name[30],goods_id[30];
int price,CT_insert=0,CT_search=0,CT_search_err=0,CT_buy=0,CT_buy_err=0,CT_node=0,CT_height=0;
FILE *O_fptr,*SHT_fptr,*BT_fptr,*STT_fptr,*LT_fptr;

void name_tolower()
{
    for(int i=0; i < 30; i++)
    goods_id[i] = 0;
    int len = strlen(goods_name);
    for(int i=0; i < len; i++)
        goods_id[i] = tolower(goods_name[i]);
}

goods* delete_goods(goods *head,char name[30])
{
    printf(">> Processing delete goods...");
    goods *tmp,*ptr;
    ptr = head;
    if (strcmp(ptr->goods_id,name) < 0)
        ptr->right = delete_goods(ptr->right,name);
    else if (strcmp(ptr->goods_id,name) > 0)
        ptr->left = delete_goods(ptr->left,name);
    else
    {
        if (!ptr->right)  //one child left child
        {
            if (ptr == head)
            {
                head = ptr->left;
                free(ptr);
                return head;
            }
            tmp = ptr->left;
            //free(ptr);
            return tmp;
        }
        else if (!ptr->left)  //one child right child
        {
            if (ptr == head)
            {
                head = ptr->right;
                free(ptr);
                return head;
            }
            tmp = ptr->right;
            //free(ptr);
            return tmp;
        }
        else   //two child
        {
            tmp = ptr->right;
            while(tmp->left && tmp)
                tmp = tmp->left; //point to the min node at the right subtree
            strcpy(ptr->goods_name,tmp->goods_name);
            strcpy(ptr->goods_id,tmp->goods_id);
            for(int i=1; i<tmp->seller_index; i++)
            {
                ptr->seller_heap[i].price=tmp->seller_heap[i].price;
                strcpy(ptr->seller_heap[i].seller_name,tmp->seller_heap[i].seller_name);
            }
            ptr->seller_index = tmp->seller_index;
            ptr->right = delete_goods(ptr->right,name); //to link the delete node right
        }
    }
    return ptr;
}

void insert_seller(goods *goods_ptr)
{
    printf(">> Processing insert seller heap...");
    int i;
    i = ++(goods_ptr->seller_index);
    if (!goods_ptr->seller_heap[1].price)
    {
        strcpy(goods_ptr->seller_heap[1].seller_name,seller_name);
        goods_ptr->seller_heap[1].price = price;
        return;
    }
    while((i!=1)&&(price < goods_ptr->seller_heap[i/2].price))
    {
        goods_ptr->seller_heap[i]=goods_ptr->seller_heap[i/2];
        i /= 2;
    }
    strcpy(goods_ptr->seller_heap[i].seller_name,seller_name);
    goods_ptr->seller_heap[i].price = price;
}

void print_seller_heap(goods *ptr)
{
    int i,index;
    index = ptr->seller_index;
    fprintf(SHT_fptr,"%s\n",ptr->goods_name);
    for(i=1; i<=index; i++)
    {
        printf("%s %d ",ptr->seller_heap[i].seller_name,ptr->seller_heap[i].price);
        fprintf(SHT_fptr,"%s %d\n",ptr->seller_heap[i].seller_name,ptr->seller_heap[i].price);
    }
    fprintf(SHT_fptr,"\n------------------------------\n\n");
}

goods* delete_seller_heap_min(goods *ptr,goods *head)
{
    int padre,nino,index;
    seller item,tmp;
    index = ptr->seller_index;
    printf("%d ",index);
    item = ptr->seller_heap[1];
    tmp = ptr->seller_heap[index--];
    padre = 1;
    nino = 2;
    while(nino<=index)
    {
        if((nino<index)&&ptr->seller_heap[nino].price>ptr->seller_heap[nino+1].price)
            nino++;
        if(tmp.price<=ptr->seller_heap[nino].price)
            break;
        ptr->seller_heap[padre] = ptr->seller_heap[nino];
        padre = nino;
        nino *= 2;
    }
    ptr->seller_heap[padre] = tmp;
    ptr->seller_index = index;
    printf("%s %d %d",item.seller_name,item.price,ptr->seller_index);
    fprintf(BT_fptr,"%s %s %d\n",ptr->goods_name,item.seller_name,item.price);
    if (index == 0)
        head = delete_goods(head,ptr->goods_id); //if no one seller in seller heap then delete goods
    return head;
}

goods* goods_search(goods *head)
{
    goods *curr;
    curr = head;
    if (!curr->right && !curr->left)
        NULL;
    while(curr)
    {
        if (strcmp(curr->goods_id,goods_id) > 0) // >
            curr = curr->left;
        else if (strcmp(curr->goods_id,goods_id) < 0) // <
            curr = curr->right;
        else if (strcmp(curr->goods_id,goods_id) == 0) // =
            break;
    }
    return curr;
}

goods* add(goods *head)
{
    goods *tmp;
    tmp = (goods*)malloc(sizeof(goods));
    strcpy(tmp->goods_name,goods_name);
    strcpy(tmp->goods_id,goods_id);
    //printf("%s",tmp->goods_id);
    tmp->left = tmp->right = NULL;
    tmp->seller_index = 0;
    if (!head) //empty binary tree
    {
        head = tmp;
        insert_seller(head);
    }
    else
    {
        if (strcmp(head->goods_id,goods_id) < 0) //<
        {
            head->right = add(head->right);
        }
        else if (strcmp(head->goods_id,goods_id) > 0) //>
        {
            head->left = add(head->left);
        }
        else if (strcmp(head->goods_id,goods_id) == 0) //=
        {
            insert_seller(head);
        }
    }
    return head;
}

void inorder_print(goods *ptr)
{
    if(ptr)
    {
        inorder_print(ptr->left);
        printf("%s ",ptr->goods_name);
        fprintf(STT_fptr,"%s\n",ptr->goods_name);
        inorder_print(ptr->right);
    }
}

int height_counter(goods* ptr)
{
    if (!ptr)
        return 0;
    else
    {
        int left = height_counter(ptr->left);
        int right = height_counter(ptr->right);
        if (left > right)
            return (left+1);
        else
            return (right+1);
    }
}

int node_counter(goods *ptr)
{
    int count = 1;
    if (!ptr)
        return 0;
    if (ptr->left)
        count += node_counter(ptr->left);
    if (ptr->right)
        count += node_counter(ptr->right);
    return count;
}

int main()
{
    goods *head = NULL,*tmp;
    char file_name[30];
    scanf("%s",file_name);
    printf("[File Log]\n");
    printf("Processing Open file...");
    O_fptr = fopen(file_name,"r");
    SHT_fptr = fopen("SeacherTable.txt","w");
    BT_fptr = fopen("BuyTable.txt","w");
    STT_fptr = fopen("SortTable.txt","w");
    LT_fptr = fopen("LogTable.txt","w");
    printf("OK\n");
    while(fscanf(O_fptr,"%s",commamd)!=EOF)
    {
        if(!strcmp(commamd,"insert"))
        {
            fscanf(O_fptr,"%s %s %d",goods_name,seller_name,&price);
debug_insert: //for debug mode
            printf("Processing insert...");
            name_tolower();
            printf(">> insert %s %s %d ",goods_name,seller_name,price);
            head = add(head);
            CT_insert+=1;
            printf(">> OK\n");
        }
        else if (!strcmp(commamd,"search"))
        {
            fscanf(O_fptr,"%s",goods_name);
debug_search: //for debug mode
            printf("Processing search...");
            printf(">> search %s ",goods_name);
            name_tolower();
            tmp = goods_search(head);
            printf(">> %s:",tmp->goods_name);
            if (tmp)
                print_seller_heap(tmp);
            else
            {
                fprintf(SHT_fptr,"%s doesn't exist!\n",goods_name);
                fprintf(SHT_fptr,"\n------------------------------\n\n");
                printf("%s doesn't exist! ",goods_name);
                CT_search_err += 1;
            }
            CT_search += 1;
            printf(">> OK\n");
        }
        else if (!strcmp(commamd,"buy"))
        {

            fscanf(O_fptr,"%s",goods_name);
debug_buy: //for debug mode
            printf("Processing buy...");
            printf(">> buy %s ",goods_name);
            name_tolower();
            tmp = goods_search(head);
            printf(">> %s:",tmp->goods_name);
            if (tmp)
                head = delete_seller_heap_min(tmp,head);
            else
            {
                fprintf(BT_fptr,"%s doesn't exist!\n",goods_name);
                printf("%s doesn't exist! ",goods_name);
                CT_buy_err += 1;
            }
            CT_buy += 1;
            printf(">> OK\n");
        }
        else if (!strcmp(commamd,"sort"))
        {
debug_sort: //for debug mode
            printf("Processing sort...");
            if (!head)
                printf("NULL");
            inorder_print(head);
            fprintf(STT_fptr,"\n------------------------------\n\n");
            printf(">> OK\n");
        }
        else if (!strcmp(commamd,"report"))
        {
debug_report: //for debug mode
            printf("Processing report...");
            CT_height = height_counter(head);
            CT_node = node_counter(head);
            printf("%d %d %d %d %d %d %d ",CT_insert,CT_search,CT_search_err,CT_buy,CT_buy_err,CT_node,CT_height);
            fprintf(LT_fptr,"insert %d\n",CT_insert);
            fprintf(LT_fptr,"search %d %d\n",CT_search,CT_search_err);
            fprintf(LT_fptr,"buy %d %d\n",CT_buy,CT_buy_err);
            fprintf(LT_fptr,"node_num %d\n",CT_node);
            fprintf(LT_fptr,"height %d\n",CT_height);
            printf(">> OK\n");
        }
    }
    fclose(O_fptr);
    fclose(SHT_fptr);
    fclose(BT_fptr);
    fclose(STT_fptr);
    fclose(LT_fptr);
    printf("\n\n[Debug Mode]\n>> ");
    while(1)
    {
        scanf("%s %s %s %d",commamd,goods_name,seller_name,&price);
        if (!strcmp(commamd,"insert"))
            goto debug_insert;
        else if (!strcmp(commamd,"search"))
            goto debug_search;
        else if (!strcmp(commamd,"buy"))
            goto debug_buy;
        else if (!strcmp(commamd,"sort"))
            goto debug_sort;
        else if (!strcmp(commamd,"report"))
            goto debug_report;
        printf("\n");
    }
    return 0;
}
