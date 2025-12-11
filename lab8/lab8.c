// WII-MAZE Skeleton code written by Jason Erbskorn 2007
// Edited for ncurses 2008 Tom Daniels
// Updated for Esplora 2013 TeamRursch185
// Updated for DualShock 4 2016 Rursch

// Headers
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ncurses/ncurses.h>
#include <time.h>
#include <unistd.h>

// Screen geometry
// Use ROWS and COLS for the screen height and width (set by system)
// MAXIMUMS
#define NUMCOLS 100
#define NUMROWS 72

// Character definitions taken from the ASCII table
#define AVATAR 'A'
#define WALL '*'
#define EMPTY_SPACE ' '

// 2D character array which the maze is mapped into
char MAZE[NUMROWS][NUMCOLS];

// POST: Generates a random maze structure into MAZE[][]
// You will want to use the rand() function and maybe use the output %100.  
// You will have to use the argument to the command line to determine how 
// difficult the maze is (how many maze characters are on the screen).
void generate_maze(int difficulty);

// PRE: MAZE[][] has been initialized by generate_maze()
// POST: Draws the maze to the screen 
void draw_maze(void);

// PRE: 0 < x < COLS, 0 < y < ROWS, 0 < use < 255
// POST: Draws character use to the screen and position x,y
void draw_character(int x, int y, char use);

/* This function takes in the current x and y positions of
 * the avatar, and then the change in x and y of the avatar.
 * Then, this function will move the avatar using the deltaX
 * and deltaY, all while taking into consideration collisions.
 * It will also delete the avatar character from where it last
 * was on screen.
 */
void move_avatar(int* curX, int* curY, int deltaX, int deltaY);

// Returns 1 if the current position is stuck.
int stuck(int curX, int curY);

// Returns -1 for num < 0, returns 1 for num > 0, returns 0 for 0
int sign(double num);

// Moving Average Functions
double avg(double buffer[], int numItems);
void updateBuffer(double buffer[], int length, int newItem);

// Controller Movement Functions
// PRE: -1.0 < x_mag < 1.0
// POST: Returns tilt magnitude scaled to -1.0 -> 1.0
// You may want to reuse the roll function written in previous labs.  
double roll(double xMag);

// Returns a value between -3 and 3 depending on the roll of the controller.
int scaleControllerMovement(double rad);

// Main - Run with './ds4rd.exe -t -g -b' piped into STDIN
int main(int argc, char* argv[])
{
	if (argc < 2) {
		printf("You forgot the difficulty\n"); 
		return 1;
	}
	
	// Generate a seed based off the current time so the rand() function is more random
	srand(time(NULL)); 
	
	// Get difficulty from first command line argument
	int difficulty = atoi(argv[1]); 
	
	// Player Data
	int playerX = 50;
	int playerY = 0;
	
	// Controller Data
	int time, deltaX, moveTimer;
	int lengthofavg = 10;
	double gx, gy, gz;
	double agx; // Average gx
	double xBuffer[100]; // 100 is a placeholder
	
	// Flags
	int started = 0;	// Has the player started moving?
	int movedX = 0; 	// Have we already moved on the x-axis in this time frame?
	int movedY = 0; 	// Have we already moved on the y-axis in this time frame?
	int won = 0;		// Have we won the game? (reached the bottom?)
	int isStuck = 0;	// Are we stuck?
	
	// Read gyroscope data to get ready for using moving averages.
	for (int i = 0; i < lengthofavg; i++) {
		scanf("%d, %lf, %lf, %lf", &time, &gx, &gy, &gz);
		updateBuffer(xBuffer, lengthofavg, gx);
	}
	
	// Setup Screen  
	initscr();
	refresh();

	// Generate and draw the maze, with initial avatar
	generate_maze(difficulty);
	draw_maze();
	move_avatar(&playerX, &playerY, 0, 0);

	// Event loop
	do
	{
		scanf("%d, %lf, %lf, %lf", &time, &gx, &gy, &gz);
		
		agx = avg(xBuffer, lengthofavg);
		
		deltaX = scaleControllerMovement(roll(gx));

		// Read data, update average
		updateBuffer(xBuffer, lengthofavg, gx);
		
		// Avatar Placed & Waiting
		if (abs(deltaX) > 0) {
			started = 1;
		}
		
		moveTimer = 200 - (45 * sign(deltaX) * deltaX);
		
		// Is it time to move?  If so, then move avatar
		if (time % moveTimer < 20 && movedX == 0 && started == 1) {
			move_avatar(&playerX, &playerY, 1 * sign(deltaX), 0);
			movedX = 1;
		} else if (time % moveTimer > 50 && movedX == 1) {
			movedX = 0;
		}
		
		// Begin Fall
		if (time % 250 < 25 && movedY == 0 && started == 1) {
			move_avatar(&playerX, &playerY, 0, 1);
			movedY = 1;
		} else if (time % 250 > 125 && movedY == 1) {
			movedY = 0;
		}
		
		if (playerY > 70) { // Have we won?
			won = 1;
		} else {
			isStuck = stuck(playerX, playerY);
		}
	} while(won == 0 && isStuck == 0);

	// Give the player a second to see that they either won or lost
	while (time % 1000 < 950) {
		scanf("%d, %lf, %lf, %lf", &time, &gx, &gy, &gz);
	}
	
	
	endwin();
	
	// Print the win message
	if (won == 1) {
		printf("YOU WIN!\n");
	} else {
		printf("YOU LOSE!\n");
	}
	
	return 0;
}


void generate_maze(int difficulty)
{
	int tRand; // temporary random integer

	for (int i = 0; i < NUMCOLS; i++) {
		for (int j = 0; j < NUMROWS; j++) {
			tRand = rand() % 100;
			if (tRand < difficulty) {
				MAZE[j][i] = WALL;
			} else {
				MAZE[j][i] = EMPTY_SPACE;
			}
		}
	}
}

void draw_maze()
{
	for (int i = 0; i < NUMCOLS; i++) {
		for (int j = 0; j < NUMROWS; j++) {
			switch (MAZE[j][i]) {
				case WALL:
					draw_character(i, j, WALL);
					break;
				case EMPTY_SPACE:
					draw_character(i, j, EMPTY_SPACE);
					break;
			}
		}
	}
}


// PRE: 0 < x < COLS, 0 < y < ROWS, 0 < use < 255
// POST: Draws character use to the screen and position x,y
// THIS CODE FUNCTIONS FOR PLACING THE AVATAR AS PROVIDED.
//
//    >>>>DO NOT CHANGE THIS FUNCTION.<<<<
void draw_character(int x, int y, char use)
{
	mvaddch(y,x,use);    
	refresh();
}

void move_avatar(int* curX, int* curY, int deltaX, int deltaY) 
{
	// The below line is likely unnecessary because collison will stop
	// the case in which we need to redraw parts of the maze. Just in case I suppose.
	// Erase previous avatar
	draw_character(*curX, *curY, MAZE[*curY][*curX]);
	
	// Is there a wall within range 'deltaX' ?
	int wallThere = 0;
	
	/* I wanted my player to move at varying speeds, so
	 * this is how I implemented collision. Basically it
	 * works by checking ahead a number of spaces equal to
	 * deltaX. If it finds a wall, it sets wallThere to 0
	 * and begins slowly moving the player towards the wall
	 * until it is flush with it. This was the solution I
	 * was most happy with and is actually pretty common in
	 * pixel perfect 2D games.
	 */
	if (deltaX > 1) {
		for (int i = *curX + 1; i <= *curX + deltaX; i++) {
			if (MAZE[*curY][i] == WALL) {
				wallThere = 1;
			}
		}
		
		if (wallThere == 1 && MAZE[*curY][*curX + 1] == EMPTY_SPACE) {
			*curX += 1;
		}
	} else if (deltaX < -1) {
		for (int i = *curX - 1; i >= *curX + deltaX; i--) {
			if (MAZE[*curY][i] == WALL) {
				wallThere = 1;
			}
		}
		
		if (wallThere == 1 && MAZE[*curY][*curX - 1] == EMPTY_SPACE) {
			*curX -= 1;
		}
	} 
	
	// Update X
	if (MAZE[*curY + deltaY][*curX + deltaX] == EMPTY_SPACE && wallThere == 0) {
		*curX += deltaX;
	}
	
	// Can I fall?
	// As long as there is an empty space directly below the avatar,
	// the avatar will be moved downward by deltaY
	// Update Y
	if (MAZE[*curY + deltaY][*curX + deltaX] == EMPTY_SPACE) {
		*curY += deltaY;
	}
	
	// Boundry checking
	if (*curX < 0) {
		*curX = 0;
	} else if (*curX > 99) {
		*curX = 99;
	}
	
	// Place new avatar
	draw_character(*curX, *curY, AVATAR);
}

int stuck(int curX, int curY)
{
	int rWallFound = 0; // Right wall found?
	int lWallFound = 0; // Left wall found?

	if (MAZE[curY + 1][curX] == WALL && MAZE[curY][curX + 1] == WALL && MAZE[curY][curX - 1] == WALL) {
		return 1;
	}
	
	if (MAZE[curY + 1][curX] == EMPTY_SPACE) {
		return 0;
	}


	// We take the current position and go all the way to the right, checking for any gaps.
	// We then do the same thing going to the left. If there are none, the player is stuck,
	// as there is no possible way for the player to go any further down. Game over.
	for (int i = curX + 1; i < 100; i++) {
		if (MAZE[curY][i] == EMPTY_SPACE) {
			if (MAZE[curY + 1][i] == EMPTY_SPACE) {
				break;
			}
		} else {
			rWallFound = 1;
		}
	}

	for (int i = curX - 1; i >= 0; i--) {
		if (MAZE[curY][i] == EMPTY_SPACE) {
			if (MAZE[curY + 1][i] == EMPTY_SPACE) {
				break;
			}
		} else {
			lWallFound = 1;
		}
	}

	if (lWallFound == 1 && rWallFound == 1) {
		return 1;
	}
	
	return 0;
}

int sign(double num)
{
	return (num > 0) - (num < 0);
}

double avg(double buffer[], int numItems)
{
	double temp = 0.0;
	for (int i = 0; i < numItems; i++) {
		temp += buffer[i];
	}

	temp /= numItems;
	return temp;
}

void updateBuffer(double buffer[], int length, int newItem)
{
	for (int i = 0; i < length - 1; i++) {
		buffer[i] = buffer[i + 1];
	}

	buffer[length - 1] = newItem;
}

double roll(double xMag) {
	if (xMag > 1.0)
		xMag = 1.0;
	
	if (xMag < -1.0)
		xMag = -1.0;
	
	return asin(-xMag);
}

int scaleControllerMovement(double rad)
{
	int temp = 0;
	if (rad < (M_PI/15) && rad > -(M_PI/15)) {
		temp = 0;
	} else if (rad < (M_PI / 4) && rad > -(M_PI/4)) {
		temp = sign(rad) * 1;
	} else if (rad < (3 * (M_PI / 7)) && rad > -(3 * (M_PI/7))) {
		temp = sign(rad) * 2;
	} else {
		temp = sign(rad) * 3;
	}
 
	return temp;
}