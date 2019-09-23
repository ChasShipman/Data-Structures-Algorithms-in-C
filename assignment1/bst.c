#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "queue.h"
#include "bst.h"


struct bstnode{
	BSTNODE *left;
	BSTNODE *right;
	BSTNODE *parent;
	void *value;
};

struct bst{

	void (*display)(void *, FILE *);
	int (*comparator)(void *, void *);
	void (*swapper)(BSTNODE *, BSTNODE *);
	void (*free)(void *);
	BSTNODE *root;
	int size;
};


extern BSTNODE *newBSTNODE(void *v){
	BSTNODE *node = malloc(sizeof(BSTNODE));
	assert(node != 0);

	node->left = 0;
	node->right = 0;
	node->parent = 0;
	node->value = v;

	return node;
}

extern void *getBSTNODEvalue(BSTNODE *n){
	if(n != 0)
		return n->value;
	else return 0;
}

extern void setBSTNODEvalue(BSTNODE *n,void *value){
	n->value = value;
	return;
}

extern BSTNODE *getBSTNODEleft(BSTNODE *n){
	if(n != 0)
		return n->left;
	else return 0;
}

extern void setBSTNODEleft(BSTNODE *n,BSTNODE *replacement){
	n->left = replacement;
	return;
}

extern BSTNODE *getBSTNODEright(BSTNODE *n){
	if (n != 0)
		return n->right;
	else return 0;
}

extern void setBSTNODEright(BSTNODE *n,BSTNODE *replacement){
	n->right = replacement;
	return;
}

extern BSTNODE *getBSTNODEparent(BSTNODE *n){
	if(n != 0)
		return n->parent;
	else return 0;
}

extern void setBSTNODEparent(BSTNODE *n,BSTNODE *replacement){
	n->parent = replacement;
	return;
}

extern void freeBSTNODE(BSTNODE *n,void (*f)(void *)){
	if(f != 0)
		f(n->value);
	free(n);
	return;
}

static void swap(BSTNODE *x, BSTNODE *y){
	void *temp = x->value;
	x->value = y->value;
	y->value = temp;
	return;
}//check this and *swap and constructor swap conditional


extern BST *newBST(void (*d)(void *,FILE *),/*display*/int (*c)(void *,void *),/*comparator*/void (*s)(BSTNODE *,BSTNODE *),/*swapper*/void (*f)(void *))/*free*/{
	BST *tree = malloc(sizeof(BST));
	assert(tree !=0);
	tree->display = d;
	tree->comparator = c;

	if(s != 0)
		tree->swapper = s;
	else tree->swapper = swap;	

	tree->free = f;
	tree->size = 0;
	tree->root = 0;
	return tree;
}

extern BSTNODE *getBSTroot(BST *t){
	if(t->root)
		return t->root;
	else return 0;
}

extern void setBSTroot(BST *t,BSTNODE *replacement){

	//	if(t->root == 0)
	//		t->size++;

	t->root = replacement;

	//	if(t->root == 0)
	//		t->size--;

	return;
}

extern void setBSTsize(BST *t,int s){
	if(t->root)
		t->size = s;
	else t->size = 0;
	return;
}


static BSTNODE *insertBSThelper(BSTNODE *root, BSTNODE *insertNode, BST *t){
	if(t->comparator(root->value, insertNode->value) > 0){

		if(root->left){
			return insertBSThelper(root->left, insertNode, t);
		}

		else{
			//BSTNODE *insertNode = newBSTNODE(value);
			//root->left = newBSTNODE(value);
			root->left = insertNode;
			insertNode->parent = root;
			return insertNode;
		}
	}

	else{

		if(root->right){
			return insertBSThelper(root->right, insertNode, t);
		}

		else{
			//	BSTNODE *insertNode = newBSTNODE(value);
			//	root->right = newBSTNODE(value);
			root->right = insertNode;
			insertNode->parent = root;
			return insertNode;
		}
	}
}

extern BSTNODE *insertBST(BST *t,void *value){
	BSTNODE *insertNode = newBSTNODE(value);
	if(t->root == 0){
		//t->root = newBSTNODE(value);
		t->root = insertNode;
				//t->root->parent = t->root;
		insertNode = t->root;
		t->size++;
		return insertNode;
	}

	else
	{
		t->size++;
		return insertBSThelper(t->root, insertNode, t);
	}

}

static BSTNODE *findBSThelper(BSTNODE *root, void *value, BST *t){
	if(root == 0 || t->comparator(root->value, value)==0)
		return root;

	if (t->comparator(root->value, value) > 0)
		return findBSThelper(root->left, value, t);

	else if(t->comparator(root->value, value) < 0)
		return findBSThelper(root->right, value, t);

	if(t->comparator(root->value, value))
		return 0;
	
	return 0;


}


extern BSTNODE *findBST(BST *t,void *value){

	if(t->root == 0 || t->comparator(t->root->value, value) == 0)
		return t->root;

	else
		//return findBST(t->root->right, value, t);
		return findBSThelper(t->root, value, t);

}

extern int sizeBST(BST *t){
	if(t->root == 0)
		return 0;

	else 
		return t->size;

}
/*
static BSTNODE *min(BSTNODE *root){
	BSTNODE *temp = root;

	while(temp->left != 0){
		temp = temp->left;
	}
	return temp;
}

static BSTNODE *max(BSTNODE *root){
	BSTNODE *temp = root;

	while(temp->right != 0){
		temp = temp->right;
	}
	return temp;
}

static BSTNODE *predecessor(BSTNODE *node){
	if(node->left != 0)
		return max(node);
	
//	BSTNODE *temp = node->parent;
//		while(temp != 0 && node == temp->parent){
//			node = temp;
//			temp = temp->parent;
//		}
	

	return node;
}

static BSTNODE *successor(BSTNODE *node){
	if(node->right != 0)
		return min(node->right);

	//BSTNODE *temp = node->parent;
	//	while(temp != 0 && node == temp->parent){
	//		node = temp;
	//		temp = temp->parent;
	//	}

	return node;
}
*/

static BSTNODE *predecessor(BSTNODE *node){
	BSTNODE *tempNode = node->left;

	if(tempNode->right == 0)
		return tempNode;
	
	else{
		while(tempNode->right != 0){
			tempNode = tempNode->right;
		}
	}

	return tempNode;
}

static BSTNODE *successor(BSTNODE *node){
	BSTNODE *tempNode = node->right;
	if(tempNode->left == 0)
		return tempNode;

	else{
		while(tempNode->left != 0)
			tempNode = tempNode->left;
		}

	return tempNode;
}
/*
extern BSTNODE *swapToLeafBST(BST *t, BSTNODE *node){
	if(node->left==0 && node->right==0)
		return node;
	else{
	if(node->right)
		BSTNODE *temp = successor(node);
	else if(node->right == 0 && node->left != 0)
		BSTNODE *temp = predeccessor(node);

	t->swapper(node, temp);
	return swapToLeafBST(t, temp);
	}
}*/


extern BSTNODE *swapToLeafBST(BST *t,BSTNODE *node){
	//if(t == 0)
	//	return 0;

	if (node->left == 0 && node->right == 0)
		return node;

	else if(node->right){
		BSTNODE *succ = successor(node);
		t->swapper(node, succ);
		return swapToLeafBST(t, succ);

	}

	else{
		if(node->left != 0 && node->right == 0){//node->left
		BSTNODE *pred = predecessor(node);
		t->swapper(node, pred);
		return swapToLeafBST(t, pred);
		}
		//	else return node;

	}
	return node;
}

extern void pruneLeafBST(BST *t, BSTNODE *leaf){

	if (t->size == 1 || t->root == leaf){
		t->root = 0;
	}

	else if(leaf->parent->left == leaf)
			leaf->parent->left = 0;
	//		leaf->parent = 0;
	else{
		leaf->parent->right = 0;
	//			leaf->parent = 0;
		}
	t->size--;
	return;
}

extern BSTNODE *deleteBST(BST *t,void *value){
	BSTNODE *node = findBST(t, value);

	//if(node != 0){
	if(t->root == 0){
		return t->root;
	}
	
	//else if(node->left == 0 && node->right == 0){
	//	BSTNODE *temp = node;
	//	return temp;
	//}
	
	else{
		//if(node->left != 0 && node->right != 0)
		BSTNODE *temp = swapToLeafBST(t, node);
		pruneLeafBST(t, temp);
//		t->size--;
		return temp;
	}
}


static int minDepthHelper(BSTNODE *t){

	if(t == 0){
		return 0;
	}
	else{
		int lDepth = minDepthHelper(t->left);
		int rDepth = minDepthHelper(t->right);
		if(lDepth < rDepth)
			return(lDepth + 1);
		else
			return(rDepth + 1);
	}
}

static int minDepth(BST *t){
	if(t->root == 0)
		return 0;

	else
		return minDepthHelper(t->root)-1;
}


static int maxDepthHelper(BSTNODE *t){
	if(t == NULL)
		return 0;

	else{
		int lDepth = maxDepthHelper(t->left);
		int rDepth = maxDepthHelper(t->right);
		if(lDepth > rDepth)
			return(lDepth + 1);
		else
			return(rDepth + 1);
	}
}

static int maxDepth(BST *t){

	if(t->root == NULL)
		return 0;
	else
		return maxDepthHelper(t->root)-1;

}

extern void statisticsBST(BST *t,FILE *fp){

	fprintf(fp, "Nodes: %d\n", sizeBST(t));
	if(sizeBST(t) == 0){
		fprintf(fp, "Minimum depth: -1\n");
		fprintf(fp, "Maximum depth: -1\n");
	}
	else{
		fprintf(fp, "Minimum depth: %d\n", minDepth(t));
		fprintf(fp, "Maximum depth: %d\n", maxDepth(t));
	}
	return;

}

static void preorder(BSTNODE *root, FILE *fp, BST *t){
	if(root != 0){
		if(t->comparator(root->value, t->root->value)==0){
			fprintf(fp, "[");
			t->display(root->value, fp);
		}
		else{
			fprintf(fp, " [");
			t->display(root->value, fp);
		}
		preorder(root->left, fp, t);
		preorder(root->right, fp, t);
		fprintf(fp, "]");
	}
}

extern void displayBST(BST *t,FILE *fp){
	if(t->root == 0 && t->size == 0)
		fprintf(fp, "[]");

	else
		preorder(t->root, fp, t);

}

extern void displayBSTdebug(BST *t,FILE *fp){

	if(t == 0 || t->size == 0 || t->root == 0)
		return;

	QUEUE *levelOrder = newQUEUE(t->display,t->free);

	enqueue(levelOrder, t->root);
	//enqueue(levelOrder, 0);
	while(1){
		int nodeCount = sizeQUEUE(levelOrder);
		if(nodeCount == 0)
			break;
		while (nodeCount > 0){
			BSTNODE *tempNode = peekQUEUE(levelOrder);
			t->display(tempNode->value, fp);
			dequeue(levelOrder);
			if(tempNode->left)
				enqueue(levelOrder,tempNode->left);
			if(tempNode->right)
				enqueue(levelOrder,tempNode->right);
			nodeCount--;
			if(nodeCount != 0)
			fprintf(fp, " ");
		}
		fprintf(fp, "\n");
	}
	freeQUEUE(levelOrder);
	return;
}


static void freeBSThelp(BSTNODE *node,BST *t ){
	if(node == 0) 
		return;

	else{
		freeBSThelp(node->left, t);
		freeBSThelp(node->right,t);
		freeBSTNODE(node, t->free);
	}
	return;
}

extern void freeBST(BST *t){
	if (t == 0 && t->root == 0 && t->size == 0)
		return;

	else{
		freeBSThelp(t->root, t);
	}

	free(t);
	return;
}

