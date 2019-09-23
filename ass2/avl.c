/*** AVL binary search tree class ***/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "avl.h"
#include "bst.h"

struct avl{
	void (*display)(void *, FILE *);
	int (*comparator)(void *, void *);
	void (*free)(void *);
	BST *bst;
	int size;
};


typedef struct avlvalue{
	void *value;
	int count;
	int lheight;
	int rheight;
	int height;
	int balance;
	void (*display)(void *, FILE *);
	int (*comparator)(void *, void*);
	void (*free)(void *);
}AVLVALUE;

static int getBalance(AVLVALUE *x){
		assert(x->balance < 2 && x->balance > -2);
		return x->balance;
	}

static void adisplay(void *value, FILE *fp){

	AVLVALUE *node = value;
	node->display(node->value, fp);
	if(node->count > 1) {

		fprintf(fp,"[%d]",node->count);
	}
	if(getBalance(node) != 0){
		if(getBalance(node) < 0)
			fprintf(fp, "-");
		else 
			fprintf(fp, "+");

	}
}

static int acompare(void *a, void *b){

	AVLVALUE *x = a;
	AVLVALUE *y = b;
	void *p = x->value;
	void *q = y->value;
	return x->comparator(p, q);
}

static void aswap(BSTNODE *a,BSTNODE *b){

	AVLVALUE *ta = getBSTNODEvalue(a);
	AVLVALUE *tb = getBSTNODEvalue(b);

	/* swap the values stored in the AVL value objects */
	void *vtemp = ta->value;
	ta->value = tb->value;
	tb->value = vtemp;

	/* swap the counts stored in the AVL value objects */
	int ctemp = ta->count;
	ta->count = tb->count;
	tb->count = ctemp;

	return;
	/* note: AVL heights and balance factors are NOT swapped */
}

static void freeAVLVALUE(AVLVALUE *avl, void (*f)(void*)){
	if (avl){
		if(f){
			f(avl->value);
		}
		free(avl);
	}
	return;
}

static void afree(void *a){

	AVLVALUE  *avl = (AVLVALUE *) a;
	freeAVLVALUE(avl, avl->free);
	return;
}


extern AVL *newAVL(void (*d)(void *,FILE *),/*display*/int (*c)(void *,void *),/*comparator*/void (*f)(void *))/*freeing function*/{
	AVL *tree = malloc(sizeof(AVL));
	assert(tree != 0);
	tree->display = d;
	tree->comparator = c;
	tree->free = f;
	tree->bst = newBST(adisplay, acompare, aswap, afree);
	tree->size = 0;

	return tree;

}

static AVLVALUE *newAVLVALUE(void (*d)(void *,FILE *),/*display*/int (*c)(void *    ,void *),/*comparator*/void (*f)(void *)/*freeing function*/, void *v){


	AVLVALUE *avl = malloc(sizeof(AVLVALUE));
	assert(avl != 0);
	avl->display = d;
	avl->comparator = c;
	avl->free = f;
	avl->value = v;
	avl->count = 1;
	avl->lheight = 0;
	avl->rheight = 0;
	avl->height = 1;
	avl->balance = avl->lheight - avl->rheight;

	return avl;
}


static void zeroBalance(BSTNODE *x){
	if(x==0)
		return;
	else{
		AVLVALUE *tnode = getBSTNODEvalue(x);

		tnode->height = 0;
		return;
	}
}


static void setBalance(BSTNODE *x){
	if(x == 0)
		return;

	else{
		AVLVALUE *tnode = getBSTNODEvalue(x);

		if(getBSTNODEleft(x)){
			AVLVALUE *lnode = getBSTNODEvalue(getBSTNODEleft(x));
			tnode->lheight = lnode->height;
		}
		else tnode->lheight = 0;

		if(getBSTNODEright(x)){
			AVLVALUE *rnode = getBSTNODEvalue(getBSTNODEright(x));
			tnode->rheight = rnode->height;
		}
		else tnode->rheight = 0;

		if(tnode->lheight >= tnode->rheight)	
			tnode->height = tnode->lheight + 1;
		else
			tnode->height = tnode->rheight + 1;
		tnode->balance = tnode->lheight - tnode->rheight;

		//printf("<%d>", tnode->balance);
		assert(tnode->balance < 2 && tnode->balance > -2);
		return;
	}
}

static BSTNODE *favorite(BSTNODE *p){ //boolean
	AVLVALUE *parent = getBSTNODEvalue(p);
		//printf("<%d>", parent->balance);
	if(getBalance(parent) == 1){
		if(getBSTNODEleft(p)){
			BSTNODE *left = getBSTNODEleft(p);
			return left;
		}
		else return 0;
	}
	else if(getBalance(parent) == -1){
		if(getBSTNODEright(p)){
			BSTNODE *right = getBSTNODEright(p);
			return right;
		}
		else return 0;
	}
	else 
		return 0;
}

static int fav(BSTNODE *x){
	assert(getBSTNODEparent(x) != 0);
	BSTNODE *p = getBSTNODEparent(x);
	AVLVALUE *parent = getBSTNODEvalue(p);
	if((parent->balance == -1 && x == getBSTNODEright(p)) || (parent->balance == 1 && x == getBSTNODEleft(p)))
		return 1;
	else return 0;
}

static BSTNODE *sibling(BSTNODE *c, BSTNODE *p){
	assert(p == getBSTNODEparent(c)); //assert if parent exists
	if(c == getBSTNODEleft(p))
		return getBSTNODEright(p);
	else if(c == getBSTNODEright(p))
		return getBSTNODEleft(p);
	else return 0;
}

static int linear(BSTNODE *c, BSTNODE *p, BSTNODE *gp){
	if((getBSTNODEleft(gp) == p && getBSTNODEleft(p) == c)
			|| (getBSTNODEright(gp) == p && getBSTNODEright(p) == c))
		return 1;
	else return 0;

}

static void lrotate(BSTNODE *x, AVL *tree){
//	printf("lrotate\n");

	BSTNODE *parent = getBSTNODEparent(x);
	BSTNODE *left = getBSTNODEleft(x);
	BSTNODE *gp = getBSTNODEparent(parent);

	if(parent == getBSTroot(tree->bst)){
		setBSTNODEparent(x,x);
		setBSTroot(tree->bst, x);
	}
	else{
		if(gp){
			setBSTNODEparent(x, gp);
			if(parent == getBSTNODEleft(gp)){
				setBSTNODEleft(gp, x);
			}
			else{
				setBSTNODEright(gp, x);
			}
		}
	}
	if(parent){
		setBSTNODEleft(x, parent);
		setBSTNODEparent(parent,x);
		setBSTNODEright(parent, left);
	}
	if (left != 0){
		setBSTNODEparent(left, parent);
	}
	return;
}

static void rrotate(BSTNODE *x, AVL *tree){
//	printf("rrotate\n");
	
	BSTNODE *parent = getBSTNODEparent(x);
	BSTNODE *right = getBSTNODEright(x);
	BSTNODE *gp = getBSTNODEparent(getBSTNODEparent(x));
		
	if(parent == getBSTroot(tree->bst)){
		setBSTNODEparent(x,x);
		setBSTroot(tree->bst, x);
	}

	else{
		if(gp){
			setBSTNODEparent(x, gp);
			if(parent == getBSTNODEleft(gp)){
				setBSTNODEleft(gp, x);
			}
			else setBSTNODEright(gp, x);
		}
	}

	if(parent){
		setBSTNODEright(x, parent);
		setBSTNODEparent(parent,x);
		setBSTNODEleft(parent, right);
	}
	if (right)
		setBSTNODEparent(right, parent);

	return;

}

static void insertionFixup(BSTNODE *x, AVL *tree){
	while(1){
		BSTNODE *parent = getBSTNODEparent(x);

//		AVLVALUE *X = getBSTNODEvalue(x);
//		AVLVALUE *pr = getBSTNODEvalue(parent);
//		AVLVALUE *sib = getBSTNODEvalue(sibling(x, parent));

		if(getBSTroot(tree->bst) == x && parent == x){
//			printf("Case 0 :root\n");
			break;
		}
		else if(favorite(parent) == sibling(x, parent) && favorite(parent) != 0){

/*			printf("Case 1: parent {");
			tree->display(pr->value, stdout);
			printf("} of ");
			tree->display(X->value, stdout);
			printf(" favors sibling {");
			tree->display(sib->value, stdout);
			printf("}\n");
*/			
			setBalance(parent);
			break;
		}
		else if(getBalance(getBSTNODEvalue(parent))== 0){

/*			printf("Case 2: parent {");
			tree->display(pr->value, stdout);
			printf("} of ");
			tree->display(X->value, stdout);
			printf(" has no favorite\n");
*/			
			setBalance(parent);
			x = parent;

/*		AVLVALUE *newX = getBSTNODEvalue(x);
			printf("x is {");
			tree->display(newX->value, stdout);
			printf("}\n");
*/			continue;
		}
		else{

//			printf("else: parent favors x\n");
			BSTNODE *y = favorite(x);
//			AVLVALUE *Y = getBSTNODEvalue(y);
			BSTNODE *p = parent;
//			AVLVALUE *P = getBSTNODEvalue(p);
			

			if(y != NULL && linear(y, x, p) ==0){

/*				printf("Case 3: child <y,"); 
				tree->display(Y->value, stdout);
				printf(">, ");
				printf("parent <x, "); 
				tree->display(X->value, stdout);
				printf(">, ");
				printf("grandparent <p, "); 
				tree->display(P->value, stdout);
				printf(">, ");
				printf("are not linear\n");
*/
			if(y == getBSTNODEleft(x)){//if(y == x.left)
					rrotate(y, tree);//rotate y right;
					 lrotate(y,tree);//else rotate y left;
				}	
				else{//if(y == p.left)
					lrotate(y, tree);//rotate y right;
					rrotate(y, tree);//else rotate y left;
				}
				setBalance(x);
				setBalance(p);
				setBalance(y);
			}
			else{

/*				printf("Case 4: child <y,"); 
				tree->display(Y->value, stdout);
				printf(">, ");
				printf("parent <x, "); 
				tree->display(X->value, stdout);
				printf(">, ");
				printf("grandparent <p, "); 
				tree->display(P->value, stdout);
				printf(">, ");
				printf("are linear\n");
*/				
				if(x == getBSTNODEleft(p))//if(x == p.left)
					rrotate(x,tree);//rotate x right
				else lrotate(x,tree);//else rotate x left
				setBalance(p);
				setBalance(x);

			}
			break;
		}
	}
	return;
}

extern void insertAVL(AVL *tree,void *value){
	AVLVALUE *anode = newAVLVALUE(tree->display, tree->comparator, tree->free, value);

/*		printf("INSERTING ");
		tree->display(anode->value, stdout);
		printf("\n");
*/	
	BSTNODE *temp = findBST(tree->bst, anode);
	if(temp){
		AVLVALUE *node = getBSTNODEvalue(temp);
		tree->size++;
		node->count++;
		freeAVLVALUE(anode, 0);
	}
	else{
		BSTNODE *newInsert = insertBST(tree->bst, anode);
		setBalance(newInsert);
		BSTNODE *emp = newInsert;
		insertionFixup(emp, tree);
		tree->size++;
	}
	return;
}

extern int findAVLcount(AVL *tree,void *value){
	AVLVALUE *anode = newAVLVALUE(tree->display, tree->comparator, tree->free, value);
	BSTNODE *temp = findBST(tree->bst, anode);
	int hold = 0;
	
	if(temp){
		AVLVALUE *node = getBSTNODEvalue(temp);
		hold = node->count;
		freeAVLVALUE(anode, 0);
	}
	else{
		freeBSTNODE(temp, 0);
		freeAVLVALUE(anode, 0);
	}
	return hold;
}

extern void *findAVL(AVL *tree,void *value){
	AVLVALUE *anode = newAVLVALUE(tree->display, tree->comparator, tree->free, value);
	BSTNODE *temp = findBST(tree->bst, anode);
	void *hold = 0;
	
	if(temp){

		AVLVALUE *node = getBSTNODEvalue(temp);
		hold = node->value;
		freeAVLVALUE(anode, 0);
	}
	else{
		freeBSTNODE(temp, 0);
		freeAVLVALUE(anode, 0);
	}
		return hold;

}

static void deletionFixUp(BSTNODE *x, AVL *tree){
	zeroBalance(x); //set height of x to zero
	while(1){
	BSTNODE *parent = getBSTNODEparent(x);

//	AVLVALUE *X = getBSTNODEvalue(x);
//	AVLVALUE *pr = getBSTNODEvalue(parent);
//	AVLVALUE *sib = getBSTNODEvalue(sibling(x, parent));

		if(x == getBSTroot(tree->bst) && parent == x){//if x is root
//			printf("case 0: root`\n");
			break;
		}
		else if (fav(x) != 0){//if parent favors x

/*			printf("Case 1: parent {");
			tree->display(pr->value, stdout);
			printf("} favors x {");
			tree->display(X->value, stdout);
			printf("}\n");
*/			
			setBalance(parent);
			x = parent;

/*			AVLVALUE *newX = getBSTNODEvalue(x);
			printf("x is {");
			tree->display(newX->value, stdout);
			printf("}\n");
			AVLVALUE *left = getBSTNODEvalue(getBSTNODEparent(x));
			printf("left is {");
			tree->display(left->value, stdout);
			printf("}\n");
			//break;
			//printf("finish\n");
*/		//	break;
			continue;
		}
		else if (getBalance(getBSTNODEvalue(parent)) == 0){//if parent has no favorite
//			printf("case 2\n");
			setBalance(parent);
			break;
		}
		else{
			BSTNODE *p = getBSTNODEparent(x);
			BSTNODE *z = sibling(x, p);
			BSTNODE *y = favorite(z);
			if(y != 0 && linear(y,z,p)==0){
//				printf("case 3`\n");
				if(y == getBSTNODEleft(z)){
					rrotate(y, tree);
					 lrotate(y, tree);
					}

			 else{
					lrotate(y, tree);
					rrotate(y, tree);
				}

				setBalance(p);
				setBalance(z);
				setBalance(y);
				x = y;
				continue;
			}
			else{
//			printf("case 4`\n");
				if(z == getBSTNODEleft(p))
					rrotate(z, tree);
				else lrotate(z, tree);
				setBalance(p);
				setBalance(z);
				if(y == 0)
					break;
				x = z;
				continue;
			}
		}
	}
	return;
}

extern void *deleteAVL(AVL *tree,void *value){
	AVLVALUE *anode = newAVLVALUE(tree->display, tree->comparator, tree->free, value);
	BSTNODE *temp = findBST(tree->bst, anode);
/*		printf("DELETING ");
		tree->display(anode->value, stdout);
		printf("\n");
*/	
	if(temp){
		AVLVALUE *tnode = getBSTNODEvalue(temp);
		if(tnode->count > 1){
			tnode->count--;
			tree->size--;
			free(anode);
			return 0;
		}
		else {
//			tnode->count--;
			temp = swapToLeafBST(tree->bst, temp);
			AVLVALUE *hold = getBSTNODEvalue(temp);
			void *value = hold->value;
			BSTNODE *leaf = temp;	
			zeroBalance(leaf);
			deletionFixUp(leaf, tree);
			pruneLeafBST(tree->bst, temp);
			tree->size--;
			setBSTsize(tree->bst, sizeBST(tree->bst)-1);
			free(anode);
			free(hold);
			free(leaf);
			return value;
		}
	}
	else{
		free(anode);
		return 0;
	}
}




extern int sizeAVL(AVL *tree){
	return sizeBST(tree->bst);
}

extern int duplicatesAVL(AVL *tree){
	return tree->size - sizeBST(tree->bst);
}

extern void statisticsAVL(AVL *tree,FILE *fp){
	fprintf(fp, "Duplicates: %d\n", duplicatesAVL(tree));
	statisticsBST(tree->bst, fp);
	return;
}

extern void displayAVL(AVL *tree,FILE *fp){
	displayBSTdecorated(tree->bst, fp);
	return;
}

extern void displayAVLdebug(AVL *tree,FILE *fp){
	displayBST(tree->bst, fp);
	return;
}

extern void freeAVL(AVL *tree){
	freeBST(tree->bst);
	free(tree);
	return;
}
