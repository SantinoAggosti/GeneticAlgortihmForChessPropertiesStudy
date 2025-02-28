// Author: @santinoagosti

#include "position.h"
#include "operations.h"
#include "statistics.h"
#include "plottingTools.h"

#include <math.h>

#define _USE_MATH_DEFINES

#define NUMBER_OF_GENERATIONS 500
#define N_SPECIES 4

Position* next_generation = new Position[POPULATION_SIZE];
Position* current_generation = new Position[POPULATION_SIZE];



int main() {
	// X-axis for plotting
	std::vector<int> generationsVector;

	// Best fitness individual from each generation vector (FEN, Fitness and Number of MOves)
	std::vector<GenerationData> generationalData;

	// Statistics data and auxiliary vector;
	std::vector<double> auxFitnessStatistics;
	double mean = 0;
	double std_dev = 1;

	// Allowed error in statistical test of hypothesis
	double epsilon = 0.01;

	// Z-Value for test of hypothesis
	double z_value = 3.6;

	// Fittest Overall and Generational Fittest;
	std::pair<Position, Position> result;

	// Generation and Overall fittest individuals
	Position fittestIndividualInGen;
	Position fittestIndividualOverall = Position();

	// Graphing data
	GraphingData graphs;

	for (int i = 0; i < NUMBER_OF_GENERATIONS; i++) {

		// Selection, Cross-over, mutation;
		result = operations(current_generation, next_generation, fittestIndividualOverall);

		// Operations returns the best individual in the generation and overall through the whole program run
		fittestIndividualInGen = result.first;
		fittestIndividualOverall = result.second;

		//Mean, StdDev, Median
		auxFitnessStatistics = analyzeGeneration(current_generation, POPULATION_SIZE, epsilon, z_value);

		std::cout << " --------------------------------------------------------------------------\n" << std::endl;
		std::cout << "Generation N: " << i + 1 << "\n" << std::endl;
		std::cout << "Fitness " << ": " << fittestIndividualInGen.fitness << std::endl;
		std::cout << "Number of Moves: " << fittestIndividualInGen.numberOfMoves << "\n" << std::endl;
		std::cout << " CODE: " << fittestIndividualInGen.FEDstringCode << ";" << std::endl;
		std::cout << "Species: " << fittestIndividualInGen.species << std::endl;

		//if (speciesOn) {
		//	std::cout << "Species Distribution - 1: " << result.first.speciesDist[0] << std::endl;
		//	std::cout << "Species Distribution - 2: " << result.first.speciesDist[1] << std::endl;
		//	std::cout << "Species Distribution - 3: " << result.first.speciesDist[2] << std::endl;
		//	std::cout << "Species Distribution - 4: " << result.first.speciesDist[3] << std::endl;
		//}

		// Statistical Analysis Results
		mean = auxFitnessStatistics[0];
		std_dev = auxFitnessStatistics[1];

		// Statistical Anlaysis printing
		std::cout << "Generation Fitness Mean: " << mean << std::endl;
		std::cout << "Generation Fitness StdDev: " << std_dev << "\n" << std::endl;

		// X-axis Generations
		generationsVector.push_back(i + 1);

		// Recompile data for Y-axis Graphing
		graphs.maxFitnessData.push_back(fittestIndividualInGen.fitness);
		graphs.fitMovementData.push_back(fittestIndividualInGen.numberOfMoves);
		graphs.meanData.push_back(mean);
		graphs.stdDevData.push_back(std_dev);

		// Overall Generational Data through program run is saved
		generationalData.push_back({ result.first });
	}

	plotNormalCurve(mean, std_dev);
	plotData(generationsVector, graphs.maxFitnessData, "Maximum Fitness per Generation", "Fitness");
	plotData(generationsVector, graphs.fitMovementData, "N° of Movements in Fittest Individual per Generation", "Fitness");
	plotData(generationsVector, graphs.meanData, "Mean Fitness per Generation", "Fitness");
	plotData(generationsVector, graphs.stdDevData, "Standard Deviation per Generation", "Fitness");



	std::cout << "CODE (Max Fit): " << fittestIndividualOverall.FEDstringCode << "\n" << std::endl;
	std::cout << "MOVES (Overall Max Fit):" << fittestIndividualOverall.numberOfMoves << std::endl;

	//Free heap memory from generations
	delete[] current_generation;
	delete[] next_generation;
	return 0;
}
