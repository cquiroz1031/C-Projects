#include <stdio.h>
#include <math.h>
#include <time.h>

/////////////////////////////////////////////////////////////////////////////////////////////////
/*  This program computes an integral numerically using the Gauss-Hermite Method.
 
    User Inputs:     none
    Outputs:         integral (numerical value of integral), time (program runtime), accuracy 
    Compiler flags:  gcc -Wall gaussH.c -o gaussH -lm
  
    Program authors: Christian Quiroz, Ian Ravenscroft                                         */
/////////////////////////////////////////////////////////////////////////////////////////////////



// Define function to be integrated
double f_x ( double x )
{
    return (3*x*x);
}

// Factorial function
double factorial(int n)
{
    int i;
    double fact;
    for (i = 1; i <= n; i++)
    {
        fact = fact*i;
    }
    return fact;
}


// Define function that performs gauss hermite method integration
double gaussherm ()
{

    double sum, x = 0, w[5];
    double x_i[5] = {0, 0.7071, 1.2247, 1.65068, 2.02018};
    int i, n = 4;
    double herm[6] = {1,2*x,4*x*x-2,8*x*x*x-12*x,16*x*x*x*x-48*x*x+12,32*x*x*x*x*x-160*x*x*x+120*x};
    sum = 0;
    for(i = 1; i <= n; i++)
    {
        x = x_i[i];
        w[i] = (pow(2,i-1) * factorial(i) * sqrt(M_PI)) / (i*i * herm[i-1]*herm[i-1]);
        sum = sum + w[i]*f_x(x);
    }

    return sum;
}


//////////////////////////////////////////////////////////////////////////////////////////////////
/*                            Main program begins                                               */
//////////////////////////////////////////////////////////////////////////////////////////////////


int main()
{
    double integral, trueVal, error;

    // Request user input for values a, b, and n
    printf("\nThe function to be integrated is exp(-x^2)*f(x)\n");
    printf("where f(x) = 3x^2\n");

    clock_t tic = clock(); // Start clock timer
    trueVal = 7.205461024; // True integral value to be used in error calculation

    // Print table headings
    printf("\n|| n || Numerical value ||  Actual Value || Percent Error ||\n");

    // Begin numerical integration

        integral = gaussherm();  // Numerical integral value for each n
        error = 100 * fabs((integral - trueVal) / (trueVal));  // Error calculation

         printf("|| %i ||  %.4f            ||  %.4f       ||  %.4f          ||\n", 5, integral, trueVal, error);
    clock_t toc = clock(); // End clock timer
    printf("\nComputation time: %f seconds \n\n", (double)(toc-tic) / CLOCKS_PER_SEC);

    return 0;
}