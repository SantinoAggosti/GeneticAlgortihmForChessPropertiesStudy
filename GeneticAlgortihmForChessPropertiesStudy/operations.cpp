#include "operations.h"

void xOver(Position& pos1, Position& pos2, int xOverBoard, int xOverPieces, Position* new_generation) {

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
    *new_generation = newPosition;
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

void selection(Position* currentGeneration, Position* nextGeneration) {
    nextGeneration;
    int xOverBoard, xOverPieces;
    int counter = 0;
    while (counter != POPULATION_SIZE) {
        xOverBoard = xOverIndex(BOARD_STRING_SIZE);
        xOverPieces = xOverIndex(PIECE_STRING_SIZE);
        Position pos1 = weightedRouletteWheelSelection(currentGeneration);
        Position pos2 = weightedRouletteWheelSelection(currentGeneration);

        if (biasedCoin(XOVER_PROBABILITY)) {
            counter++;
            xOver(pos1, pos2, xOverBoard, xOverPieces, nextGeneration++);
        }
    }
    for (int i = 0; i < POPULATION_SIZE; i++) {
        nextGeneration--;
    }

    for (int j = 0; j < POPULATION_SIZE; j++) {
        currentGeneration[j] = nextGeneration[j];
    }
}

// Function to perform weighted roulette wheel selection
Position weightedRouletteWheelSelection(Position* currentGeneration) {
    // Calculate the total fitness of all individuals
    double totalFitness = 0.0;
    for (int i = 0; i < POPULATION_SIZE; i++) {
        totalFitness += currentGeneration[i].fitness;
    }

    // Generate a random value within the range of the total fitness
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> distrib(0.0, totalFitness);
    double randomValue = distrib(gen);

    // Spin the roulette wheel to select an individual
    double partialSum = 0.0;
    for (int i = 0; i < POPULATION_SIZE; i++) {
        partialSum += currentGeneration[i].fitness;
        if (randomValue <= partialSum) {
            return currentGeneration[i];
        }
    }

    // This should not be reached, but return the last individual just in case
    return currentGeneration[POPULATION_SIZE - 1];
}

int xOverIndex(int type) {
    // Size of gene indiccates type of xOverIndex I am going to be using
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> distrib(0.0, 1);
    double randomValue = distrib(gen);
    int xOverIndex;
    if (type == BOARD_STRING_SIZE) {
        xOverIndex = randomValue * BOARD_STRING_SIZE;
    }
    else {
        xOverIndex = randomValue * PIECE_STRING_SIZE;
    }
    return xOverIndex;
}




