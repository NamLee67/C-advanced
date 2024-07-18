#include <stdio.h>
#include <stdlib.h>

struct linked_list
{
    int data;
    struct linked_list *next;
};

typedef struct linked_list node;

node *createNode(int value){
    node *temp;
    temp = (node*) malloc(sizeof(node));
    temp->data = value;
    temp->next = NULL;
    return temp;
}

void print(node *head){
    while (head != NULL)
    {
        printf("%d ", head->data);
        head = head->next;
    }    
}
node push_back(node **head, int value){
    node *newNode = createNode(value);
    if(*head == NULL){
        *head = newNode;
    }else{
        node *temp = *head;
        while(temp->next != NULL){
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

node push_front(node **head, int value){
    node *newNode = createNode(value);
    if(*head == NULL){
        *head = newNode;
    }else{
        newNode->next = *head;  // giải tham chiếu để lấy địa chỉ của head
        *head = newNode;
    }
}

node insert(node **head, int value, int index){
    node *newNode = createNode(value);
    int n = sizeof(*head);
    node *temp = *head;
    if(*head == NULL){
        *head = newNode;
    }else{
        if(index < 1 || index > n+1) return;
        if(index == 1){
            push_front(head,value);
            return;
        }
        for(int i=0; i <= index - 2; i++){
            temp = temp->next;
        }
        newNode->next = temp->next;
        temp->next = newNode;
        

    }    
}

void pop_front(node **head){
    if(*head == NULL) return;
    node *tmp = *head;
    *head = (*head)->next;
    free(tmp);
}

void pop_back(node **head){
    if(*head == NULL) return;
    node *tmp = *head;
    if(tmp->next == NULL){
        *head = NULL;
        free(tmp);
        return;
    }
    int n = sizeof(*head);
    while(tmp->next->next != NULL){
        tmp = tmp->next;
    }
    node *last = tmp->next;
    tmp->next = NULL;
    free(last);
}

void delete(node **head, int index){
    int n = sizeof(*head);
    if(index < 1 || index >= n) return;
    if(index == 1){
        pop_front(&head);
        return;
    }else{
        node *tmp = *head;
        for(int i = 0; i <= index - 2 ; i++){
            tmp = tmp->next;
        }
        node *tmp2 = tmp->next;
        tmp->next = tmp->next->next;  
        free(tmp2);

    }
}

int main(int argc, char const *argv[])
{
    node *head = NULL;
    int lc;
    while (1)
    {
        printf("--------------------------------\n");
        printf("1. Them vao dau :\n");
        printf("2. Them vao cuoi :\n");
        printf("3. Them vao giua :\n");
        printf("4. Xoa node dau linkedlist :\n");
        printf("5. Xoa node cuoi linkedlist :\n");
        printf("6. In ra :\n");
        printf("7. Thoat :\n");
        printf("--------------------------------\n");
        printf("Nhap lua chon :");
        scanf("%d",&lc);
        getchar();
        if(lc == 1){
            int value;
            printf("\nNhap gia tri :");
            scanf("%d",&value);
            getchar();
            push_front(&head,value);
        }else if (lc == 2 ){
            int value;
            printf("\nNhap gia tri :");
            scanf("%d",&value);
            getchar();
            push_back(&head,value);
        }else if (lc == 3){
            int value;
            int index;
            printf("\nNhap gia tri :");
            scanf("%d",&value);
            getchar();
            printf("\nNhap vi tri :");
            scanf("%d",&index);
            insert(&head,value,index);
        }else if(lc == 4){
            pop_front(&head);
        }else if(lc == 5){
            pop_back(&head);
        }else if(lc == 6){           
            print(head);
            printf("\n");
        }
        else{
            break;
        }
    }
    

    return 0;
}

