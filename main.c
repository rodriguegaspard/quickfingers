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
	init_pair(100, COLOR_YELLOW, COLOR_BLACK);
	attron(A_BOLD);
	attron(COLOR_PAIR(100));
	mvprintw(x, y, "%s", word);
	attroff(COLOR_PAIR(100));
	attroff(A_BOLD);
}

void printGuess(char* word, int x, int y, int counter, char input){
	//Initializing colors
	init_pair(101, COLOR_GREEN, COLOR_BLACK);
	init_pair(102, COLOR_RED, COLOR_BLACK);

	int word_length = strlen(word);

	for(int i = 0; i < word_length; i++){
		if (input != word[counter] && i == counter){
			attron(A_BOLD | A_UNDERLINE);
			attron(COLOR_PAIR(102));
			mvaddch(x, y+i, word[i]);
			attroff(COLOR_PAIR(102));
			attroff(A_BOLD | A_UNDERLINE);
		}
		else
		{
			if(i < counter){
				attron(A_BOLD);
				attron(COLOR_PAIR(101));
				mvaddch(x, y+i, word[i]);
				attroff(COLOR_PAIR(101));
				attroff(A_BOLD);
			}
			else{
				attron(A_DIM);
				mvaddch(x, y+i, word[i]);
				attroff(A_DIM);
			}
		}
	}
	refresh();
}

void guessWord (char *word, int x, int y){
	char input;
	int word_length = strlen(word) - 1;
	int counter = 0;

	mvprintw(x, y, "%s", word);

	while(counter < word_length){
		input = getch();
		if (input == word[counter]) counter++;
		printGuess(word, x, y, counter, input);
	}
}

int main()
{
	// INITIALIZATION
	srand(time(NULL));
	char *WORD_FILE = "english.txt";
	char word[MAX_WORD_LENGTH];
	int max_x, max_y;

	initscr();
	start_color();
	getmaxyx(stdscr, max_x, max_y);

	curs_set(0);
	raw();
	noecho();

	for(int i=0; i<5; i++){
		clear();
		getRandomWord(WORD_FILE, word);
		printWord(word, max_x/2-1, (max_y-strlen(word))/2);
		guessWord(word, (max_x/2)+1, (max_y-strlen(word))/2);
	}

	refresh();
	endwin();

	return 0;
}
