#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "heap.h"
#include "bst.h"
#include "queue.h"
#include "stack.h"

struct heap{
	int size;
	void (*display)(void *v, FILE *fp);
	int (*comparator)(void *v, void *w);
	void (*free)(void *v);
	BST *tree;
	QUEUE *queue;
	STACK *stack;

};

extern HEAP *newHEAP(void (*d)(void *,FILE *),/*display*/ int (*c)(void *,void *),/*compare*/ void (*f)(void *)){/*free*/

	HEAP *hp = malloc(sizeof(HEAP));
	assert(hp != 0);
	hp->size = 0;
	hp->display = d;
	hp->comparator = c;
	hp->free = f;
	hp->queue = newQUEUE(d, 0);
	hp->stack = newSTACK(d, 0);
	hp->tree = newBST(d, c, 0, f);
	return hp;		
}

extern void insertHEAP(HEAP *h,void *value){
	BSTNODE *newNode = newBSTNODE(value);
	h->size++;
	setBSTsize(h->tree, h->size);

	if(getBSTroot(h->tree) == 0){
		setBSTroot(h->tree, newNode);
		enqueue(h->queue, newNode);
		push(h->stack, newNode);

	}

	else{
		while(1){
			BSTNODE *temp = peekQUEUE(h->queue);
			if(getBSTNODEleft(temp) != 0 && getBSTNODEright(temp) != 0)
				dequeue(h->queue);

			else if(getBSTNODEleft(temp) == 0 && getBSTNODEright(temp) == 0){
				setBSTNODEleft(temp, newNode);
				setBSTNODEparent(newNode, temp);
				push(h->stack, newNode);
				enqueue(h->queue, newNode);
				break;
			}

			else if(getBSTNODEleft(temp) != 0 && getBSTNODEright(temp) == 0){
				setBSTNODEright(temp, newNode);
				setBSTNODEparent(newNode, temp);
				push(h->stack, newNode);
				enqueue(h->queue, newNode);
				break;
			}

		}
	}
	return;
}

static void swap(BSTNODE *x, BSTNODE *y){
	void *temp = getBSTNODEvalue(x);
	setBSTNODEvalue(x, getBSTNODEvalue(y));
	setBSTNODEvalue(y, temp);
	return;
}

static void bubbleDown(HEAP *h, BSTNODE *node){
	BSTNODE *left = getBSTNODEleft(node);
	BSTNODE *right = getBSTNODEright(node);

	int lcompare = 0;
	int rcompare = 0;

	if(left != 0){
		lcompare = h->comparator(getBSTNODEvalue(node), getBSTNODEvalue(left));
	}

	if(right != 0){
		rcompare = h->comparator(getBSTNODEvalue(node), getBSTNODEvalue(right));
	}

	if(left == 0 && right == 0)
		return;

	if(lcompare > 0 && rcompare <= 0){
		swap(node, left);
		bubbleDown(h, left);
	}
	else if(lcompare <= 0 && rcompare > 0){
		swap(node, right);
		bubbleDown(h, right);
	}
	else if(lcompare > 0 && rcompare > 0){
		if(h->comparator(getBSTNODEvalue(left), getBSTNODEvalue(right)) >= 0){
			swap(node, right);
			bubbleDown(h, right);
		}
		else{//if(h->comparator(getBSTNODEvalue(left), getBSTNODEvalue(right)) < 0){
			swap(node, left);
			bubbleDown(h, left);
		}
//		else
//			swap(left,right);
			//bubbleDown(h,left);
			//bubbleDown(h,right);
	}
	else return;
}
/*
static void bubbleDown(HEAP *h, BSTNODE *node){
	BSTNODE *left = getBSTNODEleft(node);
	BSTNODE *right = getBSTNODEright(node);

	int lcompare = 0;
	int rcompare = 0;

	if(left != 0){
		lcompare = h->comparator(getBSTNODEvalue(node), getBSTNODEvalue(left));
	}

	if(right != 0){
		rcompare = h->comparator(getBSTNODEvalue(node), getBSTNODEvalue(right));
	}

	if(left == 0 && right == 0)
		return;

	if(lcompare > 0 && rcompare <= 0){
		swap(node, left);
		bubbleDown(h, left);
	}
	if(lcompare <= 0 && rcompare > 0){
		swap(node, right);
		bubbleDown(h, right);
	}
	if(lcompare > 0 && rcompare > 0){
		if(lcompare > rcompare){
			swap(node, left);
			bubbleDown(h, left);
		}
		else{
			swap(node, right);
			bubbleDown(h, right);
		}	
	}
	else return;
}*/


/*	else if(rcompare <*=* 0 && lcompare >= 0){
		swap(node, left);
		bubbleDown(h, left);
	}
	else if(lcompare >= 0 && rcompare >= 0){//CHECK HERE
		if(lcompare > rcompare){
			swap(node, left);
			bubbleDown(h, left);
		}
		else{//rcompare > lcompare)
			swap(node, right);
			bubbleDown(h, right);
		}
	}

	else if (lcompare >= 0 && rcompare < 0){
		swap(node, left);
		bubbleDown(h, left);
	}
	else if (lcompare <*=* 0 && rcompare >= 0){
		swap(node, right);
		bubbleDown(h, right);
	}*/


	extern void buildHEAP(HEAP *h){
		STACK *tempStack = newSTACK(0, 0);
		BSTNODE *tempNode = 0;
		BSTNODE *tempNd = 0;
		while(sizeSTACK(h->stack) != 0){
			tempNode = pop(h->stack);
			push(tempStack, tempNode);	
			if(getBSTNODEleft(tempNode) != 0 || getBSTNODEright(tempNode) != 0)
				bubbleDown(h, tempNode);
		}
		while(sizeSTACK(tempStack) != 0){
			tempNd = pop(tempStack);
			push(h->stack, tempNd);
		}
		freeSTACK(tempStack);
		return;
	}


	extern void *peekHEAP(HEAP *h){
		BSTNODE *root = getBSTroot(h->tree);
		if(h->size == 0)
			setBSTNODEvalue(root, 0);
		void *a = getBSTNODEvalue(root);
		return a;
	}


	extern void *extractHEAP(HEAP *h){
		if(h->size == 1){
			h->size = 0;
			void *a = getBSTNODEvalue(getBSTroot(h->tree));
			pruneLeafBST(h->tree, getBSTroot(h->tree));
			return a;
		}
		BSTNODE *temp = pop(h->stack);
		BSTNODE *temp2 = getBSTroot(h->tree);
		swap(temp, temp2);
		void *holder = getBSTNODEvalue(temp);
		pruneLeafBST(h->tree, temp);
		freeBSTNODE(temp, 0);
		bubbleDown(h, temp2);
		h->size--;
		return holder;

	}

	extern int  sizeHEAP(HEAP *h){
		return h->size;
	}

	extern void displayHEAP(HEAP *h,FILE *fp){
		displayBST(h->tree, fp);
		return;
	}

	extern void displayHEAPdebug(HEAP *h,FILE *fp){
		fprintf(fp, "heap size: %d\n", sizeHEAP(h));
		fprintf(fp, "bst size: %d\n", sizeBST(h->tree));
		displayBSTdebug(h->tree, fp);
		return;
	}

	extern void freeHEAP(HEAP *h){
		freeQUEUE(h->queue);
		freeSTACK(h->stack);
		freeBST(h->tree);
		free(h);
		return;
	}
