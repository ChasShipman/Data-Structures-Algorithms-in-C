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
 *an abstract doubly-linked
 *data structure.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "dll.h"



typedef struct node{
	void *value;
	struct node *next;
	struct node *prev;
} NODE;



struct dll{
	void (*display)(void *, FILE *);
	void (*free)(void *);
	NODE *head;
	NODE *tail;
	int size;
};

static NODE *newNODE(){
	NODE *node = malloc(sizeof(NODE));
	node->value = 0;
	node->next = 0;
	node->prev = 0;
	return node;
}


extern DLL *newDLL(void (*d)(void *,FILE *),void (*f)(void *)){
	DLL *items = malloc(sizeof(DLL));
	assert(items != 0);
	items->head = 0;
	items->tail = 0;
	items->size = 0;
	items->display = d;
	items->free = f;
	return items;
}

extern void insertDLL(DLL *items,int index,void *value){
	assert(index >= 0 && index <= items->size);
	NODE *newNode = newNODE();
	newNode->value = value;

	if(items->size == 0){//if insert into empty
		items->head = items->tail = newNode;
		newNode->next = newNode->prev = 0;
	}

	else if(index == 0){//if insert at front
		newNode->next = items->head;
		items->head->prev = newNode;
		newNode->prev = 0;
		items->head = newNode;
	}

	else if(index == items->size){//if insert at end
		items->tail->next = newNode;
		newNode->next = 0;
		newNode->prev = items->tail;
		items->tail = newNode;
	}

	else{//insert in the middle
		if (index > (items->size/2)){//if index >= size/2}// from back 
			int i = items->size - 1;
		NODE *curTemp = items->tail;
		NODE *preTemp = items->tail->prev;
		while (i != index){
			curTemp = preTemp;//on insert
			preTemp = preTemp->prev;//previous of insert
			i--;
		}
		newNode->next = curTemp;//slide
		curTemp->prev = newNode;//in
		preTemp->next = newNode;//between
		newNode->prev = preTemp;//nodes
	}	

	else{//from the front
		NODE *prevTemp = items->head;
		NODE *currTemp = items->head->next; 
		int i = 0;
		while (i < index - 1){
			prevTemp = currTemp;//previous to insert;
			currTemp = currTemp->next;//on insert
			i++;
		}
		newNode->next = currTemp;//slide
		currTemp->prev = newNode;//in
		prevTemp->next = newNode;//between
		newNode->prev = prevTemp;//nodes
	}

}
items->size++;
return;
}

extern void *removeDLL(DLL *items,int index){
	assert(items->size > 0 && index >= 0 && index < items->size);
	void *valueHolder = 0;

	if(items->size == 1){
		NODE *tempNode = items->head;
		valueHolder = items->head->value;
		items->head->prev = 0;
		items->head = items->head->next;
		free(tempNode);
	}

	else if(index == 0){//if remove at front
		valueHolder = items->head->value;
		NODE *tempHead = items->head;
		items->head = items->head->next;
		free(tempHead);
		items->head->prev = 0;
	}

	else if(index == items->size -1){//if remove at end
		valueHolder = items->tail->value;
		NODE *tempTail = items->tail;
		items->tail = items->tail->prev;
		items->tail->next = 0;
		free(tempTail);

	}

	else{//remove at middle
		if (index > (items->size/2)){//if index >= size/2}// from back 
			int i = items->size - 1;
		NODE *curTemp = items->tail;
		NODE *preTemp = items->tail->prev;
		while (i != index){
			curTemp = preTemp;//on insert
			preTemp = preTemp->prev;//previous of insert
			i--;
		}
		valueHolder = curTemp->value;
		preTemp->next = curTemp->next;
		curTemp->next->prev = preTemp;
		free(curTemp);
	}

	else{//from the front
		NODE *prevTemp = items->head;
		NODE *currTemp = items->head->next; 
		int i = 0;
		while (i < index - 1){
			prevTemp = currTemp;//previous to insert;
			currTemp = currTemp->next;//on insert
			i++;
		}
		valueHolder = currTemp->value;
		prevTemp->next = currTemp->next;
		currTemp->next->prev = prevTemp;
		free(currTemp);
	}

}	
items->size--;
return valueHolder;
}



extern void unionDLL(DLL *recipient,DLL *donor){

	if(recipient->size == 0 && donor->size == 0){
		//if both lists are empty
		recipient->head = recipient->tail = donor->head = donor->tail= 0;
		return;
	}
	else if(recipient->size == 0 && donor->size != 0){
		//if recipient list is empty and donor is not
		recipient->size += donor->size;
		recipient->head = donor->head;
		recipient->tail = donor->tail;
		donor->head = donor->tail = 0;
		donor->size = 0;
	}

	else if(recipient->size != 0 && donor->size == 0){
		//if the donor is empty
		return;
	}

	else{
		//if both have stuff in them 
		recipient->size += donor->size;
		recipient->tail->next = donor->head;
		donor->head->prev = recipient->tail;
		recipient->tail = donor->tail;
		donor->head = donor->tail = 0;
		donor->size = 0;
	}
	return;
}


extern void *getDLL(DLL *items,int index){
	assert(index >= 0 && index < items->size);
	void *valueHolder = 0;
	if(index == 0){//if get head
		valueHolder = items->head->value;
	}

	else if(index == items->size -1){//if get tail
		valueHolder = items->tail->value;
	}

	else{//if get middle
		if (index > (items->size/2)){//if index >= size/2}// from back 
			int i = items->size - 1;
		NODE *curTemp = items->tail;
		NODE *preTemp = items->tail->prev;
		while (i != index){
			curTemp = preTemp;//on insert
			preTemp = preTemp->prev;//previous of insert
			i--;
		}
		valueHolder = curTemp->value;
	}	

	else{//from the front
		NODE *currTemp = items->head->next; 
		int i = 0;
		while (i < index - 1){
			currTemp = currTemp->next;//on insert
			i++;
		}
		valueHolder = currTemp->value;
	}

}
return valueHolder;
}


extern void *setDLL(DLL *items,int index,void *value){
	assert(index >= 0 && index <= items->size);
	void *valueHolder = 0;
	if(index == 0){//if get head
		valueHolder = items->head->value;
		items->head->value = value;
		return valueHolder;
	}

	else if(index == items->size){//if get tail
		insertDLL(items, index, value);	
		return items->tail->next;
	}

	else{//if get middle
		if (index > (items->size/2)){//if index >= size/2}// from back 
			int i = items->size - 1;
		NODE *curTemp = items->tail;
		NODE *preTemp = items->tail->prev;
		while (i != index){
			curTemp = preTemp;//on insert
			preTemp = preTemp->prev;//previous of insert
			i--;
		}
		valueHolder = curTemp->value;
		curTemp->value = value;
		return valueHolder;
	}	

	else{//from the front
		NODE *currTemp = items->head->next; 
		int i = 0;
		while (i < index - 1){
			currTemp = currTemp->next;//on insert
			i++;
		}
		valueHolder = currTemp->value;
		currTemp->value = value;
		return valueHolder;
	}

}

}

extern int sizeDLL(DLL *items){
	return items->size;
}

extern void displayDLL(DLL *items,FILE *fp){
	NODE *tempNode = items->head;

	if(items->size == 0){
		fprintf(fp, "{{}}");
		return;
	}
	else{
		fprintf(fp,"{{");
		while (tempNode->next != 0){
			items->display(tempNode->value, fp);
			fprintf(fp,",");
			tempNode = tempNode->next;
		}
		items->display(tempNode->value,fp);
		fprintf(fp,"}}");
		return;
	}
	return;
}

extern void displayDLLdebug(DLL *items,FILE *fp){
	NODE *tempHead = items->head;
	NODE *tempTail = items->tail;

	if(items->size == 0){
		fprintf(fp, "head->{{}},tail->{{}}");
		return;
	}
	else{
		fprintf(fp,"head->{{");
		while(tempHead->next != 0){
			items->display(tempHead->value, fp);
			fprintf(fp, ",");
			tempHead = tempHead->next;
		}
		items->display(tempHead->value, fp);
		fprintf(fp,"}},");
		fprintf(fp,"tail->{{");
		items->display(tempTail->value,fp);
		fprintf(fp,"}}");
		return;
	}
	return;
}

extern void freeDLL(DLL *items){
	if (items == 0 || items->head == 0 || items->tail == 0){
		free(items);
		return;
	}

	else{
		while (items->head){
			NODE *freeNode = items->head;
			freeNode->value = items->head->value;
			items->head = items->head->next;
			free(freeNode->value);
			free(freeNode);
		}
	}
	free(items);
	return;
}








