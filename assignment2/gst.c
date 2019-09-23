/*** green binary search tree class ***/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "bst.h"
#include "gst.h"

struct gst{
	void (*display)(void *, FILE *);
	int (*comparator)(void *, void*);
	void (*free)(void *);
	BST *bst;
	int size;
};


typedef struct gstvalue{
	void *value;
	int count;
	void (*display)(void *, FILE *);
	int (*comparator)(void *, void*);
	void (*free)(void *);
}GSTVALUE;

static void gdisplay(void *value, FILE *fp){
	GSTVALUE *node = value;
	node->display(node->value, fp);
	if(node->count > 1) {
		fprintf(fp,"[%d]",node->count);
	}
}

static int gcompare(void *a, void *b){
	GSTVALUE *x = a;
	GSTVALUE *y = b;
	void *p = x->value;
	void *q = y->value;
	return x->comparator(p, q);
}

static void gswap(BSTNODE *a,BSTNODE *b){
	GSTVALUE *ta = getBSTNODEvalue(a);
	GSTVALUE *tb = getBSTNODEvalue(b);

	/* swap the values stored in the AVL value objects */
	void *vtemp = ta->value;
	ta->value = tb->value;
	tb->value = vtemp;

	/* swap the counts stored in the AVL value objects */
	int ctemp = ta->count;
	ta->count = tb->count;
	tb->count = ctemp;

	/* note: AVL heights and balance factors are NOT swapped */
}

static void freeGSTVALUE(GSTVALUE *g, void (*f)(void*)){
	if(g){
		if(f){
			f(g->value);
		}
		free(g);
	}
	return;
}

static void gfree(void *a){
	GSTVALUE *x = a;
	freeGSTVALUE(x, x->free);
	return;
}


extern GST *newGST(void (*d)(void *,FILE *),/*display*/int (*c)(void *,void *),/*comparator*/void (*f)(void *))/*freeing function*/{

	GST *tree = malloc(sizeof(GST));
	assert(tree != 0);
	tree->display = d;
	tree->comparator = c;
	tree->free = f;
	tree->bst = newBST(gdisplay, gcompare, gswap/*custom swapper*/, gfree);//might need to make some functions in this beast to replace d,c, 0, f.
	tree->size = 0;

	return tree;
}

static GSTVALUE *newGSTVALUE(void (*d)(void *,FILE *),/*display*/int (*c)(void *,void *),/*comparator*/void (*f)(void *)/*freeing function*/, void *v){

	GSTVALUE *green = malloc(sizeof(GSTVALUE));
	assert(green != 0);
	green->display = d;
	green->comparator = c;
	green->free = f;
	green->value = v;
	green->count = 1;

	return green;
}

extern void insertGST(GST *tree,void *value){
	GSTVALUE *gnode = newGSTVALUE(tree->display, tree->comparator, tree->free, value);
	BSTNODE *temp = findBST(tree->bst, gnode);

	if(temp){
		GSTVALUE *node = getBSTNODEvalue(temp);
		node->count++;
	}
	else{
		insertBST(tree->bst, gnode);
	}
	tree->size++;
	return;
}

extern int findGSTcount(GST *tree,void *value){
	GSTVALUE *gnode = newGSTVALUE(tree->display, tree->comparator, tree->free, value);
	BSTNODE *temp = findBST(tree->bst, gnode);
	int hold = 0;

	if(temp){
		GSTVALUE *node = getBSTNODEvalue(temp);
		hold = node->count;
		freeGSTVALUE(gnode, 0);
	}
	else{
		freeGSTVALUE(gnode, 0);
		freeBSTNODE(temp, 0);

	}

	return hold;
}

extern void *findGST(GST *tree,void *value){
	GSTVALUE *gnode = newGSTVALUE(tree->display, tree->comparator, tree->free, value);
	BSTNODE *temp = findBST(tree->bst, gnode);
	void *hold = 0;
	if(temp){
		GSTVALUE *node = getBSTNODEvalue(temp);
		hold = node->value;
		freeGSTVALUE(gnode, 0);
		//freeBSTNODE(temp,0);
	}
	else{
		freeGSTVALUE(gnode, 0);
		//freeBSTNODE(temp,0);

	}
	//freeBSTNODE(temp,0);
	return hold;
}

extern void *deleteGST(GST *tree,void *value){
	GSTVALUE *gnode = newGSTVALUE(tree->display, tree->comparator, tree->free, value);
	BSTNODE *temp = findBST(tree->bst, gnode);
	if(temp){
		GSTVALUE *node = getBSTNODEvalue(temp);
		if(node->count > 1){
			node->count--;
			tree->size--;
			free(gnode);
			return 0;
		}
		else{
			node->count--;
			BSTNODE *del = deleteBST(tree->bst, node);
			GSTVALUE *hold = getBSTNODEvalue(del);
			void *value = hold->value;
			tree->size--;
			free(gnode);
			free(hold);
			free(del);
			return value;
		}
		
	}
	else{
		free(gnode);
		return 0;
	}
}



extern int sizeGST(GST *tree){
	//return tree->size;
	return sizeBST(tree->bst);
}

extern int duplicates(GST *tree){
	int bstSize = sizeBST(tree->bst);
	int gstSize = tree->size;
	return gstSize - bstSize;
}

extern void statisticsGST(GST *tree,FILE *fp){
	fprintf(fp, "Duplicates: %d\n", duplicates(tree));
	statisticsBST(tree->bst, fp);

}

extern void displayGST(GST *tree,FILE *fp){
	displayBSTdecorated(tree->bst, fp);
}

extern void displayGSTdebug(GST *tree,FILE *fp){
	displayBST(tree->bst, fp);
}

extern void freeGST(GST *tree){
	freeBST(tree->bst);
	free(tree);
}

