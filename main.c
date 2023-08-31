#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ncurses.h>

const char* getRandomWord(char *filename){
	char buffer[4096];
	FILE *file = fopen(filename, "r");
	int lineCount, randomLine, lineNumber = 0;

	srand(time(0));

	file = fopen(filename, "r");
	if (file == NULL) {
		printf("An error has occured. %s could not be accessed or does not exists.", filename);
		return NULL;
	}

	while (fgets(buffer, sizeof(buffer), file) != NULL) {
		lineCount++;
	}
	fclose(file);

	randomLine = rand() % lineCount + 1;

	file = fopen(filename, "r");
	while (fgets(buffer, sizeof(buffer), file) != NULL) {
		lineNumber++;
		if (lineNumber == randomLine){
			char *randomWord = malloc(sizeof(buffer));
			strcpy(randomWord, buffer);
			if (randomWord == NULL){
				printf("Failed to allocate memory.");
				return NULL;
			}
			fclose(file);
			return randomWord;
		}
	}

	fclose(file);
	printf("Failed to fetch a non-empty word.");
	return NULL;
}

int main()
{
	printf(getRandomWord("words_alpha.txt"));
	return 0;
}
