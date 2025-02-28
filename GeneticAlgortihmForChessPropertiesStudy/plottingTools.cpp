// Author: @santinoagosti

#include "plottingTools.h"
void plotNormalCurve(double& mean, double& std_dev) {

	// Generate x values (e.g., from mean - 4*std_dev to mean + 4*std_dev)
	std::vector<double> x;
	for (double i = mean - 4 * std_dev; i <= mean + 4 * std_dev; i += 0.1) {
		x.push_back(i);
	}

	// Calculate the normal distribution (PDF)
	std::vector<double> y;
	const double pi = 3.14159265358979323846;
	for (double xi : x) {
		double exponent = -0.5 * std::pow((xi - mean) / std_dev, 2);
		double pdf = (1.0 / (std_dev * std::sqrt(2 * pi))) * std::exp(exponent);
		y.push_back(pdf);
	}

	// Plot using Matplot++
	matplot::plot(x, y);
	matplot::title("Fitness Distribution");
	matplot::xlabel("Fitness");
	matplot::ylabel("Normalized Fitness Individuals Quantity");
	matplot::grid(true);
	matplot::show();
}

void plotData(std::vector<int> &x, std::vector<double>& y, std::string title, std::string yLabel) {
	matplot::plot(x, y);
	matplot::title(title);
	matplot::xlabel("Generations");
	matplot::ylabel(yLabel);
	matplot::grid(true);
	matplot::show();
}