#include <stdio.h>
#include <string.h>

typedef struct {
    char location[19];
    char time[10];
} Record;

void ChangeValue(Record* a, Record* b) {
    Record temp = *a;
    *a = *b;
    *b = temp;
}

void SortTime(Record* Value, int size) {
    int i, j;
    for (i = 0; i < size - 1; i++) {
        for (j = 0; j < size - 1 - i; j++) {
            if (strcmp(Value[j].time, Value[j + 1].time) > 0) {
                ChangeValue(&Value[j], &Value[j + 1]);
            }
        }
    }
}

void SortLoca(Record* Value, int size) {
    int i, j;
     for (i = 0; i < size - 1; i++) {
        for (j = 0; j < size - 1 - i; j++) {
            if (strcmp(Value[j].location, Value[j + 1].location) > 0) {
                ChangeValue(&Value[j], &Value[j + 1]);
            }
        }
    }
}

int main() {
    printf("%d\n",sizeof(Record));
    Record Value[] = {
        {"Chicago", "09:00:00"},
        {"Phoenix", "09:00:03"},
        {"Houston", "09:00:10"},
        {"Chicago", "09:00:13"},
        {"Chicago", "09:00:59"},
        {"Houston", "09:01:10"},
        {"Seattle", "09:01:25"},
        {"Seattle", "09:10:25"},
        {"Phoenix", "09:14:25"},
        {"Chicago", "09:19:25"},
        {"Chicago", "09:19:46"},
        {"Houston", "09:19:46"},
        {"Seattle", "09:21:05"},
        {"Phoenix", "09:22:43"},
        {"Seattle", "09:22:43"},
        {"Seattle", "09:25:52"},
        {"Chicago", "09:25:52"},
        {"Chicago", "09:36:14"},
        {"Seattle", "09:36:14"},
        {"Phoenix", "09:37:44"}
    };

    int size = sizeof(Value) / sizeof(Value[0]);
    SortTime(Value, size);
    SortLoca(Value, size);
    for (int i = 0; i < size; i++) {
        printf("%s %s\n", Value[i].location, Value[i].time);
    }
    return 0;
}
