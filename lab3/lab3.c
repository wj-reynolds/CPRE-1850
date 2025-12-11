/* 185 Lab 3 Template */

#include <stdio.h>
#include <math.h>

/* Put your function prototypes here */

double mag(double, double, double);

int minutes(double);
int seconds(double);
int millis(double);

int main(void) 
{
    /* DO NOT MODIFY THESE VARIABLE DECLARATIONS */
    int t = 55000;
    double  ax, ay, az;     


    /* This while loop makes your code repeat. Don't get rid of it. */
    while (1) {
        scanf("%d,%lf,%lf,%lf", &t, &ax, &ay, &az); 

		/* CODE SECTION 0 */
        // printf("%8.3lf, %.4lf, %.4lf, %.4lf\n", (t / 1000.0), ax, ay, az);

		/* CODE SECTION 1 */
        // printf("At %d ms, the acceleration's magnitude was: %lf\n", t, mag(ax, ay, az));
            
		/* CODE SECTION 2 */
        printf("At %d minutes, %d seconds, and %d milliseconds it was: %lf\n", 
			minutes(t), seconds(t), millis(t), mag(ax,ay,az));
    }

return 0;
}

/* Put your functions here */
double mag(double x, double y, double z)
{
	return sqrt((x * x) + (y * y) + (z * z));
}

int minutes (double t)
{
	t /= 1000; // Milliseconds to seconds
	t /= 60; // Seconds to minutes
	return (int) t;
}

int seconds (double t)
{
	t /= 1000; // Milliseconds to seconds
	t = (int) t % 60; // Get rid of the excess seconds
	return (int) t;
}

int millis(double t)
{
	t = (int) t % 1000; // Get rid of the excess milliseconds
	return (int) t;
}
