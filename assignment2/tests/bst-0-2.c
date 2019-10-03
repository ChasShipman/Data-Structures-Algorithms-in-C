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
    srandom(103);
    //simple STRING test of BST
    BST *p = newBST(displaySTRING,compareSTRING,0,freeSTRING);
    insertBST(p,newSTRING("a3"));
    insertBST(p,newSTRING("a2"));
    printf("pre-order: ");
    displayBST(p,stdout);
    printf("\n");
    printf("level: ");
    displayBSTdebug(p,stdout);
    STRING *q = newSTRING("a2");
    printf("is ");
    displaySTRING(q,stdout);
    printf(" present? %s\n",findBST(p,q) == 0? "no" : "yes");
    STRING *r = newSTRING("a3");
    freeBSTNODE(deleteBST(p,r),freeSTRING);
    printf("pre-order: ");
    displayBST(p,stdout);
    printf("\n");
    printf("level: ");
    displayBSTdebug(p,stdout);
    printf("is ");
    displaySTRING(q,stdout);
    printf(" present? %s\n",findBST(p,q) == 0? "no" : "yes");
    setSTRING(r,"a2");
    freeBSTNODE(deleteBST(p,r),freeSTRING);
    printf("pre-order: ");
    displayBST(p,stdout);
    printf("\n");
    printf("level: ");
    displayBSTdebug(p,stdout);
    printf("is ");
    displaySTRING(q,stdout);
    printf(" present? %s\n",findBST(p,q) == 0? "no" : "yes");
    printf("size: %d\n",sizeBST(p));
    statisticsBST(p,stdout);
    freeSTRING(q);
    freeSTRING(r);
    freeBST(p);
    return 0;
    }
