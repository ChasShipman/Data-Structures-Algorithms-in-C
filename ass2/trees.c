#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>
#include "scanner.h"
#include "gst.h"
#include "avl.h"
#include "string.h"
#include "queue.h"


static char *cleanToken(char *token);
static AVL *evaluateDataAVL(FILE *, AVL *treeA);
static void evaluateCommandsAVL(FILE *, FILE *, AVL *treeA);
static GST *evaluateDataGST(FILE *, GST *treeG);
static void evaluateCommandsGST(FILE *, FILE *, GST *treeG);


int main(int argc, char **argv) {

	int argIndex = 1;

	int option = 0;

	FILE *fpData;
	FILE *fpCommand;
	FILE *fpOutput;

	AVL *treeA = newAVL(displaySTRING, compareSTRING, freeSTRING);
	GST *treeG = newGST(displaySTRING, compareSTRING, freeSTRING);

	if(*argv[argIndex] == '-') {

		if(argv[argIndex][1] == 'g') {

			option = 1;
		}
		else if(argv[argIndex][1] == 'v') {

			fprintf(stdout, "Chas Shipman\n");
			exit(0);
		}
		++argIndex;
	}
	fpData = fopen(argv[argIndex], "r");
	++argIndex;
	fpCommand = fopen(argv[argIndex], "r");
	++argIndex;
	if(argIndex < argc) {

		fpOutput = fopen(argv[argIndex], "w+");
	}
	else {

		fpOutput = stdout;
	}

	if(option == 1) {

		treeG = evaluateDataGST(fpData, treeG);

		evaluateCommandsGST(fpCommand, fpOutput, treeG);
	}
	else {

		treeA = evaluateDataAVL(fpData, treeA);
		evaluateCommandsAVL(fpCommand, fpOutput, treeA);
	}

	return 0;
}

static char *readPhrase(FILE *fp) {

	if(stringPending(fp)) {
		return readString(fp);	}
	else {
		return readToken(fp);	}
}

static char *cleanToken(char *token) {

	size_t x = 0;
	size_t y = 0;
	size_t length = strlen(token);
	while(x < length) {

		char c = token[x];
		if(!ispunct(c) && !isspace(c) && isalpha(c)) {

			token[y] = tolower(c);
			y++;
		}
		else if(y > 0 && isspace(c) && islower(token[y-1])) {

			token[y] = ' ';
			y++;
		}
		x++;
	}
	if(isspace(token[y-1])) {
		token[y - 1] = '\0';	}
	while(y < length) {

		token[y] = '\0';
		y++;
	}
	return token;
}

static AVL *evaluateDataAVL(FILE *fpData, AVL *treeA) {

	char *fileToken = 0;
	fileToken = readPhrase(fpData);
	while(fileToken) {

		fileToken = cleanToken(fileToken);
		if(islower(fileToken[0])) insertAVL(treeA, newSTRING(fileToken));
		fileToken = readPhrase(fpData);
	}
	fclose(fpData);
	return treeA;
}


static GST *evaluateDataGST(FILE *fpData, GST *treeG) {

	char *fileToken = 0;
	fileToken = readPhrase(fpData);
	while(fileToken) {

		fileToken = cleanToken(fileToken);
		if(islower(fileToken[0])) insertGST(treeG, newSTRING(fileToken));
		fileToken = readPhrase(fpData);
	}
	fclose(fpData);
	return treeG;
}

static void evaluateCommandsAVL(FILE *fpCommand, FILE *fpOutput, AVL *treeA) {

	char *fileToken = 0;
	fileToken = readPhrase(fpCommand);
	void *delete = 0;
	while(fileToken) {

		switch(fileToken[0]) {

			case 'i':
				fileToken = cleanToken(readPhrase(fpCommand));
				if(islower(fileToken[0])) insertAVL(treeA, newSTRING(fileToken));
				break;
			case 'd':
				fileToken = cleanToken(readPhrase(fpCommand));
				if(islower(fileToken[0])) delete = deleteAVL(treeA, newSTRING(fileToken));
				if(findAVL(treeA, newSTRING(fileToken)) == 0 && delete == 0 && strcmp(fileToken, "")!=0) fprintf(fpOutput, "Value %s not found.\n", fileToken);
				break;
			case 'f':
				fileToken = cleanToken(readPhrase(fpCommand));
				fprintf(fpOutput,"Frequency of %s: %d\n", fileToken, findAVLcount(treeA, newSTRING(fileToken)));
				break;
			case 's':
				displayAVL(treeA, fpOutput);
				break;
			case 'r':
				statisticsAVL(treeA, fpOutput);
				break;
			default:
				fprintf(stdout, "evaluateCommandsRBT - defaulted on : ---- %s ----\n", fileToken);
				break;
		}
		fileToken = readPhrase(fpCommand);
	}
}

static void evaluateCommandsGST(FILE *fpCommand, FILE *fpOutput, GST *treeG) {

	char *fileToken = 0;
	fileToken = readPhrase(fpCommand);
	void *delete = 0;
	while(fileToken) {

		switch(fileToken[0]) {

			case 'i':
				fileToken = cleanToken(readPhrase(fpCommand));
				if(islower(fileToken[0])) insertGST(treeG, newSTRING(fileToken));
				break;
			case 'd':
				fileToken = cleanToken(readPhrase(fpCommand));
				//if(strcmp(fileToken, "")==0){
				//	fileToken = "space";
				//	fprintf(stdout, "%s", fileToken);
				//}

				if(islower(fileToken[0])) delete = deleteGST(treeG, newSTRING(fileToken));
				if(findGST(treeG, newSTRING(fileToken)) == 0 && delete == 0 && strcmp(fileToken, "")!= 0) fprintf(fpOutput, "Value %s not found.\n", fileToken);
				//if(delete == (void*)-1) fprintf(fpOutput, "Value %s not found.\n", fileToken);
				break;
			case 'f':
				fileToken = cleanToken(readPhrase(fpCommand));
				fprintf(fpOutput,"Frequency of %s: %d\n", fileToken, findGSTcount(treeG, newSTRING(fileToken)));
				break;
			case 's':
				displayGST(treeG,fpOutput);
				break;
			case 'r':
				statisticsGST(treeG, fpOutput);
				break;
			default:
				fprintf(stdout, "evaluateCommandsGT - defaulted on : ---- %s ----\n", fileToken);
				break;
		}
		fileToken = readPhrase(fpCommand);
	}
}
