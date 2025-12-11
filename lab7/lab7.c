// 185 Lab 7
#include <stdio.h>


#define MAXPOINTS 10000

// compute the average of the first num_items of buffer
double avg(double buffer[], int num_items);

//update the max and min of the first num_items of array
void maxmin(double array[], int num_items, double* max, double* min);

//shift length-1 elements of the buffer to the left and put the 
//new_item on the right.
void updatebuffer(double buffer[], int length, double new_item);



int main(int argc, char* argv[]) 
{
	/* DO NOT CHANGE THIS PART OF THE CODE */

	double x[MAXPOINTS], y[MAXPOINTS], z[MAXPOINTS];
	int lengthofavg = 0;
	if (argc>1) {
		sscanf(argv[1], "%d", &lengthofavg );
		printf("You entered a buffer length of %d\n", lengthofavg);
	}
	else {
		printf("Enter a length on the command line\n");
		return -1;
	}
	if (lengthofavg <1 || lengthofavg >MAXPOINTS) {
		printf("Invalid length\n");
		return -1;
	}


	
	/* PUT YOUR CODE HERE */
	double gx, gy, gz;
	double agx, agy, agz; // Average g_
	double xmax, xmin, ymax, ymin, zmax, zmin;
	int triangle, oButton, xButton, square;
	int time;
	
	printf("Format: \n");
	printf("time, gx, agx, xmin, xmax, gy, agy, ymin, ymax, gz, agz, zmin, zmax\n");
	fflush(stdout);

	// Necessary to first fill the arrays so we can start taking averages
	for (int i = 0; i < lengthofavg; i++) {
		scanf("%d, %lf, %lf, %lf, %d, %d, %d, %d", &time, &gx, &gy, &gz, &triangle, &oButton, &xButton, &square);
		updatebuffer(x, lengthofavg, gx);
		updatebuffer(y, lengthofavg, gy);
		updatebuffer(z, lengthofavg, gz);
	}

	do {
		scanf("%d, %lf, %lf, %lf, %d, %d, %d, %d", &time, &gx, &gy, &gz, &triangle, &oButton, &xButton, &square);

		agx = avg(x, lengthofavg);
		agy = avg(y, lengthofavg);
		agz = avg(z, lengthofavg);

		maxmin(x, lengthofavg, &xmax, &xmin);
		maxmin(y, lengthofavg, &ymax, &ymin);
		maxmin(z, lengthofavg, &zmax, &zmin);

		printf("%d,   %+2.3lf, %+2.3lf, %+2.3lf, %+2.3lf,   ", time, gx, agx, xmin, xmax);
		printf("%+2.3lf, %+2.3lf, %+2.3lf, %+2.3lf,   ", gy, agy, ymin, ymax);
		printf("%+2.3lf, %+2.3lf, %+2.3lf, %+2.3lf\n", gz, agz, zmin, zmax);

		updatebuffer(x, lengthofavg, gx);
		updatebuffer(y, lengthofavg, gy);
		updatebuffer(z, lengthofavg, gz);
		fflush(stdout);
	} while (square != 1);


	// accelerometers, averages, maximums, minimums

	return 0;
}

double avg(double buffer[], int num_items)
{
	double temp = 0.0;
	for (int i = 0; i < num_items; i++) {
		temp += buffer[i];
	}

	temp /= num_items;
	return temp;
}

void maxmin(double array[], int num_items, double* max, double* min)
{
	*max = 0.0;
	*min = 100.0; // Setting to a very high value in the case that there are no values below 0.

	for (int i = 0; i < num_items; i++) {
		if (array[i] > *max) {
			*max = array[i];
		}

		if (array[i] < *min) {
			*min = array[i];
		}
	}
}

void updatebuffer(double buffer[], int length, double new_item)
{
	for (int i = 0; i < length - 1; i++) {
		buffer[i] = buffer[i + 1];
	}

	buffer[length - 1] = new_item;
}