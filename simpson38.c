#include <stdio.h>
#include <math.h>
#include <time.h>

/////////////////////////////////////////////////////////////////////////////////////////////////
/*  This program computes an integral numerically using the Simpson 3/8 Method.
 
    User Inputs:     a (lower boundary), b (upper boundary)
    Outputs:         integral (numerical value of integral), time (program runtime), accuracy 
    Compiler flags:  gcc -Wall simpson38.c -o simpson38 -lm
  
    Program authors: Christian Quiroz, Ian Ravenscroft                                         */
/////////////////////////////////////////////////////////////////////////////////////////////////



// Define function to be integrated //
double f_x ( double x )
{
    return (3*x*x + 4*x - 5);
}

// Define the above function's antiderivative for computing the error //
double Ff_x (double x)
{
    return (x*x*x + 2*x*x - 5*x);
}

// Define function that performs simpson 3/8 method integration //
double simp38 ( double a, double b, int n)
{
    double x_i, h, sum, intgrl;
    int i;

    sum = 0;
    h = (b-a)/n;
    for(i = 0; i <= n; i++)
    {
        x_i = a + i*h;
        if(i%3 == 0)
        {
            sum = sum + 2*f_x(x_i);
        }
        else
        {
            sum = sum + 3*f_x(x_i);
        }
    }

    intgrl = (3*h/8) * (sum + f_x(a) + f_x(b));

    return intgrl;
}


//////////////////////////////////////////////////////////////////////////////////////////////////
/*                            Main program begins                                               */
//////////////////////////////////////////////////////////////////////////////////////////////////


int main()
{
    int a, b, n;
    double integral, trueVal, error;

    // Request user input for values a, b, and n
    printf("\nThe function to be integrated is f(x) = 3x^2 + 4x - 5 \n \n");
    printf("Enter integer values a and b for interval [a,b]: \n");
    scanf("%i %i", &a, &b);

    clock_t tic = clock(); // Start clock timer
    trueVal = Ff_x(b) - Ff_x(a); // Compute true integral value to be used in error calculation

    // Print table headings
    printf("\n|| n || Numerical value ||  Actual Value ||  Percent Error  ||\n\n");

    // Begin numerical integration
    for (n = 10; n <= 1010; n += 25)
    {

        integral = simp38(a, b, n);  // Numerical integral value for each n
        error = 100 * fabs((integral - trueVal) / (trueVal));  // Error calculation

        printf("|| %i ||  %.4f      ||  %.4f      ||  %.4f      ||\n", n, integral, trueVal, error);

    }
    clock_t toc = clock(); // End clock timer
    printf("\nComputation time: %f seconds \n\n", (double)(toc-tic) / CLOCKS_PER_SEC);

    return 0;
}
