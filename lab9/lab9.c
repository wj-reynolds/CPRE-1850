// Lab 9 DS4Talker Skeleton Code

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#define MAXWORDS 100
#define WORDLEN 11
#define DEBUG 1   // set to 0 to disable debug output

// reads words from the file
// into wl and trims the whitespace off of the end of each word
// DO NOT MODIFY THIS Prototype
// Students are REQUIRED to use fgets() to retreive each line from the file. 
int readWords(char* wl[MAXWORDS], char* filename); 

//modifies s to trim white space off the right side
// DO NOT MODIFY THIS Prototype
void trimws(char* s) ;

int main(int argc, char* argv[]) 
{
	char* wordlist[MAXWORDS];
	int wordCount;
	int i;
	wordCount = readWords(wordlist, argv[1]);

	if (DEBUG) {
		if (wordCount != -1)
			printf("Read %d words from %s \n", wordCount, argv[1]);

		// add code to print the words to the screen here for part 1 
		if (wordCount == -1) {
			printf("The file could not be opened!\n");
			return -1;
		}

		for (int i = 0; i < wordCount; i++) {
			//trimws(wordlist[i]);
			printf("%s", wordlist[i]);
		}
	}

	// most of your code for part 2 goes here. Don't forget to include the ncurses library 



	// strdup (used below) calls malloc, meaning we need to free the memory at some point
	for (int i = 0; i <= wordCount; i++) {
		free(wordlist[i]);
	}

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