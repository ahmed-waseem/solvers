#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"
#include "jacobi.h"

void main_menu();

int main()
{
	printf("Scientific Solvers\n");
	printf("type \"help\" for help on available commands.\n");
	while(1)
		main_menu();

	return 0;
}

void main_menu()
{
	char userInput[200];
	printf(">>> ");
	fgets(userInput, sizeof(userInput), stdin);
	userInput[strlen(userInput)-1] = '\0';

	char arg[5][50] = {}, *token;
	int x = 0;

	/* get the first token */
	token = strtok(userInput, " ");

	//  walk through other tokens
	while (token != NULL) {
		strcpy(arg[x++], token);
		token = strtok(NULL, " ");
	}

	if (strcmp(arg[0], "exit") == 0) {
		exit(0);
	}
	else if (strcmp(arg[0], "help") == 0) {
		printf("Help on commands not yet available!\n");
	}
	else if (strcmp(arg[0], "jacobi") == 0) {
		// jacobi("data/input.3", "data/output.3");
		jacobi(arg[1], arg[2]);
	}
	else if (strcmp(arg[0], "exit") == 0) {
		exit(0);
	}

	/*
	for(x=0; x<5; x++) {
		if (arg[x][0] == '\0') break;
		printf("Arg %d is %s\n", x, arg[x]);
	}
	*/

	free(token);
}
