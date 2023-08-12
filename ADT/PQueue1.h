// Priority Queue ADO header ... COMP9024 22T1

#include "WGraph.h"
#include <stdbool.h>

#define MAX_NODES 1000

void   PQueueInit();
void   joinPQueue(Vertex);
Vertex leavePQueue(int[]);
bool   PQueueIsEmpty();
