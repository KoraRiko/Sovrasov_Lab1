#include "file.h"
#include <cstdio>
#include <iostream>

// Write samples to a file
void writeSamplesToFile(const std::vector<double> &samples, const char *filename)
{
    FILE *file = fopen(filename, "w");
    if (file == nullptr)
    {
        std::cerr << "Error opening file for writing.\n";
        return;
    }
    for (double sample : samples)
    {
        fprintf(file, "%f\n", sample);
    }
    fclose(file);
}