#ifndef OPERATIONS
#define OPERATIONS

#include "position.h"
#define XOVER_PROBABILITY 0.8

void selection(Position* currentGen, Position* nextGen);
void xOver(Position& pos1, Position& pos2, int xOverBoard, int xOverPieces, Position* new_generation);
Position weightedRouletteWheelSelection(Position* currentGeneration);
bool biasedCoin(float probability);
int xOverIndex(int type);

#endif
