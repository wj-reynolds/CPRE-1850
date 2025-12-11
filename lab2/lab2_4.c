#include <stdio.h>
#include <math.h>

int main(void)
{
	// Arithmetic Operations
	int a = 6427 + 1725;
	int b = (6971 * 3925) - 95;
	double c = 79 + 12 / 5;
	double d = 3640.0 / 107.9;
	int e = (22 / 3) * 3;
	int f = 22 / (3 * 3);
	double g = 22 / (3 * 3);
	double h = 22 / 3 * 3;
	double i = (22.0 / 3) * 3.0;
	int j = 22.0 / (3 * 3.0);
	double k = 22.0 / 3.0 * 3.0;
	
	printf("a: 6427 + 1725 is %d\n", a);
	printf("b: 6971 * 3925 - 95 is %d\n", b);
	printf("c: 79 + 12 / 5 is %.2lf\n", c);
	printf("d: 3640 / 107.9 is %.2lf\n", d);
	printf("e: (22 / 3) * 3 is %d\n", e);
	printf("f: 22 / (3 * 3) is %d\n", f);
	printf("g: 22 / (3 * 3) is %.2lf\n", g);
	printf("h: 22 / 3 * 3 is %.2lf\n", h);
	printf("i: (22 / 3) * 3 is %.2lf\n", i);
	printf("j: 22 / (3 * 3) is %d\n", j);
	printf("k: 22 / 3 * 3 is %.2lf\n\n", k);
	
	
	// Area of a Circle based on Circumference
	double circum = 23.567;
	double radius = circum / (2 * M_PI);
	double area = M_PI * (radius * radius);
	printf("The area of a circle with a circumference of %.2lf is %.2lf\n", circum, area); 
	
	// Convert feet to meters
	double feet = 14;
	double meters = feet / 3.2808399;
	printf("14 feet is about %.2lf meters\n", meters);
	
	// Convert fahrenheit to centigrade
	double degF = 76;
	double degC = (degF - 32) / 1.8;
	printf("76 degrees fahrenheit is equal to %.2lf degrees centigrade\n", degF, degC);
	
	return 0;
}
