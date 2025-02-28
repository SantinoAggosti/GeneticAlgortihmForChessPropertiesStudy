// Author: @santinoagosti

#ifndef STATISTICS
#define STATISTICS

#include <iostream>
#include "position.h"
#include <vector>
#include <algorithm> // For std::sort
#include <cmath>     // For std::sqrt
#include <stdexcept>

double calculateMean(Position* currentGeneration, int n);
double calculateStdDev(Position* currentGeneration, int n, double mean);
std::vector<double> analyzeGeneration(Position* currentGeneration, int N, double epsilon, double z);

#endif 