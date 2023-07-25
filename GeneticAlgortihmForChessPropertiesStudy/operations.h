#ifndef OPERATIONS
#define OPERATIONS

#include "position.h"
#define XOVER_PROBABILITY 1
#define BOARD_MUTATION 1/1000
#define PIECE_MUTATION 1/1000

void operations(Position* currentGen, Position* nextGen);
void xOver(Position& pos1, Position& pos2, int xOverBoard, int xOverPieces, Position* new_generation);
Position weightedRouletteWheelSelection(Position* currentGeneration);
bool biasedCoin(float probability);
int xOverIndex(int type);
void mutation(Position& pos, double pBoard, double pPiece);

#endif
