#include <stdio.h>
#include <stdlib.h>
#include "bst.h"
#include "integer.h"
#include "real.h"
#include "string.h"
#include "stack.h"
#include "queue.h"
#include "heap.h"

extern void srandom(unsigned int);
extern long int random(void);

int
main(void)
    {
    srandom(2002);
    //simple REAL test of HEAP
    HEAP *p = newHEAP(displayREAL,rcompareREAL,freeREAL);
    insertHEAP(p,newREAL(1453.));
    insertHEAP(p,newREAL(4764746.));
    insertHEAP(p,newREAL(5043.));
    insertHEAP(p,newREAL(587993.));
    insertHEAP(p,newREAL(6844.));
    insertHEAP(p,newREAL(1277.));
    insertHEAP(p,newREAL(129428.));
    insertHEAP(p,newREAL(1717142838.));
    insertHEAP(p,newREAL(20409.));
    insertHEAP(p,newREAL(2062183.));
//	printHEAP(p, stdout);
    buildHEAP(p);
	displayHEAP(p,stdout);
    displayHEAPdebug(p,stdout);
    printf("\n");
//	printHEAP(p, stdout);
   /* printf("heap: ");
    displayHEAP(p,stdout);
    printf("\n");
    printf("debug:\n");
    displayHEAPdebug(p,stdout);
    printf("min should be %f\n",getREAL(peekHEAP(p)));
    REAL *r = extractHEAP(p);
    printf("min is %f\n",getREAL(r));
    freeREAL(r);
    printf("heap: ");
    displayHEAP(p,stdout);
    printf("\n");
    printf("debug:\n");
    displayHEAPdebug(p,stdout);
    printf("min should be %f\n",getREAL(peekHEAP(p)));
    r = extractHEAP(p);
    printf("min is %f\n",getREAL(r));
    freeREAL(r);
    printf("heap: ");
    displayHEAP(p,stdout);
    printf("\n");
    printf("debug:\n");
    displayHEAPdebug(p,stdout);
    printf("peek: %f\n",getREAL(peekHEAP(p)));
    printf("size: %d\n",sizeHEAP(p));
    freeHEAP(p);
   */ return 0;
    }
