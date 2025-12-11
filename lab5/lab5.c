#include <math.h>
#include <stdio.h>

double magnitude(double, double, double);
double findVelocity(double, double, double);
double mFallResistance(double, double, double);
double metersFallen(double);
void printCharacter(char, int, int, int*);

int main(void) 
{
	printf("Wesley Reynolds\n");
	printf("wesley06@iastate.edu\n\n");
	
	int prevTime, time, k; // in milliseconds
	int startTime;
	int endTime;
    double totalTime;
	
	int falling = 0; // Are we falling?
	int printed = 0; // Have we printed?
	
	double gx, gy, gz, mag;
	double vel;
	double fallen;
	
	k = 700; // Every k milliseconds, we should output a period or exclamation mark.
	
	scanf("%d, %lf, %lf, %lf", &time, &gx, &gy, &gz);
	if (time != 0) {
		printf("Ok, I'm now receiving data\n");
		printf("I'm Waiting ");
	}
	
	while (falling == 0) {
		scanf("%d, %lf, %lf, %lf", &time, &gx, &gy, &gz);
		
		mag = magnitude(gx, gy, gz);
		
		printCharacter('.', time, k, &printed);
		
		if (mag < 0.1) {
			falling = 1;
			printf("\n\n");
		}
		
		fflush(stdout);
	}
	
	printed = 0;
	
	printf("      Help me! I'm falling");
	
	fallen = 0.0;
	vel = 0.0;
	startTime = time; // Begin timer
	prevTime = time; // Separate our time into blocks for the purpose of findVelocity()
	
	while (falling == 1) {
		mag = magnitude(gx, gy, gz);
		vel = findVelocity(((time - prevTime) / 1000.0), mag, vel);
		fallen = mFallResistance(((time - prevTime) / 1000.0), vel, fallen);
		
		printCharacter('!', time, k, &printed);
		
		if (mag > 3.0) {
			falling = 0;
			endTime = time; // End timer
			printf("\n\n");
		}
		
		prevTime = time;
		scanf("%d, %lf, %lf, %lf", &time, &gx, &gy, &gz);
		fflush(stdout);
	}
	
	totalTime = (endTime - startTime) / 1000.0;
	
	printf("            ");
	printf("Ouch! I fell %.3lf meters in %.3lf seconds.\n", metersFallen(totalTime) , totalTime);

	
	printf("\nCompensating for air resistance, the fall was %.3lf meters.\n", fallen);

	double percent = fallen / metersFallen(totalTime);
	percent = 100 * (1.0 - percent);

	printf("This is %.0lf%% less than computed before.", percent);
	
	
	return 0;
}

double magnitude(double x, double y, double z) 
{
	return sqrt(x * x + y * y + z * z);
}

// Essentially a rieman sum of the velocity values, to find position.
double findVelocity(double time, double magnitude, double initialV) 
{
	double v = initialV + 9.81 * (1 - magnitude) * time;
	return v;
}

// Meters fallen while calcuating in air resistance.
double mFallResistance(double time, double velocity, double initialX)
{
	double x = initialX + (velocity * time);
	return x;
}

double metersFallen(double time)
{
	double x = 0.5 * 9.81 * (time * time);
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