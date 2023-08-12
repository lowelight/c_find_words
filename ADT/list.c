// Linked list implementation ... COMP9024 22T1
#include "list.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#define wordLen 100


void seqCopy(int *s1, int *s2, int length){
    for(int i=0;i<length;i++){
        s1[i] = s2[i];
    }
}


Node *makeNode(int *n,int length) {
    Node *new = malloc(sizeof(Node));
    assert(new != NULL);
    seqCopy(new->v,n,length);
    new->next = NULL;
    return new;
}

List insertLL(List L, int *n,int length) {
    if(L==NULL) {
        Node *new = makeNode(n, length);
        new->next = NULL;
        return new;
    } else{
        List l=L;
        while(l->next!=NULL)
            l = l->next;
        Node *new = makeNode(n, length);
        new->next = NULL;
        l->next = new;
        return L;
    }
}

void freeLL(List L) {
    if (L != NULL) {
        freeLL(L->next);
        free(L);
    }
}

