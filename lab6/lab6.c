// 185 lab6.c
//
// This is the outline for your program
// Please implement the functions given by the prototypes below and
// complete the main function to make the program complete.
// You must implement the functions which are prototyped below exactly
//  as they are requested.

#include <stdio.h>
#include <math.h>
#define PI 3.141592653589

//NO GLOBAL VARIABLES ALLOWED


//PRE: Arguments must point to double variables or int variables as appropriate
//This function scans a line of DS4 data, and returns
//  True when the square button is pressed
//  False Otherwise
//This function is the ONLY place scanf is allowed to be used
//POST: it modifies its arguments to return values read from the input line.
int read_line(double* g_x, double* g_y, double* g_z, int* time, int* Button_T, int* Button_X, int* Button_S, int* Button_C);

// PRE: -1.0 <= x_mag <= 1.0
// This function computes the roll of the DS4 in radians
// if x_mag outside of -1 to 1, treat it as if it were -1 or 1
// POST: -PI/2 <= return value <= PI/2
double roll(double x_mag);

// PRE: -1.0 <= y_mag <= 1.0
// This function computes the pitch of the DS4 in radians
// if y_mag outside of -1 to 1, treat it as if it were -1 or 1
// POST: -PI/2 <= return value <= PI/2
double pitch(double y_mag);


// PRE: -PI/2 <= rad <= PI/2
// This function scales the roll value to fit on the screen
// POST: -39 <= return value <= 39
int scaleRadsForScreen(double rad);

// PRE: num >= 0
// This function prints the character use to the screen num times
// This function is the ONLY place printf is allowed to be used
// POST: nothing is returned, but use has been printed num times
void print_chars(int num, char use);

//PRE: -39 <= number <=39
// Uses print_chars to graph a number from -39 to 39 on the screen.
// You may assume that the screen is 80 characters wide.
void graph_line(int number);

int main()
{
	double x, y, z;                             // magnitude values of x, y, and z
	int b_Triangle, b_X, b_Square, b_Circle;    // variables to hold the button statuses
	double roll_rad, pitch_rad;                 // value of the roll measured in radians
	int scaled_value;                           // value of the roll adjusted to fit screen display

	int time;
	int prevPressed = 0;						// I am using this to ensure that the button doesn't double press
	int state = 0;								// reading roll (0) or pitch (1)

	do
	{
		// Get line of input
		read_line(&x, &y, &z, &time, &b_Triangle, &b_X, &b_Square, &b_Circle);

		// calculate roll and pitch.  Use the buttons to set the condition for roll and pitch
		
		roll_rad = roll(x);
		pitch_rad = pitch(z);
		
		// printf("Roll: %2.4lf\n", roll(x));
		// printf("Pitch: %2.4lf\n", pitch(z));
		// printf("Screen Coord (r - p) %2d  -  %2d\n", scaleRadsForScreen(roll(x)), scaleRadsForScreen(pitch(z)));

		// switch between roll and pitch(up vs. down button)
		if (b_Circle == 1 && prevPressed == 0) {
			prevPressed = 1;
			
			switch (state) {
				case 0:
					state = 1;
					break;
				case 1:
					state = 0;
					break;
				default:
					printf("We shouldn't be here!!!\n");
					return -1;
			}
		} else if (b_Circle == 0) {
			prevPressed = 0;
		}

		// Scale your output value
		
		if (state == 0) {
			scaled_value = scaleRadsForScreen(roll_rad);
			//printf("Scaled Roll: %3d\n", scaled_value);
			
			graph_line(scaled_value);
		}
		
		if (state == 1) {
			scaled_value = scaleRadsForScreen(pitch_rad);
			//printf("Scaled Pitch: %3d\n", scaled_value);
			
			graph_line(scaled_value);
		}

		// Output your graph line
		
		fflush(stdout);
	} while (b_Square != 1); // Modify to stop when the square button is pressed
	
	return 0;
}

int read_line(double* g_x, double* g_y, double* g_z, int* time, int* Button_T, int* Button_X, int* Button_S, int* Button_C)
{
	scanf("%d, %lf, %lf, %lf, %d, %d, %d, %d", time, g_x, g_y, g_z, Button_T, Button_C, Button_X, Button_S);
	
	if (*Button_S == 1)
		return 1;
	
	return 0;
}

double roll(double x_mag)
{
	if (x_mag > 1)
		x_mag = 1.0;
	
	if (x_mag < -1)
		x_mag = -1.0;
	
	return asin(x_mag);
}

double pitch(double y_mag)
{
	if (y_mag > 1)
		y_mag = 1.0;
	
	if (y_mag < -1)
		y_mag = -1.0;
	
	return asin(y_mag);
}

int scaleRadsForScreen(double rad)
{
	// Alleviate some of the noise
	if ((rad < 0.03 && rad > 0) || (rad > -0.03 && rad < 0))
		rad = 0;
	
	rad = rad / (PI / 2);
	rad *= 39;
	return rad;
}

void print_chars(int num, char use)
{
	for (int i = 0; i < num; ++i) {
		printf("%c", use);
	}
}

void graph_line(int number)
{	
	if (number == 0) {
		print_chars(39 - number, ' ');
		print_chars(1, '0');
	}
	
	if (number < 0) {
		print_chars(39, ' ');
		print_chars(number * -1, 'r'); // Multiply by negative one because number is negative here.
	}
	
	if (number > 0) {
		print_chars(39 - number, ' ');
		print_chars(number, 'l');
	}
	
	print_chars(1, '\n');
}