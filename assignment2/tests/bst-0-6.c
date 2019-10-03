#include <stdio.h>
#include <stdlib.h>
#include "bst.h"
#include "integer.h"
#include "real.h"
#include "string.h"
#include "queue.h"

void srandom(unsigned int);
long int random(void);

int
main(void)
    {
    srandom(107);
    //simple INTEGER test of BST
    int i;
    BST *p = newBST(displayINTEGER,compareINTEGER,0,freeINTEGER);
    for (i = 0; i < 161; ++i)
        {
        int j = random() % 161;
        INTEGER *a = newINTEGER(j);
        if (findBST(p,a) == 0)
            insertBST(p,a);
        else
            freeINTEGER(a);
        }
    if (sizeBST(p) < 200)
        {
        printf("pre-order: ");
        displayBST(p,stdout);
        printf("\n");
        printf("level: ");
        displayBSTdebug(p,stdout);
        }
    printf("size is %d\n",sizeBST(p));
    for (i = 0; i < 161; ++i)
        {
        int j = random() % 161;
        INTEGER *a = newINTEGER(j);
        if (findBST(p,a) != 0)
            freeBSTNODE(deleteBST(p,a),freeINTEGER);
        freeINTEGER(a);
        }
    if (sizeBST(p) < 200)
        {
        printf("pre-order: ");
        displayBST(p,stdout);
        printf("\n");
        printf("level: ");
        displayBSTdebug(p,stdout);
        }
    printf("size is %d\n",sizeBST(p));
    statisticsBST(p,stdout);
    freeBST(p);
    return 0;
    }
