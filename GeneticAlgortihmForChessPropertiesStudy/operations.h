#ifndef OPERATIONS
#define OPERATIONS

#include "position.h"
#include <algorithm> // for std::copy
#define XOVER_PROBABILITY 1
#define BOARD_MUTATION 1/1000
#define PIECE_MUTATION 1/1000

struct GenerationData {
	std::string code = "";
	float maximumFitness = 0.0;
	int maxNumberMoves = 0;
	double mean = 0.0;
	double std_dev = 0.0;
};

std::pair<GenerationData, GenerationData> operations(Position* currentGen, Position* nextGen);
void xOver(Position& pos1, Position& pos2, int xOverBoard, int xOverPieces, Position& new_generation);
//void PMX(Position& pos1, Position& pos2, int xOverIndex1, int xOverIndex2, bool isBoard);
Position weightedRouletteWheelSelection(Position* currentGeneration);
bool biasedCoin(float probability);
int xOverIndex(int type);
void mutation(Position& pos, double pBoard, double pPiece);
void generationAndOverallFittest(GenerationData& generationFittest, GenerationData& fittestOverall, Position& individual2Analyze);


#endif
