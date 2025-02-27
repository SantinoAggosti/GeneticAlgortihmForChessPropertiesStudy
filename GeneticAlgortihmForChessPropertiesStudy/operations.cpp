#include "operations.h"
using namespace std;
void PMX(Position& pos1, Position& pos2, int xOverIndex1, int xOverIndex2, bool isBoard, Position* nextGeneration) {
	// Largest size
	int const arraySize = PIECE_STRING_SIZE;
	array<bool, arraySize> boardArr1{};
	array<bool, arraySize> boardArr2{};
	if (isBoard) {
		for (int i = xOverIndex1; i < xOverIndex2; i++) {
			boardArr1[i] = pos2.boardGene[i];
			boardArr2[i] = pos1.boardGene[i];
		}
		for (int i = xOverIndex1; i < xOverIndex2; i++) {
			pos1.boardGene[i] = boardArr1[i];
			pos2.boardGene[i] = boardArr2[i];
		}
	}
	else {
		for (int i = xOverIndex1; i < xOverIndex2; i++) {
			boardArr1[i] = pos2.piecesGene[i];
			boardArr2[i] = pos1.piecesGene[i];
		}
		for (int i = xOverIndex1; i < xOverIndex2; i++) {
			pos1.piecesGene[i] = boardArr1[i];
			pos2.piecesGene[i] = boardArr2[i];
		}
	}

}

// CrossOver Function: Genetic Diversification is generated through Crossover operation.
void xOver(Position& pos1, Position& pos2, int xOverBoard, int xOverPieces, Position& newIndividual) {

	array<bool, BOARD_STRING_SIZE> newBoardGene{};
	array<bool, PIECE_STRING_SIZE> newPieceGene{};

	//CrossOver Board Gene
	for (int i = 0; i < xOverBoard && i < pos1.boardGene.size(); ++i) {
		newBoardGene[i] = pos1.boardGene[i];
	}
	for (int i = xOverBoard; i < pos2.boardGene.size(); ++i) {
		newBoardGene[i] = pos2.boardGene[i];
	}

	//CrossOver Pieces Gene
	for (int i = 0; i < xOverPieces && i < pos1.piecesGene.size(); ++i) {
		newPieceGene[i] = pos1.piecesGene[i];
	}
	for (int i = xOverPieces; i < pos2.piecesGene.size(); ++i) {
		newPieceGene[i] = pos2.piecesGene[i];
	}

	Position newPosition(newBoardGene, newPieceGene);
	newIndividual = newPosition;
}

bool biasedCoin(float p) {
	random_device rd; // Obtain a random seed from hardware
	mt19937 gen(rd()); // Seed the random number generator
	uniform_int_distribution<> distrib(0, 1); // Distribution for generating 0 or 1

	if (distrib(gen) < p) {
		// Execute action with probability p
		return true;
	}
	else {
		// Do not execute the action with probability p
		return false;
	}
}

// Information holder for fittest individual overall.
GenerationData fittestOverall = { "", 0, 0 };

// Information holder for fittest individual within a genertion
GenerationData generationFittest = { "", 0, 0 };

//TODO: Speciation requires strict distinction between individuals. Even considering their overall net fitness.
// The weighted rullete selection should be strictlly performed by normalizing each fitness with their respective Species population.

// Operations: The whole set of operations is executed in the correct order through the overall population.
std::pair<GenerationData, GenerationData> operations(Position* currentGeneration, Position* nextGeneration) {
	int xOverBoard1, xOverBoard2, xOverPieces1, xOverPieces2;
	generationFittest = { "", 0, 0, FIRSTQ };
	vector<double> speciesDistribution = { 0, 0, 0, 0, 0 };
	for (int i = 0; i < POPULATION_SIZE; i++) {

		switch (currentGeneration[i].species) {
		case FIRSTQ:
			speciesDistribution[0] += 1;

			break;
		case SECONDQ:
			speciesDistribution[1] += 1;

			break;
		case THIRDQ:
			speciesDistribution[2] += 1;

			break;
		case FOURTHQ:
			speciesDistribution[3] += 1;

			break;
		case NOBLACKKING:
			speciesDistribution[4] += 1;

			break;
		}
		generationFittest.speciesDist = speciesDistribution;
		xOverBoard1 = xOverIndex(BOARD_STRING_SIZE);
		xOverBoard2 = xOverIndex(BOARD_STRING_SIZE);

		xOverPieces1 = xOverIndex(PIECE_STRING_SIZE);
		xOverPieces2 = xOverIndex(PIECE_STRING_SIZE);

		// Probabilistic fitness scaled selection. (Iteration through current Generation)
		Position pos1 = weightedRouletteWheelSelection(currentGeneration);
		Position pos2 = weightedRouletteWheelSelection(currentGeneration);


		// Speciation is applied for reproduction!
		/*while (pos1.species != pos2.species) {
			pos1 = weightedRouletteWheelSelection(currentGeneration);
		}*/


		if (biasedCoin(XOVER_PROBABILITY)) {
			xOver(pos1, pos2, xOverBoard1, xOverPieces1, nextGeneration[i]);
			//PMX(pos1, pos2, nextGeneration);

		}
		else {
			// No crossOver produced
			nextGeneration[i] = biasedCoin(0.5) ? pos2 : pos1;
		}

		// Mutation process
		mutation(nextGeneration[i], BOARD_MUTATION, PIECE_MUTATION);

		// Set values for new Generation individual
		nextGeneration[i].setFED();
		nextGeneration[i].setFitness();

		// Update generational and overall data
		generationAndOverallFittest(generationFittest, fittestOverall, nextGeneration[i]);

	}

	// The pointer initially being used to allocate the current generation now points
	// To the now updated next generation.
	//
	// The pointer that previouslly pointed to the to-fullfill generation now points to the previous population.
	// This dynamic memory that allocated the previous population, will now be edited through the OPERATIONS function.

	// This saves the iteration through the entire Population to individually assign one generation to the other.
	//std::swap(currentGeneration, nextGeneration);

	for (int i = 0; i < POPULATION_SIZE; i++) {
		currentGeneration[i] = nextGeneration[i];
	}

	return { generationFittest, fittestOverall };
}

// Wighted Roullete: Function to perform weighted roulette wheel operations
Position weightedRouletteWheelSelection(Position* currentGeneration) {
	// Calculate the total fitness of all individuals
	vector<double> totalFitness = { 0, 0, 0, 0, 0 };
	double fitnessSum = 0;
	for (int i = 0; i < POPULATION_SIZE; i++) {
		switch (currentGeneration[i].species) {
		case FIRSTQ:
			totalFitness[0] += currentGeneration[i].fitness;
			break;
		case SECONDQ:
			totalFitness[1] += currentGeneration[i].fitness;
			break;
		case THIRDQ:
			totalFitness[2] += currentGeneration[i].fitness;
			break;
		case FOURTHQ:
			totalFitness[3] += currentGeneration[i].fitness;
			break;
		case NOBLACKKING:
			totalFitness[4] += currentGeneration[i].fitness;
			break;
		}
	}
	for (int i = 0; i < 5; i++) {
		fitnessSum += totalFitness[i];
	}
	vector<double> normalizationFactors = { 0, 0, 0, 0, 0 };
	for (int i = 0; i < 5; i++) {
		normalizationFactors[i] = fitnessSum / (5 * totalFitness[i]);
	}
	// Generate a random value within the range of the total fitness
	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<> distrib(0.0, fitnessSum);
	double randomValue = distrib(gen);

	// Spin the roulette wheel to select an individual
	double partialSum = 0.0;
	for (int i = 0; i < POPULATION_SIZE; i++) {

		// Fitness normalization: Each species now has 25% chance of being choseen for reproduction.
		switch (currentGeneration[i].species) {
		case FIRSTQ:
			currentGeneration[i].fitness *= normalizationFactors[0];
			break;
		case SECONDQ:
			currentGeneration[i].fitness *= normalizationFactors[1];
			break;
		case THIRDQ:
			currentGeneration[i].fitness *= normalizationFactors[2];
			break;
		case FOURTHQ:
			currentGeneration[i].fitness *= normalizationFactors[3];
			break;
		case NOBLACKKING:
			currentGeneration[i].fitness *= normalizationFactors[4];
			break;
		}

		partialSum += currentGeneration[i].fitness;
		if (randomValue <= partialSum) {
			return currentGeneration[i];
		}
	}

	// This should not be reached, but return the last individual just in case
	return currentGeneration[POPULATION_SIZE - 1];
}

// XOverIndex: Index Cross Over Selection
int xOverIndex(int type) {
	// Size of gene indiccates type of xOverIndex I am going to be using
	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<> distrib(0.0, 1.0);
	double randomValueBoard = distrib(gen);
	double randomValuePiece = distrib(gen);
	int xOverIndex;
	if (type == BOARD_STRING_SIZE) {
		xOverIndex = randomValueBoard * BOARD_STRING_SIZE;
	}
	else {
		xOverIndex = randomValueBoard * PIECE_STRING_SIZE;
	}
	return xOverIndex;
}

// Mutation: Additional genetic diversification and generation of unexplores genetic code is produced through Mutation of single alleles in genes.
void mutation(Position& pos, double pBoard, double pPiece) {
	random_device rd;  // Seed for the random number generator
	mt19937 gen(rd()); // Mersenne Twister random number engine
	uniform_real_distribution<> dis(0.0, 1.0); // Uniform distribution [0, 1)

	for (int i = 0; i < BOARD_STRING_SIZE; i++) {
		// Generate a random number between 0 and 1
		double randomProb = dis(gen);

		// If the random number is less than the probability, mutate the bit
		if (randomProb < pBoard) {
			pos.boardGene[i] = !pos.boardGene[i]; // Mutate the bit (flip 0 to 1 or 1 to 0)
		}
	}
	for (int j = 0; j < PIECE_STRING_SIZE; j++) {
		// Generate a random number between 0 and 1
		double randomProb = dis(gen);

		// If the random number is less than the probability, mutate the bit
		if (randomProb < pPiece) {
			pos.piecesGene[j] = !pos.piecesGene[j]; // Mutate the bit (flip 0 to 1 or 1 to 0)
		}
	}
}

// Optimization is still required.
void generationAndOverallFittest(GenerationData& generationFittest, GenerationData& fittestOverall, Position& individual2Analyze) {
	if (individual2Analyze.fitness > fittestOverall.maximumFitness) {
		fittestOverall.maximumFitness = individual2Analyze.fitness;
		fittestOverall.code = individual2Analyze.FEDstringCode;
		fittestOverall.maxNumberMoves = individual2Analyze.numberOfMoves;
		fittestOverall.species = individual2Analyze.species;

		generationFittest.maximumFitness = individual2Analyze.fitness;
		generationFittest.code = individual2Analyze.FEDstringCode;
		generationFittest.maxNumberMoves = individual2Analyze.numberOfMoves;
		generationFittest.species = individual2Analyze.species;
	}

	else if (individual2Analyze.fitness > generationFittest.maximumFitness) {
		generationFittest.maximumFitness = individual2Analyze.fitness;
		generationFittest.code = individual2Analyze.FEDstringCode;
		generationFittest.maxNumberMoves = individual2Analyze.numberOfMoves;
		generationFittest.species = individual2Analyze.species;
	}
}