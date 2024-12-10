#include <stdio.h>
#include <math.h>
#include <time.h>

/////////////////////////////////////////////////////////////////////////////////////////////////
/*  This program computes an integral numerically using the Chebyshev-Gauss Method.
 
    User Inputs:     a (lower boundary), b (upper boundary)
    Outputs:         integral (numerical value of integral), time (program runtime), accuracy 
    Compiler flags:  gcc -Wall chebG.c -o chebG -lm
  
    Program authors: Christian Quiroz, Ian Ravenscroft                                         */
/////////////////////////////////////////////////////////////////////////////////////////////////



// Define function to be integrated
double f_x ( double x )
{
    return (3*x*x);
}

// Define function that performs chebyshev-gauss method integration
double chebG (int n, int flag)
{
    double x_i, w_i, sum, pi = 3.14159265359;
    int i;

    sum = 0;
 
    if (flag == 0)
    {
        for(i = 0; i <= n; i++)
        {   
             x_i = cos( pi * (2*i - 1) / (2*n));
             w_i = (pi/n);
             sum = sum + w_i*f_x( x_i );
        }
    }
    else if (flag == 1)
    {
        for(i=0; i <= n; i++)
        {
             x_i = cos( (pi*i) / (n+1) );
             w_i = (pi/(n+1)) * (sin((i*pi) / (n+1)) * sin((i*pi) / (n+1)));
             sum = sum + w_i*f_x( x_i );
        }
    }

    return sum;
}


//////////////////////////////////////////////////////////////////////////////////////////////////
/*                            Main program begins                                               */
//////////////////////////////////////////////////////////////////////////////////////////////////


int main()
{
    int n, flag;
    double integral, trueVal, error;

    // Request user input for values flag and n
    printf("\n Case 0: f(x)*(1-x^2)^(-1/2) || Case 1: f(x)*(1-x^2)^(1/2) \n \n");
    printf("The function f above is f(x) = 3x^2 on the interval [-1,1] \n \n");

    printf("Enter 0 for case 0, 1 for case 1: \n");
    scanf("%i", &flag);

    if (flag == 0)
    {
        trueVal = (3*M_PI)/2;
    }
    else
    {
        trueVal = (3*M_PI)/8;
    }


    clock_t tic = clock(); // Start clock timer

    // Print table headings
    printf("\n|| n || Numerical value ||  Actual Value || Percent Error ||\n\n");

    // Begin numerical integration
    for (n = 10; n <= 1010; n += 25)
    {

         integral = chebG(n, flag);  // Numerical integral value for each n
         error = 100 * fabs((integral - trueVal) / (trueVal));  // Error calculation

         printf("|| %i ||  %.4f      ||  %.4f      ||  %.4f      ||\n", n, integral, trueVal, error);

    }
    clock_t toc = clock(); // End clock timer
    printf("\nComputation time: %f seconds \n\n", (double)(toc-tic) / CLOCKS_PER_SEC);

    return 0;
}
