#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "list.h"
#include "PQueue.h"

#define VERY_HIGH_VALUE 999999
#define VERY_LOW_VALUE -999999
#define LETTER_NUM 32
// I used many for loop functions for counting, printing or processing data,
// the costs of all for loop functions are O(n^2)
// I also used dijkstra's algorithm to find the longest path and shortest path
// The cost of dijkstra algorithm using PQueue is O(E+V*logV)
// I use link list to store path, and the cost of printing list nodes
// or deleting list are O(n)
// I create two DFS algorithm to find multiple shortest/longest paths
// Both of these DFS algorithms have O(V+E) time complexity
// Therefore the whole time complexity of my program is
// O(n^2)+O(E+V*logV)+O(n)+O(V+E)
// which the overall time complexity is O(n^2).



//list header
typedef struct Head{
    List list; // Node *list;
}Head;

// Recursive DFS algorithm for finding multiple shortest paths
void findAll(Graph g,int sho,Vertex source,Vertex destination, int *arr,Head *head,int depth ){
    if(depth+1 ==sho && source != destination){
    }
    else if(source == destination){
        if(depth+1 ==sho){
            arr[depth]=source;
            head->list = insertLL(head->list,arr,sho);
        }
    } else{
        for(int i =source;i<=destination;i++){
            if(adjacent(g,source,i)){
                arr[depth]=source;
                findAll(g,sho,i,destination,arr,head,depth+1);
            }
        }

    }
}

// Recursive DFS algorithm for finding multiple longest paths
void findAllL(Graph g,int lo,Vertex source,Vertex destination, int *arr,Head *head,int depth ){
    int count = 0;
    for(int i =source;i<=destination;i++){
        if(adjacent(g,source,i)){
            count++;
            arr[depth]=source;
            findAllL(g,lo,i,destination,arr,head,depth+1);
        }
    }
    if(count==0){
        if(depth+1==lo){
            arr[depth]=source;
            head->list = insertLL(head->list,arr,lo);
        }
    }
}
//find the shortest path
int originDij(Graph g,Vertex source,Vertex destination){
    int  dist[MAX_NODES];
    //int  pred[MAX_NODES];
    int s;

    PQueueInit();
    for (s = source; s < destination+1; s++) {
        joinPQueue(s);
        dist[s] = VERY_HIGH_VALUE;
        //pred[s] = -1;
    }
    dist[source] = 0;
    while(!PQueueIsEmpty()){
        int n = leavePQueue1(dist);
        for (int i=source;i<destination+1;i++){
            if(adjacent(g,n,i)){
                if(dist[i]==VERY_HIGH_VALUE){
                    dist[i]=dist[n]+adjacent(g,n,i);
                    //pred[i]=n;
                }else{
                    if((dist[n]+adjacent(g,n,i))<dist[i]){
                        dist[i] = dist[n]+adjacent(g,n,i);
                        //pred[i] = n;
                    }
                }
            }
        }
    }
    int shortest = dist[destination];
    return shortest;
}

//find the longest path
int dijkstraSSSP(Graph g, Vertex source,Head *head) {
    int  dist[MAX_NODES];
    //int  pred[MAX_NODES];


    PQueueInit();
    int nV = numOfVertices(g);
    for (int s = source; s < nV; s++) { //s start from source number, that is different from the original function
        joinPQueue(s);
        dist[s] = VERY_LOW_VALUE;
        //pred[s] = -1;
    }
    dist[source] = 0;
    while(!PQueueIsEmpty()){
        int n = leavePQueue(dist);
        for (int i=source;i<nV;i++){
            if(adjacent(g,n,i)){
                if(dist[i]==VERY_LOW_VALUE){
                    dist[i]=dist[n]+adjacent(g,n,i);
                    //pred[i]=n;
                }else{
                    if((dist[n]+adjacent(g,n,i))>dist[i]){
                        dist[i] = dist[n]+adjacent(g,n,i);
                        //pred[i] = n;
                        joinPQueue(i);
                    }
                }
            }
        }

    }

    int biggest = 0;
    for (int i=source; i<nV;i++){
        if(dist[i]>=biggest){
            biggest = dist[i];
        }
    }
    return biggest;
}

// string copy
void wordCopy(char *word, char *w){
    char m = w[0];
    int n=0;
    while(m!='\0'){
        word[n] = w[n];
        n++;
        m = w[n];
    }
    word[n]='\0';
}

// word length
int wL(char *word){ //word length
    int num =0 ;
    while(word[num]!='\0'){
        num++;
    }
    return num;
}

// to check if two words are same
bool sameW(char *w1,char *w2){//to check if two words are same
    if(wL(w1)!= wL(w2)){
        return false;
    } else{
        int index=0;
        while(w1[index]!='\0'){
            if(w1[index]!=w2[index]){
                return false;
            }
            index++;
        }
    }
    return true;
}

//to check if those two words could be consecutive
bool wordCheck(char *w1, char *w2){ // to check if those two words could be consecutive
    int i = 0,i2 =0;
    int length=(wL(w1)> wL(w2))? wL(w1): wL(w2);
    int same = 0;
    for(int m=0;m<length;m++){ // to check if every pair of chars are same
        if(w1[i]==w2[i2]) {
            same++;
            i++;
            i2++;
        }else{
            if(wL(w1)> wL(w2)){i++;
            }else if(wL(w2)> wL(w1)){ i2++;
            }else {
            i++;
            i2++;
            }
        }

    }
    if(length-same==1){
        return true;
    }else{
        return false;
    }
};

int main(){
    char **words;
    int  n;
    printf("Enter a number: ");
    scanf("%d", &n);
    words = malloc(n*sizeof(char*));
    for(int i =0;i<n;i++){
        words[i]= malloc(LETTER_NUM*sizeof (char));
    }
    char w[LETTER_NUM];
    for(int i=0;i<n;i++){
        printf("Enter a word: ");
        fflush(stdin); // to clear the buffer
        scanf("%s", w);
        wordCopy(words[i],w);
    }
    printf("Enter start word: ");
    char c[LETTER_NUM];
    fflush(stdin);
    scanf("%s",c);
    if(c[0]=='#') {
        // we could treat all words as a weight graph,
        // then we can use modified dijkstra algorithm
        Edge e;
        Graph g = newGraph(n);
        for (int i = 0; i < n - 1; i++) {
            for (int m = i + 1; m < n; m++) {
                if (wordCheck(words[i], words[m])) {
                    e.v = i;
                    e.w = m;
                    e.weight = 1;
                    insertEdge(g, e);
                }
            }
        }

        printf("\n");
        for (int i = 0; i < n; i++) {
            printf("%s:", words[i]);
            for (int m = 0; m < n; m++) {
                if (adjacent(g, i, m)) {
                    printf(" %s", words[m]);
                }
            }
            printf("\n");
        }

        Head *head= malloc(sizeof (Head));
        head->list = NULL;
        int bb;
        int biggest = -1;
        for (int i = 0; i < n; i++) {
            bb = dijkstraSSSP(g, i, head) + 1;
            if (bb > biggest) {
                biggest = bb;
            }
        }
        //find multiple longest paths
        int *arr = malloc(biggest*sizeof (int));
        for(int i=0;i<(n-biggest+1);i++){
            int depth = 0;
            findAllL(g,biggest,i,n-1,arr,head,depth);
        }

        printf("\n");// print the sequence
        printf("Maximum sequence length: %d\n", biggest);
        printf("Maximal sequence(s):\n");
        List index;
        index = head->list;
        while (index!=NULL) {
            printf("%s", words[index->v[0]]);
            for (int i = 1; i < biggest; i++) {
                printf(" -> %s", words[index->v[i]]);
            }
            index = index->next;
            printf("\n");
        }
        freeGraph(g);
        freeLL(head->list);
        free(head);
    }
    else{
        char start[LETTER_NUM];
        wordCopy(start,c);
        printf("Enter end word: ");
        fflush(stdin);
        scanf("%s",c);
        char end[LETTER_NUM];
        wordCopy(end,c);

        //print the graph
        Edge e;
        Graph g = newGraph(n);
        for (int i = 0; i < n - 1; i++) {
            for (int m = i + 1; m < n; m++) {
                if (wordCheck(words[i], words[m])) {
                    e.v = i;
                    e.w = m;
                    e.weight = 1;
                    insertEdge(g, e);
                }
            }
        }

        //start to find the minimum path
        int sI=-1,eI=-1; //start word index and end word index
        for(int i=0;i<n;i++){
            if(sameW(words[i],start)){
                sI = i;
                break;
            }
        }
        for(int i=0;i<n;i++){
            if(sameW(words[i],end)){
                eI = i;
                break;
            }
        }
        Head *head= malloc(sizeof (Head));
        head->list = NULL;
        int shortest = originDij(g,sI,eI)+1;
        int *arr = malloc(shortest*sizeof(int));
        int depth = 0;
        //find multiple shortest paths
        findAll(g,shortest,sI,eI,arr,head,depth);
        printf("\n");// print the sequence
        printf("Minimum sequence length: %d\n", shortest);
        printf("Minimal sequence(s):\n");
        List index;
        index = head->list;
        while (index!=NULL) {
            printf("%s", words[index->v[0]]);
            for (int i = 1; i < shortest; i++) {
                printf(" -> %s", words[index->v[i]]);
            }
            index = index->next;
            printf("\n");
        }
        freeGraph(g);
        freeLL(head->list);
        free(head);
    }
}


