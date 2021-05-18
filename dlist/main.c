#include <stdio.h>
#include "lib/DList.h"

int main() {
    DList *dl;

    //reverse test
    {
        dl = createDList(sizeof(int));
        for (int i = 1; i <= 10; ++i) {
            pushHead(dl, &i);
        }
        int *item;
        int i = 10;
        while ((item = popHead(dl)) != NULL) {
            assert(i == *item);
            free(item);
            i--;
        }
        destroyDList(dl);
    }

    //Иа IO case
    {
        dl = createDList(sizeof(short));
        short data = 3;

        pushHead(dl, &data);
        short *item = popHead(dl);
        assert(data == *item);
        free(item);

        pushHead(dl, &data);
        item = popTail(dl);
        assert(data == *item);
        free(item);

        pushTail(dl, &data); //Found typo with this case
        item = popHead(dl);
        assert(data == *item);
        free(item);

        pushTail(dl, &data);
        item = popTail(dl);
        assert(data == *item);
        free(item);

        item = popTail(dl);
        assert(item == NULL);

        item = &data;
        item = popHead(dl);
        assert(item == NULL);

        destroyDList(dl);
    }

    //test at
    {

        dl = createDList(sizeof(int));
        for (int i = 1; i <= 10; ++i) {
            pushHead(dl, &i);
            assert(*(int *)at(dl, i - 1) == 1);
        }
        for (int j = 9; j >= 0; --j) {
            assert(*(int *)at(dl,j) == 10 - j);
        }
        destroyDList(dl);
    }

    printf("All test passed!");
}