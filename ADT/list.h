// Linked list interface ... COMP9024 22T1
#include <stdbool.h>

#define wordLen 100
typedef struct Node {
    int     v[wordLen];
    struct Node *next;
} Node;
typedef struct Node *List;

List insertLL(List, int*,int);
void freeLL(List);
