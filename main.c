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

void guessWord (char *word, int x, int y){
	char input;
	int word_length = strlen(word);
	int counter = 0;

	while(counter < word_length - 1){
		input = getch();
		if (input == word[counter]) counter++;
		//Move this stuff in a different function..
		for(int i = 0; i < word_length; i++){
			if (input != word[counter] && i == counter){
				attron(A_BOLD | A_UNDERLINE);
				attron(COLOR_PAIR(3));
				mvaddch(x, y+i, input);
				attroff(COLOR_PAIR(3));
				attroff(A_BOLD | A_UNDERLINE);
			}
			else
			{
				if(i < counter){
					attron(A_BOLD);
					attron(COLOR_PAIR(2));
					mvaddch(x, y+i, word[i]);
					attroff(COLOR_PAIR(2));
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
	init_pair(1, COLOR_YELLOW, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_RED, COLOR_BLACK);
	getmaxyx(stdscr, max_x, max_y);

	curs_set(0);
	raw();
	noecho();

	for(int i=0; i<5; i++){
		clear();
		getRandomWord(WORD_FILE, word);
		printWord(word, max_x/2, (max_y-strlen(word))/2); //Prints at the center of the screen
		guessWord(word, (max_x/2)-1, (max_y-strlen(word))/2);
	}

	refresh();
	endwin();

	return 0;
}
