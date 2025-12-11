/*-----------------------------------------------------------------------------
-					         SE/CprE 185 Lab 04
-             Developed for 185-Rursch by T.Tran and K.Wang
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
-	                            Includes
-----------------------------------------------------------------------------*/
#include <stdio.h>
#include <math.h>


/*-----------------------------------------------------------------------------
-	                            Defines
-----------------------------------------------------------------------------*/

#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4
#define FRONT 5
#define BACK 6

/*-----------------------------------------------------------------------------
-	                            Prototypes
-----------------------------------------------------------------------------*/
double magnitude(double, double, double);
int closeTo(double, double, double);
int facing(double, double, double, double);
char* stringFacing(int);


/*-----------------------------------------------------------------------------
-							  Implementation
-----------------------------------------------------------------------------*/
int main(void) 
{
    int t;
	int triangle, o, x, square;
	int dir, prevDir;
	
    double ax, ay, az;
	double gx, gy, gz, mag;


    while (triangle != 1) {
        scanf("%d, %lf, %lf, %lf, %lf, %lf, %lf, %d, %d, %d, %d", &t, &ax, &ay, &az, &gx, &gy, &gz, &triangle, &o, &x, &square);
		
		mag = magnitude(ax, ay, az);
		
		/* When I was testing, if I did the magnitude
		 * check at the same time as the same direction
		 * check, the program would never print something
		 * because prevDir would update before magnitude
		 * dropped below 0.1. If we instead do all of our
		 * direction checks inside of the magnitude check
		 * we get our desired behavior.
		 */
		 
		if (mag < 0.1) {
			dir = facing(gx, gy, gz, 0.15); // After testing, 0.2 seems to be a good tolerance value for the accelerometers.
		
			if (dir != prevDir && dir != -1) {
				//printf("a(x, y, z) values: %lf, %lf, %lf with a magnitude of %lf\n", ax, ay, az, mag);
				//printf("g(x, y, z) values: %lf, %lf, %lf with a magnitude of %lf and is facing %s\n", gx, gy, gz, mag, facing(gx, gy, gz, 0.2));
			
				printf("The controller is facing %s\n", stringFacing(dir));
			}

			//printf("At %d ms, the acceleration's magnitude was: %f\n", t, mag(ax, ay, az));
		
			/* We don't set prevDir to dir if dir is -1 because
			* when we check if dir is not equal to prevDir we
			* want to ignore values that we aren't going to
			* print.
			*/
			
			if (dir != -1)
				prevDir = dir;
		}
		
		fflush(stdout);
    }

    return 0;
}

/* Put your functions here */
double magnitude(double x, double y, double z)
{
	return sqrt((x * x) + (y * y) + (z * z));
}

int closeTo(double tolerance, double point, double value) // Determins if point is within value +- tolerance.
{
	if (value + tolerance > point && value - tolerance < point) {
		return 1;
	}
	
	return 0;
}

int facing(double gx, double gy, double gz, double tolerance)
{
	// There are 6 possible directions (in our case) that the controller can face.
	// UP = 1, DOWN = 2, LEFT = 3, RIGHT = 4, FRONT = 5, BACK = 6 (and we have a non-cardinal direction 'error' value of -1)
	// We check if the gravity-affected-accelerometer is within acceptable bounds (1 +- tolerance).
	if (closeTo(tolerance, gy, 1)) {
		return UP;
	}
	else if (closeTo(tolerance, gy, -1)) {
		return DOWN;
	}
	
	if (closeTo(tolerance, gz, 1)) {
		return BACK;
	}
	else if (closeTo(tolerance, gz, -1)) {
		return FRONT;
	}
	
	if (closeTo(tolerance, gx, 1)) {
		return RIGHT;
	}
	else if (closeTo(tolerance, gx, -1)) {
		return LEFT;
	}
	
	return -1;
}

char* stringFacing(int facing) // Converts the integer facing value into a string to be human readable.
{
	switch (facing) {
		case UP:
			return "TOP";
			break;
			
		case DOWN:
			return "BOTTOM";
			break;
			
		case LEFT:
			return "LEFT";
			break;
			
		case RIGHT:
			return "RIGHT";
			break;
			
		case FRONT:
			return "FRONT";
			break;
			
		case BACK:
			return "BACK";
			break;
			
		default:
			return "Non Cardinal Direction";
			break;
	}
}