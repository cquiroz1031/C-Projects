/*
 ============================================================================
 Name        : Booles.c
 Authors     : Ian Ravenscroft, Christian Quiroz
 Description : Implementation of Boole's Rule for third degree polynomial
 ============================================================================
 */

#include <stdio.h>
#include <math.h>
#include <time.h>

////Function to integrate: 3x^2 + 4x - 5
double f(double x)
{
	return (3*x*x + 4*x - 5);
}

// Antiderivative 
double Ff_x (double x)
{
    return (x*x*x +2*x*x - 5*x);
}

double boolesRule(double a, double b, int n)
{
	double h = (b-a)/n; //
	double sum;

	if (n == 4)
		sum = 7*f(a) + 32*f(a + h) + 12*f(a + 2*h) + 32*f(a + 3*h) + 7*f(b);

	//Composite Boole's Rule for n > 4
	else {
		int i;
		sum = 7 * (f(a) + f(b));
		for (i = 1; i <= n - 1; i += 2)
			sum += 32*f(a + i*h);

		for (i = 2; i <= n - 2; i += 4)
			sum += 12*f(a + i*h);

		for (i = 4; i <= n - 4; i += 4)
			sum += 14*f(a + i*h);

	}

	sum *= 2 * h / 45;

	return sum;

}

int main(void) {

	  double a, b, integral, trueVal, error; //Initialize end points
	  int n;

	  setbuf(stdout, NULL);
	  printf("Enter value for start of interval:\n"); //Get 1st integer from user
	  scanf("%lf", &a);

	  printf("Enter value for end of interval:\n"); //Get 2st integer from user
	  scanf("%lf", &b);
	  trueVal = Ff_x(b) - Ff_x(a);

	  clock_t tic = clock(); // Start clock timer

	  // Begin numerical integration
      for (n = 4; n <= 1004; n += 50)
      {

          integral = boolesRule(a, b, n);  // Numerical integral value for each n
          error = 100 * fabs((integral - trueVal) / (trueVal));  // Error calculation

        printf("|| %i ||  %.4f      ||  %.4f      ||  %.4f      ||\n", n, integral, trueVal, error);

    }
    clock_t toc = clock(); // End clock timer
    printf("\nComputation time: %f seconds \n\n", (double)(toc-tic) / CLOCKS_PER_SEC);

	return 0;
}