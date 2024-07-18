#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node* next;
};
typedef struct node node;

node *createNode(int value) {
    node *newNode = (node*) malloc(sizeof(node));
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

void push(node **top, int value) {
    node *newNode = createNode(value);
    if(top == NULL) {
        *top = newNode;
        return;
    }
    newNode->next = *top;
    *top = newNode;
}

void pop(node **top) {
    if(top == NULL) {
        printf("Stack is empty\n");
        return;
    }
    node *tmp = *top;
    (*top) = tmp->next;
    free(tmp);
}

int Top(node *top){
    if(top != NULL) {
        return (top)->data;
    }
}

int Size(node *top){
    int count = 0;
    while(top != NULL){
        ++count;
        top = top->next;
    }
    return count;
}

int main(int argc, char const *argv[])
{
    node *stack = NULL;
    int lc;
    while (1)
    {
        printf("\n--------------------------------\n");
        printf("1. push :\n");
        printf("2. pop :\n");
        printf("3. top :\n");
        printf("4. size :\n");
        printf("--------------------------------\n");
        printf("Nhap lua chon :");
        scanf("%d",&lc);
        getchar();
        if(lc == 1){
            int value;
            printf("\nNhap gia tri :");
            scanf("%d",&value);
            getchar();
            push(&stack,value);
        }else if (lc == 2 ){
            pop(&stack);
        }else if (lc == 3){
            printf("\ndata : %d",Top(stack));
        }else if(lc == 4){
            printf("\nsize : %d",Size(stack));
        }else{
            break;
        }
    }
    
    return 0;
}
