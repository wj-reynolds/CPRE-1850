/* 185 Lab 3 Template */

#include <stdio.h>
#include <math.h>

/* Put your function prototypes here */
int numButtonsPressed(int, int, int, int);

int main(void) 
{
    /* DO NOT MODIFY THESE VARIABLE DECLARATIONS */
    // int t = 55000;
    // double  ax, ay, az;  
	int triangle, o, x, square;


    /* This while loop makes your code repeat. Don't get rid of it. */
    while (1) {
		scanf("%d,%d,%d,%d", &triangle, &o, &x, &square);
		
		printf("The number of buttons pressed is:  %d\n", 
			numButtonsPressed(triangle, o, x, square));
		fflush(stdout);
    }

return 0;
}

/* Put your functions here */
int numButtonsPressed(int triangle, int o, int x, int square)
{
	return triangle + o + x + square;
}
