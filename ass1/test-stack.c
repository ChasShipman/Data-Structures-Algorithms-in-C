#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "dll.h"
#include "integer.h"

extern void srandom(unsigned int);
extern long int random(void);

int
main(void)
    {
    srandom(1);
    STACK *p = newSTACK(displayINTEGER,freeINTEGER);
    push(p,newINTEGER(3));
    push(p,newINTEGER(4));
    push(p,newINTEGER(2));
    displaySTACK(p,stdout);
    printf("\n");
    void *value = pop(p);
    displayINTEGER(value,stdout);
    printf("\n");
    freeINTEGER(value);
    displaySTACK(p,stdout);
    printf("\n");
    displaySTACKdebug(p,stdout);
    printf("\n");
    value = pop(p);
    displayINTEGER(value,stdout);
    printf("\n");
    freeINTEGER(value);
    displaySTACK(p,stdout);
    printf("\n");
    displaySTACKdebug(p,stdout);
    printf("\n");
    freeINTEGER(pop(p));
    displaySTACK(p,stdout);
    printf("\n");
    displaySTACKdebug(p,stdout);
    printf("\n");
    freeSTACK(p);
    return 0;
    }
