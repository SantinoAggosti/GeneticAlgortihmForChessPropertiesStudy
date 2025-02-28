#ifndef PLOTTINGTOOLS
#define PLOTTINGTOOLS

#include <matplot/matplot.h>

void plotNormalCurve(double& mean, double& std_dev);
void plotData(std::vector<int>&, std::vector<double>&, std::string, std::string);

#endif // !PLOTTINGTOOLS
