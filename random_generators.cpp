#include "random_generators.h"
#include <cmath>

// Function to generate a uniform random number between 0 and 1
double generateUniform()
{
    return rand() / (RAND_MAX + 1.0);
}

// Function to generate an exponential random number using the inverse transform method
double generateExponential(double lambda)
{
    double u = generateUniform();  // Uniform random number
    return -log(1.0 - u) / lambda; // Inverse transform method
}

// Function to generate an Erlang random number by summing k exponential random variables
double generateErlang(int k, double lambda)
{
    double sum = 0.0;
    for (int i = 0; i < k; ++i)
    {
        sum += generateExponential(lambda); // Sum of k exponential random variables
    }
    return sum;
}
// Function to generate a normal random number using the Box-Muller transform
double generateNormal(double mean, double stddev)
{
    double u1 = generateUniform();                           // Uniform random number [0, 1)
    double u2 = generateUniform();                           // Uniform random number [0, 1)
    double z0 = sqrt(-2.0 * log(u1)) * cos(2.0 * M_PI * u2); // Box-Muller transform
    return mean + z0 * stddev;                               // Scale to desired mean and standard deviation
}
