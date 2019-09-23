#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scanner.h"
#include "heap.h"
#include "integer.h"
#include "real.h"
#include "string.h"
#include "bst.h"
#include "queue.h"

static char *readItem(FILE *);
static void (*reader)(FILE *,HEAP *);
static int (*compare)(void *,void *);
static void (*display)(void *,FILE *);
static void (*release)(void *);

static void readREAL(FILE *, HEAP *);
static void readSTRS(FILE *, HEAP *);
static void readINTS(FILE *, HEAP *);
static int processOptions(int, char **, int choice[], int order[]);
static int heapOrder(int order[] );
static void printHEAP(HEAP *h,FILE *fp);

int main(int argc, char **argv){

	int choice[1] = {1};
	int order[1] = {1};
	int argIndex;

	argIndex = processOptions(argc, argv, choice, order);
	int hpOrder = heapOrder(order);

	FILE *fp = fopen(argv[argIndex], "r");

	if (choice[0] == 2)//if argv = -r
	{
		reader = readREAL;
		release = freeREAL;
		display = displayREAL;
//		if(order[0]== -1){
//			compare = rcompareREAL;
//		}
//		else{
			compare = hpOrder == 1? compareREAL : rcompareREAL;
//		}
	}

	else if (choice[0] == 3)//if argv = -s
	{
		reader = readSTRS;
		release = freeSTRING;
		display = displaySTRING;
//		if(order[0] == 1)
//			compare = compareSTRING;
//		else
			compare = hpOrder == 1? compareSTRING : rcompareSTRING;
	}

	else//if argv = -i
	{
		reader = readINTS;
		release = freeINTEGER;
		display = displayINTEGER;
//		if(order[0] == 1){
//			compare = compareINTEGER;
//		}
//		else{
			compare = hpOrder == 1? compareINTEGER : rcompareINTEGER;
//		}
	} 

	HEAP *h = newHEAP(display,compare,release);
	reader(fp,h);
	buildHEAP(h);
	printHEAP(h, stdout);

	//at this point, the heap is ready for buildHEAP
	return 0;
}

static char *readItem(FILE *fp){
	if(stringPending(fp))
		return readString(fp);
	else
		return readToken(fp);
}


static void readREAL(FILE *fp, HEAP *h){
	REAL *num = 0;
	double newReal = readReal(fp);
	while(!(feof(fp))){
		num = newREAL(newReal);
		insertHEAP(h, num);
		newReal = readReal(fp);
	}
	fclose(fp);
	return;
}

static void readSTRS(FILE *fp, HEAP *h){
	STRING *abc = 0;
	char *newChar = readItem(fp);
	while(!(feof(fp))){
		abc = newSTRING(newChar);
		insertHEAP(h, abc);
		newChar = readItem(fp);
	}
	fclose(fp);
	return;

}

static void readINTS(FILE *fp, HEAP *h){
	INTEGER *num = 0;
	int newInt = readInt(fp);
	while(!(feof(fp))){
		num = newINTEGER(newInt);
		insertHEAP(h, num);
		newInt = readInt(fp);
	}
	fclose(fp);
	return;
}

static int processOptions(int argc, char **argv, int choice[], int order[]){
	int argIndex;
	//int argUsed;
	//int separateArg;
	//char *arg;

	argIndex = 1;

	while (argIndex < argc && *argv[argIndex] == '-')
	{
		/* check if stdin, represented by "-" is an argument */
		/* if so, the end of options has been reached */
		if (argv[argIndex][1] == '\0') return argIndex;

		//		separateArg = 0;
		//		argUsed = 0;
		//
		//		if (argv[argIndex][2] == '\0')
		//		{
		//			arg = argv[argIndex+1];
		//			separateArg = 1;
		//		}
		//		else
		//			arg = argv[argIndex]+2;
		//
		switch (argv[argIndex][1])
		{
			/*
			 * when option has an argument, do this
			 *
			 *     examples are -m4096 or -m 4096
			 *
			 *     case 'm':
			 *         MemorySize = atol(arg);
			 *         argUsed = 1;
			 *         break;
			 *
			 *
			 * when option does not have an argument, do this
			 *
			 *     example is -a
			 *
			 *     case 'a':
			 *         PrintActions = 1;
			 *         break;
			 */
			case 'v':
				fprintf(stdout, "Chas Shipman\n");
				exit(1);

			case 'i':
				choice[0] = 1; //"default";
//			printf("case i\n");
				break;

			case 'r':
				//	Special = 1;
				choice[0] = 2;//"reals";
//			printf("case r\n");
				break;

			case 's':
				choice[0] = 3;//"strings";
//			printf("case s\n");
				break;

			case 'I':
				order[0] = 1;//"INCREASING";
//			printf("case Increasing\n");
				break;

			case 'D':
				order[0] = -1;//"DECREASING";

				break;
			
			default:
//				order[0] = 1;//"default";
//			printf("case default\n");
//				choice[0] = 1; //"default";
				break;
//				Fatal("option %s not understood\n",argv[argIndex]);
		}


		++argIndex;
	}

	return argIndex;
}

static int heapOrder(int order[]){
	if(order[0]==1){
		return 1;
	}

	else{
//			printf("case Decreasing\n");
		return -1;
	}
}

static  void printHEAP(HEAP *h,FILE *fp){
		void *printer = extractHEAP(h);
	while(sizeHEAP(h) != 0){
		display(printer, fp);
		if(sizeHEAP(h)!=1)
			fprintf(fp, " ");
		printer = extractHEAP(h);
	}
			fprintf(fp, " ");
		display(printer, fp);
			fprintf(fp, "\n");

	return;
}
