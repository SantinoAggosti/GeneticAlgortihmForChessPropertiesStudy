// Author: @santinoagosti

#include "statistics.h"
using namespace std;

// Grok 3 was used to synthesyse the following document:

// @file: Hypothesis Testing given a population size, confidence level and error satisfaction for fitness.

// Function to calculate mean of a vector slice (first n elements)
double calculateMean(Position* currentGeneration, int n) {
    if (n == 0 || n > POPULATION_SIZE) throw invalid_argument("Invalid sample size");
    double sum = 0.0;
    for (int i = 0; i < n; ++i) {
        sum += currentGeneration[i].fitness;
    }
    return sum / n;
}

// Function to calculate standard deviation of a vector slice (first n elements)
double calculateStdDev(Position* currentGeneration, int n, double mean) {
    if (n <= 1) throw invalid_argument("Sample size too small for standard deviation");
    double sumSquaredDiff = 0.0;
    for (int i = 0; i < n; ++i) {
        double diff = currentGeneration[i].fitness - mean;
        sumSquaredDiff += diff * diff;
    }
    return sqrt(sumSquaredDiff / (n - 1)); // Sample standard deviation
}

// Function to calculate required sample size and statistics
vector<double> analyzeGeneration(Position* currentGeneration, int N, double epsilon, double z) {
    // Step 1: Calculate initial mean and std dev from full population to estimate CV
    double fullMean = calculateMean(currentGeneration, POPULATION_SIZE);
    double fullStdDev = calculateStdDev(currentGeneration, POPULATION_SIZE, fullMean);
    double cv = fullStdDev / fullMean;

    // Step 2: Calculate initial sample size n0
    double zOverEpsilon = z / epsilon;
    double n0 = (zOverEpsilon * cv) * (zOverEpsilon * cv);
    //cout << "Initial sample size (n0): " << n0 << "\n";

    // Step 3: Apply finite population correction
    // n: Adjusted sample size
    double n = n0 / (1.0 + (n0 - 1.0) / N);
    int sampleSize = static_cast<int>(ceil(n));
    if (sampleSize > POPULATION_SIZE) {
        sampleSize = POPULATION_SIZE; // Cap at population size
        cout << "Warning: Required sample size exceeds population; using full population\n";
    }
    // Step 4: Calculate statistics using first n individuals
    double mean = calculateMean(currentGeneration, sampleSize);
    double stdDev = calculateStdDev(currentGeneration, sampleSize, mean);
    //double median = calculateMedian(currentGeneration, sampleSize);

    //// Step 5: Output results
    //cout << "Estimated Mean: " << mean << "\n";
    //cout << "Estimated Standard Deviation: " << stdDev << "\n";
    //cout << "Estimated Median: " << median << "\n";
    //cout << "These estimates are within " << (epsilon * 100) << "% error with "
    //    << (1.0 - 2.0 * std::erfc(z / std::sqrt(2))) * 100 << "% confidence\n";

    vector<double> meanStdDevMedian = { mean, stdDev};
    return meanStdDevMedian;
}
