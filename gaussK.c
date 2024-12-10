#include <stdio.h>
#include <math.h>
#include <time.h>

/////////////////////////////////////////////////////////////////////////////////////////////////
/*  This program computes an integral numerically using the Gauss-Kronrod Method.
 
    User Inputs:     a (lower boundary), b (upper boundary)
    Outputs:         integral (numerical value of integral), time (program runtime), accuracy 
    Compiler flags:  gcc -Wall gaussK.c -o gaussK -lm
  
    Program authors: Christian Quiroz, Ian Ravenscroft                                         */
/////////////////////////////////////////////////////////////////////////////////////////////////



// Define function to be integrated
double f_x ( double x )
{
    return (3*x*x + 4*x - 5);
}

// Define the above function's antiderivative for computing the error
double Ff_x (double x)
{
    return (x*x*x + 2*x*x - 5*x);
}

// Define function that performs gauss kronrod method integration
double gausskron ( double a, double b, int n)
{
    double x_i, w_i, sum;
    int i;

    sum = 0;
    x_i = 0;
    w_i = 1;
    for(i = 0; i <= n; i++)
    {
        x_i = a + (b-a)*(x_i + 1)/2;
        w_i = w_i * ((b-a)/2);
        sum = sum + w_i*f_x(x_i);
    }

    return sum;
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
    printf("\n|| n || Numerical value ||  Actual Value || Percent Error ||\n\n");

    // Begin numerical integration
    for (n = 10; n <= 1010; n += 25)
    {

        integral = gausskron(a, b, n);  // Numerical integral value for each n
        error = 100 * fabs((integral - trueVal) / (trueVal));  // Error calculation

         printf("|| %i ||  %.4f      ||  %.4f      ||  %.4f      ||\n", n, integral, trueVal, error);

    }
    clock_t toc = clock(); // End clock timer
    printf("\nComputation time: %f seconds \n\n", (double)(toc-tic) / CLOCKS_PER_SEC);

    return 0;
}

