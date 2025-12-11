// Lab 9 DS4Talker Skeleton Code

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include <ncurses/ncurses.h>
#define MAXWORDS 100
#define WORDLEN 11
#define DEBUG 0   // set to 0 to disable debug output

// reads words from the file
// into wl and trims the whitespace off of the end of each word
// DO NOT MODIFY THIS Prototype
// Students are REQUIRED to use fgets() to retreive each line from the file. 
int readWords(char* wl[MAXWORDS], char* filename); 

// modifies s to trim white space off the right side
// DO NOT MODIFY THIS Prototype
void trimws(char* s);

// print the words from the given array in an array
void printWords(char* wl[MAXWORDS]);

// print the words in the sentence below
void printSentence(char sentence[80], int* index);

// returns the correct word based off of joystick position
char* findWord(char* wl[MAXWORDS], int x, int y);

// move the cursor by delta[x or y] amount
void moveCursor(int* x, int* y, int deltaX, int deltaY);

// calculates the movement based off joystick and calls moveCursor as needed
void calcJoy(int l_joyX, int l_joyY, int r_joyX, int r_joyY, int time, int *lastPress, int* curX, int* curY, int* sentenceClear);

// apend word to sentence, with and without a space, then update history accordingly
void append_s(char* word, char sentence[80], int history[80]);
void append(char* word, char sentence[80], int history[80]);

void capitalize(char* word);

void delete(char sentence[80], int history[80]);

int main(int argc, char* argv[]) 
{
	char* wordlist[MAXWORDS];
	int wordCount;
	wordCount = readWords(wordlist, argv[1]);

	(void)argc;

	if (wordCount == -1) {
		printf("The file could not be opened!\n");
		return -1;
	}

	if (DEBUG) {
		printf("Read %d words from %s \n", wordCount, argv[1]);

		// add code to print the words to the screen here for part 1 
		for (int i = 0; i < wordCount; i++) {
			printf("%s", wordlist[i]);
		}

		return 0;
	}

	// most of your code for part 2 goes here. Don't forget to include the ncurses library
	int time, lastPress = 0; 	// time since last pressed 
	int triangle, o, x, square;	// button inputs
	int l_joyX, l_joyY; 		// left joystick x and y values
	int r_joyX, r_joyY; 		// right joystick x and y values
	
	// Flags
	int running = 1;		// should the program be running?
	int sentenceClear = 0;	// should the sentence be cleared?
	int capitalized = 0;	// has this word been capitalized?
	int tPressed = 0; 		// triangle button pressed?
	int oPressed = 0;		// o button pressed?
	int xPressed = 0;		// x button pressed?
	int sPressed = 0;		// square button pressed?

	// Cursor Position
	int curX = 0;
	int curY = 0;

	// Sentence
	char sentence[80];
	char* selectedWord;
	int history[80]; // edit history in lengths. a -1 represents no history

	for (int i = 0; i < 79; i++) {
		history[i] = -1;
	}

	initscr();

	moveCursor(&curX, &curY, 0, 0);

	refresh();

	do {
		mvprintw(20, 0, "--> ");
		printWords(wordlist);

		if (sentenceClear == 1) {
			sentenceClear = 0;
			memset(sentence, 0, strlen(sentence));

			for (int i = 0; history[i] != -1; i++) {
				history[i] = -1;
			}
			clear();
		}

		scanf("%d, %d, %d, %d, %d, %d, %d, %d, %d", &time, &triangle, &o, &x, &square, &l_joyX, &l_joyY, &r_joyX, &r_joyY);

		calcJoy(l_joyX, l_joyY, r_joyX, r_joyY, time, &lastPress, &curX, &curY, &sentenceClear);

		selectedWord = findWord(wordlist, curX, curY);

		if (o == 1 && capitalized == 0 && oPressed == 0) {
			capitalized = 1;
			oPressed = 1;
		} else if (o == 1 && capitalized == 1 && oPressed == 0) {
			capitalized = 0;
			oPressed = 1;
		} else if (o == 0) {
			oPressed = 0;
		}

		if (capitalized == 1) {
			for (int i = 0; i < wordCount; i++) {
				capitalize(wordlist[i]);
			}
		} else {
			for (int i = 0; i < wordCount; i++) {
				wordlist[i][0] = tolower(wordlist[i][0]);
			}
		}

		if (triangle == 1 && tPressed == 0) {
			append_s(selectedWord, sentence, history);

			capitalized = 0;
			tPressed = 1;
		} else if (triangle == 0) {
			tPressed = 0;
		}

		if (x == 1 && xPressed == 0) {
			clear();
			delete(sentence, history);
			xPressed = 1;
		} else if (x == 0) {
			xPressed = 0;
		}

		if (square == 1 && sPressed == 0) {
			append(selectedWord, sentence, history);

			capitalized = 0;
			sPressed = 1;
		} else if (square == 0) {
			sPressed = 0;
		}
		
		/* Debug step that prints some of the appendage history
		for (int i = 0; i < 10; i++) {
			mvprintw(22, 4 + (3 * i), "%+d", history[i]);
		}
		*/ 

		mvprintw(20, 4, "%s", sentence);
		refresh();
		
		running = square + x;
	} while (running < 2);

	refresh();

	// strdup (used in readWords) calls malloc, meaning we need to free the memory at some point
	for (int i = 0; i <= wordCount; i++) {
		free(wordlist[i]);
	}

	// Clean  up the ncurses window
	endwin();

    return 0;
}

int readWords(char* wl[MAXWORDS], char* filename)
{
	FILE* tmp = fopen(filename, "r");
	if (tmp == NULL) {
		return -1;
	}

	int count = 0;

	char buffer[WORDLEN];
	while (fgets(buffer, sizeof(buffer), tmp) != NULL) {
		// wl[count] = malloc(strlen(buffer) + 1);
		// strcpy(wl[count], buffer);
		trimws(buffer);
		wl[count] = strdup(buffer);
		count++;
	}

	fclose(tmp);
	return count;
}

void trimws(char* s)
{
	for(int i = 0; i < (int) strlen(s); i++) {
		if (isspace(s[i])) {
			s[i] = '\0';
		}
	}
}

void printWords(char* wl[MAXWORDS])
{
	int k = 0;
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 5; j++) {
			if (wl[k] != NULL) {
				mvprintw(i + 1, (j * 15) + 2, "%s", wl[k]);
				k++;
			}
		}
	}
}

char* findWord(char* wl[MAXWORDS], int x, int y)
{
	int index = x + (y * 5);
	return wl[index];
}

void moveCursor(int *x, int *y, int deltaX, int deltaY)
{
	mvaddch(*y + 1, (*x * 15) + 1, ' ');

	*x += deltaX;
	*y += deltaY;

	if (*x < 0) {
		*x = 0;
	} else if (*x > 4) {
		*x = 4;
	}

	if (*y < 0) {
		*y = 0;
	} else if (*y > 15 && *x == 0) {
		*y = 15;
	} else if (*y > 14 && *x > 0) {
		*y = 14;
	}

	mvaddch(*y + 1, (*x * 15) + 1, '>');
}

void calcJoy(int l_joyX, int l_joyY, int r_joyX, int r_joyY, int time, int* lastPress, int* curX, int* curY, int* sentenceClear) 
{
	int elapsed = time - *lastPress;
	int interval = 250;

	int joyX = (abs(l_joyX) > abs(r_joyX)) ? l_joyX : r_joyX;
	int joyY = l_joyY;

	if (joyX > 100 && elapsed > interval) {
		*lastPress = time;
		moveCursor(curX, curY, 1, 0);
	}
	
	if (joyX < -100 && elapsed > interval) {
		*lastPress = time;
		moveCursor(curX, curY, -1, 0);
	}

	if (joyY > 100 && elapsed > interval) {
		*lastPress = time;
		moveCursor(curX, curY, 0, 1);
	}
	
	if (joyY < -100 && elapsed > interval) {
		*lastPress = time;
		moveCursor(curX, curY, 0, -1);
	}

	if (r_joyY > 100 && elapsed > interval) {
		*lastPress = time;
		*sentenceClear = 1;
	}

	moveCursor(curX, curY, 0, 0);
}

void append_s(char* word, char sentence[80], int history[80])
{
	int mod = 1;


	if (strlen(sentence) + strlen(word) < 80) {
		strcat(sentence, word);

		if (strlen(word) > 1 || isalpha(word[0])) {
			strcat(sentence, " ");
		} else {
			mod = 0;
		}

		int i;
		for (i = 0; history[i] != -1; i++) {}

		history[i] = strlen(word) + mod;
	}
}

void append(char* word, char sentence[80], int history[80])
{
	if (strlen(sentence) + strlen(word) < 80) {
		strcat(sentence, word);

		int i;
		for (i = 0; history[i] != -1; i++) {}

		history[i] = strlen(word);
	}
}

void capitalize(char* word)
{
	word[0] = toupper(word[0]);
}

void delete(char sentence[80], int history[80])
{
	int i;
	char oldSentence[80];

	strcpy(oldSentence, sentence);

	for (i = 0; history[i] != -1; i++) {}

	if (i != 0) {
		int removal = history[i - 1];
		history[i - 1] = -1; 

		// strncpy(sentence, oldSentence, strlen(sentence) - removal);

		// strcat(sentence, "\0");

		memset(sentence, 0, strlen(sentence));

		strncpy(sentence, oldSentence, strlen(oldSentence) - removal);
	}
}