#include <stdio.h>
#include <assert.h>
#include "lib/priorityQueue.h"

int main() {
    PriorityQueue *myqueue = createPQ(sizeof(char) * 10);
    char temp[10];
    for (int i = 0; i < 10; ++i) { //Заполнение в обратном порядке
        char desc[10];
        sprintf(desc, "%d", i);
        insertPQ(myqueue, i, desc);
    }
    for (int j = 0; j < 10; ++j) {
        char desc[10];
        sprintf(desc, "%d", 9 - j);
        memcpy(temp, (char *) extractMaxPQ(myqueue), 10);
        assert(strcmp(temp, desc) == 0);
    }
    printf("All done!");
    destroyPQ(myqueue);
    return 0;
}