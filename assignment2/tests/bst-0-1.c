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
    srandom(102);
    //simple REAL test of BST
    BST *p = newBST(displayREAL,compareREAL,0,freeREAL);
    insertBST(p,newREAL(3));
    insertBST(p,newREAL(2));
    printf("pre-order: ");
    displayBST(p,stdout);
    printf("\n");
    printf("level: ");
    displayBSTdebug(p,stdout);
    REAL *q = newREAL(2);
    printf("is ");
    displayREAL(q,stdout);
    printf(" present? %s\n",findBST(p,q) == 0? "no" : "yes");
    REAL *r = newREAL(3);
    freeBSTNODE(deleteBST(p,r),freeREAL);
    printf("pre-order: ");
    displayBST(p,stdout);
    printf("\n");
    printf("level: ");
    displayBSTdebug(p,stdout);
    printf("is ");
    displayREAL(q,stdout);
    printf(" present? %s\n",findBST(p,q) == 0? "no" : "yes");
    setREAL(r,2);
    freeBSTNODE(deleteBST(p,r),freeREAL);
    printf("pre-order: ");
    displayBST(p,stdout);
    printf("level: ");
    displayBSTdebug(p,stdout);
    printf("is ");
    displayREAL(q,stdout);
    printf(" present? %s\n",findBST(p,q) == 0? "no" : "yes");
    printf("size: %d\n",sizeBST(p));
    statisticsBST(p,stdout);
    freeREAL(q);
    freeREAL(r);
    freeBST(p);
    return 0;
    }
