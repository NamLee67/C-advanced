#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
void print(node *head){
    while (head != NULL)
    {
        printf("%d ", head->data);
        head = head->next;
    }    
}

void sapxep(node **head){
    for(node *i = *head; i!=NULL; i=i->next){
        node *min = i;
        for(node *j = min->next; j!=NULL; j=j->next){
            if(j->data <= min->data){
                min = j;
            }
        }
        int tmp = min->data;
        min->data = i->data;
        i->data = tmp;
        

    }
}
int main(int argc, char const *argv[])
{
    node *head = NULL;
    int a[]={2,3,5,1,6,8,4,10,7,9,0};
    for(int i= 0; i<10; i++){
        push_back(&head, a[i]);
    }
    sapxep(&head);
    print(head);
    return 0;
}
