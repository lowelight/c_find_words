// Priority Queue ADO header ... COMP9024 22T1

#include "WGraph.h"
#include <stdbool.h>

#define MAX_NODES 100

void   PQueueInit();
void   joinPQueue(Vertex);
Vertex leavePQueue1(int[]);
Vertex leavePQueue(int[]);
bool   PQueueIsEmpty();