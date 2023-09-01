#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ncurses.h>



#define MAX_WORD_LENGTH 512

void getRandomWord(const char *filename, char* random_word){
	char line[MAX_WORD_LENGTH];
	FILE *file;
	int line_count, random_line, line_number;

	file = fopen(filename, "r");
	if (file == NULL) {
		printf("An error has occured. %s could not be accessed or does not exists.\n", filename);
	}

	line_count = 0;
	while (fgets(line, MAX_WORD_LENGTH, file) != NULL) {
		line_count++;
	}

	random_line = rand() % line_count + 1;

	file = fopen(filename, "r");
	line_number = 0;
	rewind(file);

	while (fgets(line, MAX_WORD_LENGTH, file) != NULL) {
		line_number++;
		if (line_number == random_line){
			fclose(file);
			strcpy(random_word, line);
			return;
		}
	}

	fclose(file);
	printf("Failed to fetch a non-empty word.\n");
	return;
}

void printWord(char* word, int x, int y){
	attron(A_BOLD);
	attron(COLOR_PAIR(1));
	mvprintw(x, y, "%s", word);
	attroff(COLOR_PAIR(1));
	attroff(A_BOLD);
}

int main()
{
	// INITIALIZATION
	srand(time(NULL));
	char *WORD_FILE = "english.txt";
	char word[MAX_WORD_LENGTH];
	int row, col;

	initscr();
	start_color();
	init_pair(1, COLOR_YELLOW, COLOR_BLACK);
	getmaxyx(stdscr, row, col);
	raw();
	noecho();

	getRandomWord(WORD_FILE, word);
	printWord(word, row/2, (col-strlen(word))/2); //Prints at the center of the screen

	refresh();
	getch();
	endwin();

	return 0;
}
