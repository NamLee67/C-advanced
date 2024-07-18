#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


int MAX_STR = 100000;
int str[100000];
int n=0;

int size(){
    return n;
}
bool empty(){
    return n == 0;
}
void push(int x){
    if(str[n] == MAX_STR) return;  
    str[n] = x;  ++n;
}

void pop(){
    if(n == 0)  return;
    for(int i=0; i<n-1; i++){
        str[i] = str[i+1];
    }  
    --n; 
}

int front(){
    if(n == 0) return 0;
    return str[0];
}

struct node{
    int data;
    struct node *next;
};

typedef struct node node;

node *createNode(int value){
    node *newNode = (node *) malloc(sizeof(node));
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

void enQueue(node **queue,int value){
    node *newNode = createNode(value);
    if(*queue == NULL){
        *queue = newNode;
        return;
    }
    node *tmp = *queue;
    while(tmp->next != NULL){
        tmp = tmp->next;
    }
    tmp->next = newNode;
}

void deQueue(node **queue,int value){
    if(*queue == NULL){
        return;
    }
    node *tmp = *queue;
    *queue = (*queue)->next;
    free(tmp);
}

int size(node *queue){
    int count = 0;
    while(queue != NULL){
        count++;
        queue = queue->next;
    }
    return count;
}

bool isEmpty(node *queue){
    return queue == NULL;
}

int front(node *queue){
    return queue->data;
}

void print(node *queue){
    while (queue != NULL)
    {
        printf("%d ", queue->data);
        queue = queue->next;
    }    
}
int main(int argc, char const *argv[])
{
    int lc;
    while (1)
    {
        printf("\n--------------------------------\n");
        printf("1. push \n");
        printf("2. pop \n");
        printf("3. front \n");
        printf("4. size \n");
        printf("5. is empty \n");
        printf("6. duyet \n");
        printf("7. thoat \n");       
        printf("--------------------------------\n");
        printf("Nhap lua chon :");
        scanf("%d",&lc);
        getchar();
        if(lc == 1){
            int value;
            printf("\nNhap gia tri :");
            scanf("%d",&value);
            getchar();
            push(value);
        }else if (lc == 2 ){
            pop();
        }else if (lc == 3){
            printf("\nfront : %d",front());
        }else if(lc == 4){
            printf("\nsize : %d",size());
        }else if(lc == 5){
            printf("\nisEmpty : %s",empty()?"true":"false");
        } else if(lc == 6){
            for(int i=0; i< n; i++){
                printf("%d ",str[i]);
            }
        }else{
            break;
        }
    }
    
    return 0;
}
