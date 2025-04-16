#ifndef RANDOM_GENERATORS_H
#define RANDOM_GENERATORS_H

// Function declarations
double generateUniform();
double generateExponential(double lambda);
double generateErlang(int k, double lambda);
double generateNormal(double mean, double stddev);
#endif // RANDOM_GENERATORS_H
