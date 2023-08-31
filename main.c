#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ncurses.h>

char* getRandomWord(char *filename){
	char buffer[4096];
	FILE *file;
	int lineCount, randomLine, lineNumber;

	file = fopen(filename, "r");
	if (file == NULL) {
		printf("An error has occured. %s could not be accessed or does not exists.\n", filename);
		return NULL;
	}

	lineCount = 0;
	while (fgets(buffer, sizeof(buffer), file) != NULL) {
		lineCount++;
	}
	fclose(file);

	randomLine = rand() % lineCount + 1;

	file = fopen(filename, "r");
	lineNumber = 0;
	while (fgets(buffer, sizeof(buffer), file) != NULL) {
		lineNumber++;
		if (lineNumber == randomLine){
			char *randomWord = malloc(sizeof(buffer));
			strcpy(randomWord, buffer);
			if (randomWord == NULL){
				printf("Failed to allocate memory.\n");
				return NULL;
			}
			fclose(file);

			return randomWord;
		}
	}

	fclose(file);
	printf("Failed to fetch a non-empty word.\n");
	return NULL;
}

int main()
{
	srand(time(NULL));

	for(int i=0 ; i<100 ; i++){
		char *randomWord = getRandomWord("words_alpha.txt");
		printf(randomWord);
		free(randomWord);
	}
	return 0;
}
