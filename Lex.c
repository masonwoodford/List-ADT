/*
 * File:   Lex.c
 * Author: Mason Woodford (mwoodfor@ucsc.edu)
 *
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "List.h"

#define MAX_LEN 1000

int main(int argc, char* argv[]) {
	if (argc != 3) {
		fprintf(stderr, "Error: two command line arguments required\n");
		exit(EXIT_FAILURE);
	}
	int line_count;
	FILE* input;
	FILE* output;
	int i = 0, j = 0;
	char line[MAX_LEN];
	input = fopen(argv[1], "r");
	if (input == NULL) {
		fprintf(stderr, "File Error: input file does not exist\n");
		exit(EXIT_FAILURE);
	}
	output = fopen(argv[2], "w");
	if (output == NULL) {
		fprintf(stderr, "File Error: output file does not exist\n");
		exit(EXIT_FAILURE);
	}
	line_count = 0;

	//------ Line counting + Placing indices into array -------//
	while (fgets(line, MAX_LEN, input)) {
		line_count++;
	}
	fseek(input, 0, SEEK_SET);
	char lines[line_count][MAX_LEN];
	while (fgets(line, MAX_LEN, input) != NULL) {
		strcpy(lines[i], line);
		i++;
	}
	fclose(input);
	List A = newList();
	append(A, 0);
	moveFront(A);

	//----- Sorting Algorithm --------//
	for (i = 1; i < line_count; i++) {
		for (j = 0; j < length(A); j++) {
			if (strcmp(lines[get(A)], lines[i]) > 0) {
				insertBefore(A, i);
				break;
			}
			if (index(A) == length(A) - 1) {
				append(A, i);
				break;
			}
			moveNext(A);
		}
		moveFront(A);
	}
	moveFront(A);

	//----- Printing based on indices of sorted array ------//
	while (index(A) >= 0) {
		i = get(A);
		fprintf(output, "%s", lines[i]);
		moveNext(A);
	}
	freeList(&A);
	fclose(output);
}
