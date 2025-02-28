#ifndef OPERATIONS
#define OPERATIONS

#include "position.h"
#define XOVER_PROBABILITY 1
#define BOARD_MUTATION 1/1000
#define PIECE_MUTATION 1/1000


struct GenerationData {

	// Fittest individual within a generation
	Position fittestIndividual = Position();

	// Statistical data of each generation
	double mean = 0.0;
	double std_dev = 0.0;

	// Species implementation analysis
	std::vector<double> speciesDist = { 0, 0, 0, 0, 0 };
};

struct GraphingData {
	// Fitness value from fittest individual in each generation evolution data.
	std::vector<double> maxFitnessData = {};

	// N° of movements value from fittest individual in each generation evolution data.
	std::vector<double> fitMovementData = {};

	// Max N° of movements in each generation (independentlly of fitness) evolution data.
	std::vector<double> maxMovementData = {};

	// Statistical values (mean & std_dev) in  each generation evolution data.
	std::vector<double> meanData = {};

	std::vector<double> stdDevData = {};
};

std::pair<Position, Position> operations(Position* currentGen, Position* nextGen, Position& fittestoverall);
void xOver(Position& pos1, Position& pos2, int xOverBoard, int xOverPieces, Position& new_generation);
//void PMX(Position& pos1, Position& pos2, int xOverIndex1, int xOverIndex2, bool isBoard);
Position weightedRouletteWheelSelection(Position* currentGeneration);
bool biasedCoin(float probability);
int xOverIndex(int type);
void mutation(Position& pos, double pBoard, double pPiece);
void generationAndOverallFittest(Position& generationFittest, Position& fittestOverall, Position& individual2Analyze);


#endif
