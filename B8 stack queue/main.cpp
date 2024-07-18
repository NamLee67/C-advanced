#include <iostream>
#include <iomanip>
#include <string>

using namespace std;


struct Sinhvien{
    string name;
    float gpa;
    Sinhvien(){

    }
    Sinhvien(string ten, float diem){
        name = ten;
        gpa = diem;
    }
};
struct linked_list
{
    Sinhvien data;
    struct linked_list *next;
};

typedef struct linked_list node;
node *createNode(Sinhvien s){
    node *temp;
    temp = new node;
    temp->data = s;
    temp->next = NULL;
    return temp;
}

void push_back(node **head, Sinhvien s){
    node *newNode = createNode(s);
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
        cout << head->data.name << ' ' << fixed << setprecision(2) << head->data.gpa << endl;
        head = head->next;
    }    
}

void sapxep(node **head){
    for(node *i = *head; i!=NULL; i=i->next){
        node *min = i;
        for(node *j = min->next; j!=NULL; j=j->next){
            if(j->data.gpa <= min->data.gpa){
                min = j;
            }
            else if(j->data.gpa == min->data.gpa){
                if(j->data.name < min->data.name){
                    min = j;
                }
            }
        }
        Sinhvien tmp = min->data;
        min->data = i->data;
        i->data = tmp;
        

    }
}
int main(int argc, char const *argv[])
{
    node *head = NULL;
    Sinhvien a("A",3.2);
    Sinhvien b("B",2.5);
    Sinhvien c("C",3.0);
    Sinhvien d("D",2.5);
    push_back(&head,a);
    push_back(&head,b);
    push_back(&head,c);
    push_back(&head,d);
    cout << "Danh sach sinh vien: " << endl;
    print(head);
    cout << "\nSap xep theo diem GPA tang dan: " << endl;
    sapxep(&head);
    print(head);
    return 0;
}
