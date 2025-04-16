#include "random_generators.h"
#include <cmath>
#include <cstdlib>
#include <ctime>

// Function to generate a uniform random number between 0 and 1
double generateUniform()
{
    return rand() / (RAND_MAX + 1.0);
}

// Function to generate an exponential random number using the inverse transform method
double functionI1() // Expon 1.4
{
    double u = generateUniform(); // Uniform random number
    return -log(1.0 - u) / 1.4;   // Inverse transform method
}

// Function to generate an Erlang random number by summing k exponential random variables
double functionI2() // Erlang k=3, lambda = 7.0
{
    double sum = 0.0;
    for (int i = 0; i < 3; ++i)
    {
        sum += -log(1.0 - generateUniform()) / 7.0; // Sum of k exponential random variables
    }
    return sum;
}
// Function to generate a normal random number using the Box-Muller transform
double functionP1() // Normal mean = 1, stdev = 0.2
{
    double u1 = generateUniform();                           // Uniform random number [0, 1)
    double u2 = generateUniform();                           // Uniform random number [0, 1)
    double z0 = sqrt(-2.0 * log(u1)) * cos(2.0 * M_PI * u2); // Box-Muller transform
    return 1.0 + z0 * 0.2;                                   // Scale to desired mean and standard deviation
}

double functionP2() // Erlang k=2, lambda = 1.0
{
    double sum = 0.0;
    for (int i = 0; i < 2; ++i)
    {
        sum += -log(1.0 - generateUniform()); // Sum of k exponential random variables
    }
    return sum;
}
