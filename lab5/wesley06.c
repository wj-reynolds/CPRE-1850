#include <math.h>
#include <stdio.h>

double magnitude(double, double, double);
//double findVelocity(double, double);
//double mFallResistance(double, double);
double metersFallen(double);
void printCharacter(char, int, int, int*);

int main(void) 
{
	printf("Wesley Reynolds\n");
	printf("wesley06@iastate.edu\n\n");
	
	// int prevTime;
	int time, k; // in milliseconds
	int startTime;
	int endTime;
    double totalTime;
	
	int falling = 0; // Are we falling?
	int printed = 0; // Have we printed?
	
	double gx, gy, gz, mag;
	//double vel;
	// double fallen;
	
	k = 700; // Every k milliseconds, we should output a period or exclamation mark.
	
	scanf("%d, %lf, %lf, %lf", &time, &gx, &gy, &gz);
	if (time != 0) {
		printf("Ok, I'm now receiving data\n");
		printf("I'm Waiting ");
	}
	
	while (falling == 0) {
		scanf("%d, %lf, %lf, %lf", &time, &gx, &gy, &gz);
		
		mag = magnitude(gx, gy, gz);
		
		// printf("%d\n", time % 1000);
		// printf("%.3lf\n", mag);
		
		printCharacter('.', time, k, &printed);
		
		if (mag < 0.1) { // TODO: Refine the falling tolerance
			falling = 1;
			printf("\n\n");
		}
		
		fflush(stdout);
	}
	
	printed = 0;
	
	printf("      Help me! I'm falling");
	
	//velocity = 0;
	startTime = time; // Begin timer
	//prevTime = time;
	while (falling == 1) {
		mag = magnitude(gx, gy, gz);
		//vel = findVelocity((time - prevTime), magnitude(gx, gy, gz), vel);
		//fallen = mFallResistance((time - prevTime), vel, fallen);
		
		printCharacter('!', time, k, &printed);
		
		if (mag > 3.0) { // TODO: Refine the stop falling tolerance
			falling = 0;
			endTime = time; // End timer
			printf("\n\n");
		}
		
		scanf("%d, %lf, %lf, %lf", &time, &gx, &gy, &gz);
		// prevTime = time;
		fflush(stdout);
	}
	
	totalTime = (endTime - startTime) / 1000.0;
	
	printf("            ");
	printf("Ouch! I fell %.3lf meters in %.3lf seconds.\n", metersFallen(totalTime) , totalTime);

	/*
	printf("Compensating for air resistance, the fall was $.3lf meters.\n", mFallResistance(totalTime, velocity));

	double percent = mFallResistance(totalTime, velocity) / metersFallen(totalTime);
	percent = (1 - percent);

	printf("This is %.0lf% less than computed before.", percent);
	*/
	
	return 0;
}

double magnitude(double x, double y, double z) 
{
	return sqrt(x * x + y * y + z * z);
}

/*
double findVelocity(double time, double magnitude, double initialV) 
{
	double v = initialV + 9.81 * (1 - magnitude) * time;
	initialV = v;
	return v;
}

// Meters fallen while calcuating in air resistance.
double mFallResistance(double time, double velocity, double initialX)
{
	double x = initalX + (velocity * time);
	initialX = x;
	return x;
}*/

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