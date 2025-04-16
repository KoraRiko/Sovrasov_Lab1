#include <iostream>
#include <vector>
#include "random_generators.h"
#include "file.h"

void Exponential()
{
    double lambdaExp = 1.4;  // Rate parameter for the exponential distribution
    int numSamplesExp = 500; // Number of random numbers to generate
    std::vector<double> expSamples;

    for (int i = 0; i < numSamplesExp; ++i)
    {
        double sample = generateExponential(lambdaExp);
        expSamples.push_back(sample);
    }

    writeSamplesToFile(expSamples, "exponential_samples.txt");
    std::cout << "Generated " << numSamplesExp << " exponential random numbers and saved to 'exponential_samples.txt'.\n";
}

void Erlang()
{
    int k = 3;                  // Shape parameter for the Erlang distribution
    double lambdaErlang = 7.0;  // Rate parameter for the Erlang distribution
    int numSamplesErlang = 500; // Number of random numbers to generate
    std::vector<double> erlangSamples;

    for (int i = 0; i < numSamplesErlang; ++i)
    {
        double sample = generateErlang(k, lambdaErlang);
        erlangSamples.push_back(sample);
    }

    writeSamplesToFile(erlangSamples, "erlang_samples.txt");
    std::cout << "Generated " << numSamplesErlang << " Erlang random numbers and saved to 'erlang_samples.txt'.\n";
}

void Normal()
{
    double mean = 1.0;          // Mean of the normal distribution
    double stddev = 0.2;        // Standard deviation of the normal distribution
    int numSamplesNormal = 500; // Number of random numbers to generate
    std::vector<double> normalSamples;

    for (int i = 0; i < numSamplesNormal; ++i)
    {
        double sample = generateNormal(mean, stddev);
        normalSamples.push_back(sample);
    }

    writeSamplesToFile(normalSamples, "normal_samples.txt");
    std::cout << "Generated " << numSamplesNormal << " normal random numbers and saved to 'normal_samples.txt'.\n";
}

int main()
{
    srand(time(0)); // Seed the random number generator

    Exponential();
    Erlang();
    Normal();

    return 0;
}