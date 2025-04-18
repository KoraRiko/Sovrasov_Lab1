
#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <fstream>
#include "random_generators.h"
// #include "file.h"

// Structure to represent events in the simulation log
struct LogEntry
{
    std::string eventType; // 'J1', 'J2', 'E' (End of processing)
    double currentTime;
    double nextJ1;
    double nextJ2;
    double endOfProcessing;
    int serverStatus;
    int queueLength;
    std::string queueContent;
};

// Function to simulate the system
void runSimulation()
{
    srand(time(0)); // Seed the random number generator

    // Initialize variables
    double t = 0.0;             // Current time
    double L1 = functionI1();   // Next arrival time for J1
    double L2 = functionI2();   // Next arrival time for J2
    double h = 501.0;           // End of processing (fake initial value)
    int S = 0;                  // Server status (0: free, 1: busy)
    int n = 0;                  // Queue length
    std::vector<std::string> Q; // FIFO queue

    // Measures of Effectiveness
    double totalBusyTime = 0.0; // Total time the server is busy
    int maxQueueLength = 0;     // Maximum queue length observed

    std::ofstream outFile("Simulation.txt");
    if (!outFile.is_open())
    {
        std::cerr << "Error in opening file.\n";
        return;
    }

    outFile << "Event\tTm\tJ1\tJ2\tSt\tS\tn\tQ\n";
    // Simulation loop
    while (t < 500.0)
    {
        // Determine the next event
        double nextEventTime = L1;
        if (L2 < nextEventTime)
            nextEventTime = L2;
        if (h < nextEventTime)
            nextEventTime = h;

        // Update server status and queue length
        if (S == 1)
        {
            totalBusyTime += (nextEventTime - t); // Accumulate busy time
        }

        // Handle events
        const double epsilon = 1e-6;
        std::string eventType;
        if (std::abs(t - L1) < epsilon)
        {
            eventType = "J1";
            // Job J1 arrives
            if (S == 0)
            {
                // Server is free, start processing
                S = 1;
                h = t + functionP1(); // Processing time for J1
            }
            else
            {
                // Server is busy, add to queue
                Q.push_back("J1");
                n++;
                maxQueueLength = std::max(maxQueueLength, n);
            }
            L1 = t + functionI1(); // Schedule next J1 arrival
        }
        else if (std::abs(t - L2) < epsilon)
        {
            eventType = "J2";
            // Job J2 arrives
            if (S == 0)
            {
                // Server is free, start processing
                S = 1;
                h = t + functionP2(); // Processing time for J2
            }
            else
            {
                // Server is busy, add to queue
                Q.push_back("J2");
                n++;
                maxQueueLength = std::max(maxQueueLength, n);
            }
            L2 = t + functionI2(); // Schedule next J2 arrival
        }
        else if (std::abs(t - h) < epsilon)
        {
            eventType = "E";
            // Processing ends
            S = 0;
            if (!Q.empty())
            {
                // Start processing the next job in the queue
                std::string nextJob = Q.front();
                Q.erase(Q.begin());
                n--;
                if (nextJob == "J1")
                {
                    h = t + functionP1(); // Processing time for J1
                }
                else
                {
                    h = t + functionP2(); // Processing time for J2
                }
            }
            else
            {
                h = 501.0; // Reset to fake value
            }
        }

        // Log the simulation process
        std::string queueContent = Q.empty() ? "empty" : "";
        for (const std::string &job : Q)
        {
            queueContent += job + " ";
        }

        if (!queueContent.empty())
        {
            queueContent.pop_back();
        }

        outFile << eventType << "\t"
                << t << "\t"
                << L1 << "\t"
                << L2 << "\t"
                << h << "\t"
                << S << "\t"
                << n << "\t"
                << queueContent << "\n";

        t = nextEventTime;
    }
    outFile.close();

    // Calculate Measures of Effectiveness
    double loadFactor = totalBusyTime / 500.0;
    std::cout << "Load Factor: " << loadFactor << "\n";
    std::cout << "Max Queue Length: " << maxQueueLength << "\n";
}

int main()
{
    runSimulation();
    return 0;
}