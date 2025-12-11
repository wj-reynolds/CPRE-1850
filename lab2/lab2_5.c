/*-----------------------------------------------------------------------------
-					          CPRE 185 Lab 02
-	Name:
- 	Section:
-	NetID:
-	Date:
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
-	                            Includes
-----------------------------------------------------------------------------*/
#include <stdio.h>
#include <math.h>


/*-----------------------------------------------------------------------------
-	                            Defines
-----------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
-	                            Prototypes
-----------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
-							 Implementation
-----------------------------------------------------------------------------*/
int main(void)
{
    double a, b, c;
    double filler;
    /* Put your code after this line */
	
	printf("Pythagorean Theorem:\n");
	printf("Enter your 'a' value: ");
	scanf("%lf", &a);
	printf("Enter your 'b' value: ");
	scanf("%lf", &b);
	
	c = (a * a) + (b * b);

    /*  This next line will calculate the square root of whatever value is
        inside the parenthesis and assigns it to the variable filler. */
    filler = sqrt(c);
	
	printf("A right triangle with side lengths %.2lf and %.2lf\n has a hypotenuse of %.2lf\n", a, b, filler);


    return 0;
}

