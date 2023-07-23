#include "position.h"
#include <iostream>
#include <random>

void Position :: setPieces() {
    for (int i = 0; i < 128; i++) {
        piecesGene[i] = generateRandomBit();
    }
}

void Position::setBoard() {
    for (int i = 0; i < 64; i++) {
        boardGene[i] = generateRandomBit();
    }
}

bool generateRandomBit() {
    random_device rd; // Obtain a random seed from hardware
    mt19937 gen(rd()); // Seed the random number generator
    uniform_int_distribution<> distrib(0, 1); // Distribution for generating 0 or 1

    int randomBit = distrib(gen); // Generate 0 or 1 randomly

    return randomBit;
}

void Position :: printBoardGene() {
    cout << "Board: ";
    for (int i = 0; i < BOARD_STRING_SIZE; i++) {
        cout << boardGene[i];
    }
    cout << endl;
}

void Position::printPiecesGene() {
    cout << "Pieces: ";
    for (int i = 0; i < PIECE_STRING_SIZE; i++) {
        cout << piecesGene[i];
    }
    cout << endl;
}
