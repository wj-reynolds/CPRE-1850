#include <math.h>
#include <stdio.h>

double magnitude(double, double, double);
double metersFallen(int time);
void printCharacter(char, int, int, int*);

int main(void) 
{
	
	int time;
	double gx, gy, gz;
	
	while (1) {
		scanf("%d, %lf, %lf, %lf", &time, &gx, &gy, &gz);
		
		printf("%d,%lf\n", time, magnitude(gx, gy, gz));
	}
	
	return 0;
}

double magnitude(double x, double y, double z) 
{
	return sqrt(x * x + y * y + z * z);
}

double metersFallen(int time)
{
	int x = 0.5 * 9.81 * time * time;
	return x;
}

void printCharacter(char character, int time, int k, int* printed) 
{
	/* 30 here acts like a tolerance because the controller often
	 * skips milliseconds, meaning we cannot just check if this
	 * expression is equal to 0.
	 */
	if (time % k < 30 && *printed == 0) {
		printf("%c", character);
		*printed = 1;
	}
		
	/* We check if we have gone over the previous tolerance so that
	 * we can set printed back to 0. This ensure that we won't printed
	 * more than one time per value k, and that we will print every
	 * value k milliseconds.
	 */
	if (time % k > 50 && *printed == 1) {
		*printed = 0;
	}
}