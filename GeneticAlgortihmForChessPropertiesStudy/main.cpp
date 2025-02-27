#include "position.h"
#include "operations.h"
#include "statistics.h"
#include <matplot/matplot.h>
#include <math.h>

//TODO: Classify each position in a given species.
// Each species is defined by the position the black king is at
// Generally what happens, is that a given position is fundamentally fitter in early generations
// and prolongs its life due to the key positioning of the black king within that position. Diminishing the genetic diversity
// for possible greater maxima.

// Dividing the chess positions in species by the rank at which the black king is positioned at, will provide with a way to compute several 
// sub-optimal maximas, reduce unnecesarry competition that detrys in early generations strong genetic sequences, and reproduce
// species competition after a given number of generations to produce new offspring and very-likkelly an auntouched subspace of the overall possible chess positions.

#define _USE_MATH_DEFINES

#define TSHOLD 32

#define NUMBER_OF_GENERATIONS 300
#define N_SPECIES 4

Position* next_generation = new Position[POPULATION_SIZE];
Position* current_generation = new Position[POPULATION_SIZE];

int main() {

	// X-axis for plotting
	std::vector<int> generationsVector;

	// Best fitness individual from each generation vector (FEN, Fitness and Number of MOves)
	std::vector<GenerationData> generationalData;

	// Statistics generational data
	std::vector<double> generationalStatistics;

	// Statistics auxiliary vector
	std::vector<double> auxFitnessStatistics;

	// Fittest Overall and Generational Fittest;
	std::pair<GenerationData, GenerationData> result;

	for (int i = 0; i < NUMBER_OF_GENERATIONS; i++) {

		// result = {generationalFittest, fittestOverall}
		result = operations(current_generation, next_generation);

		//Mean, StdDev, Median
		//auxFitnessStatistics = analyzeGeneration(current_generation, POPULATION_SIZE, 0.01, 3.6);

		std::cout << " -------------------------------------------------------------------------------------------------------------\n" << std::endl;

		std::cout << "Generation N: " << i + 1 << "\n" << std::endl;
		std::cout << "Fitness " << ": " << result.first.maximumFitness << std::endl;
		std::cout << "Number of Moves: " << result.first.maxNumberMoves << "\n" << std::endl;
		std::cout << " CODE: " << result.first.code << ";" << std::endl;
		std::cout << "Species: " << result.first.species << std::endl;

		//if (speciesOn) {
		//	std::cout << "Species Distribution - 1: " << result.first.speciesDist[0] << std::endl;
		//	std::cout << "Species Distribution - 2: " << result.first.speciesDist[1] << std::endl;
		//	std::cout << "Species Distribution - 3: " << result.first.speciesDist[2] << std::endl;
		//	std::cout << "Species Distribution - 4: " << result.first.speciesDist[3] << std::endl;
		//}


		//std::cout << "Generation Fitness Mean: " << auxFitnessStatistics[0] << std::endl;
		//std::cout << "Generation Fitness StdDev: " << auxFitnessStatistics[1] << "\n" << std::endl;

		generationsVector.push_back(i + 1);
		generationalData.push_back({ result.first.code, result.first.maximumFitness, result.first.maxNumberMoves, 0, 0 });
		//double mean = auxFitnessStatistics[0];
		//double std_dev = auxFitnessStatistics[1];

		//// Generate x values (e.g., from mean - 4*std_dev to mean + 4*std_dev)
		//std::vector<double> x;
		//for (double i = mean - 4 * std_dev; i <= mean + 4 * std_dev; i += 0.1) {
		//	x.push_back(i);
		//}

		//// Calculate the normal distribution (PDF)
		//std::vector<double> y;
		//const double pi = 3.14159265358979323846;
		//for (double xi : x) {
		//	double exponent = -0.5 * std::pow((xi - mean) / std_dev, 2);
		//	double pdf = (1.0 / (std_dev * std::sqrt(2 * pi))) * std::exp(exponent);
		//	y.push_back(pdf);
		//}

		//// Plot using Matplot++
		//matplot::plot(x, y);
		//matplot::title("Normal Distribution");
		//matplot::xlabel("X");
		//matplot::ylabel("Probability Density");
		//matplot::grid(true);
		//matplot::show();
	}
	std::cout << "CODE (Max Fit): " << result.second.code << "\n" << std::endl;
	std::cout << "MOVES (Overall Max Fit):" << result.second.maxNumberMoves << std::endl;
	//Free heap memory
	delete[] current_generation;
	delete[] next_generation;
	return 0;
}

//// Returns if two individuals can be of the same species
//bool Compatibility(Position pos1, Position pos2) {
//	float compatibility = 0;
//	for (int i = 0; i < PIECE_STRING_SIZE; i++) {
//		if (pos1.piecesGene[i] == pos2.piecesGene[i]) {
//			compatibility += 1;
//		}
//	}
//	for (int i = 0; i < BOARD_STRING_SIZE; i++) {
//		if (pos1.boardGene[i] == pos2.boardGene[i]) {
//			compatibility += 1;
//		}
//	}
//	if (compatibility > TSHOLD) {
//		return true;
//	}
//}
//
//void SpeciesGeneration(Position* current_generation) {
//	for (int i = 0; i < POPULATION_SIZE; i++) {
//		Position pos = current_generation[i];
//	}
//}

