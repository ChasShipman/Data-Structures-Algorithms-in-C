/*
 *
 *Author: Chas Shipman
 *CS201
 *Assignment 0
 *Anderson
 *Due: 1/30/18
 *
 *
 *This file acts as 
 *an abstract stack
 *data structure built
 *from an underlying
 *doubly-linked list 
 *
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "stack.h"
#include "dll.h"

struct stack{
	DLL *list;
	void (*display)(void *, FILE *);
	void (*free)(void *);

};

extern STACK *newSTACK(void (*d)(void *,FILE *),void (*f)(void *)){

	STACK *stack;
	stack = malloc(sizeof(STACK));
	assert(stack != 0);
	stack->display = d;
	stack->free = f;
	stack->list = newDLL(d,f);
	return stack;
}

extern void push(STACK *items,void *value){
	insertDLL(items->list,0, value);
	assert(sizeSTACK(items) > 0);
	return;
}

extern void *pop(STACK *items){
	assert(sizeSTACK(items) > 0);
	return removeDLL(items->list, 0);

}

extern void *peekSTACK(STACK *items){
	assert(sizeSTACK(items) > 0);
	return getDLL(items->list, 0);

}

extern int sizeSTACK(STACK *items){
	return sizeDLL(items->list);

}

extern void displaySTACK(STACK *items,FILE *fp){
	if(sizeSTACK(items)==0){
		fprintf(fp, "||");
		return;
	}

	int i = 0;
	fprintf(fp,"|");
	items->display(getDLL(items->list, i),fp);
	for(i = 1; i < sizeSTACK(items); i++){
		fprintf(fp, ",");
		items->display(getDLL(items->list, i),fp);
	}
	fprintf(fp, "|");
	return;
}

extern void displaySTACKdebug(STACK *items,FILE *fp){
	displayDLLdebug(items->list, fp);
	return;
}

extern void freeSTACK(STACK *items){
	freeDLL(items->list);
	free(items);
	return;
}


