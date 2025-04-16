#include "file.h"
#include <cstdio>
#include <fstream>
#include <iostream>

// Write samples to a file
/*
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
*/

void writeSimulationLog(const std::string& logEntry)
{
    static std::ofstream logFile("simulation_log.txt");
    if (!logFile.is_open())
    {
        std::cerr << "Error opening log file.\n";
        return;
    }
    logFile << logEntry << "\n";
}