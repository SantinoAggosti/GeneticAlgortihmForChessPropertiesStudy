#ifndef POSITION
#define POSITION

#include <stdio.h>
#include <array>
#include <iostream>
#include <random>

bool generateRandomBit();

using namespace std;
#define POPULATION_SIZE 100
#define BOARD_STRING_SIZE 64
#define PIECE_STRING_SIZE 128

class Position {
public:
	//Initial Random Constructor
	Position() {
		setBoard();
		setPieces();
		setFitness();
	}
	// Operational Constructor
	Position(array<bool, BOARD_STRING_SIZE> boardGene, array<bool, PIECE_STRING_SIZE> pieceGene) {
		setBoard(boardGene);
		setPieces(pieceGene);
		setFitness();
	}
	int fitness;
	array<bool, BOARD_STRING_SIZE> boardGene;
	array<bool, PIECE_STRING_SIZE> piecesGene;
	void printBoardGene();
	void printPiecesGene();

private:
	void setBoard();
	void setPieces();
	void setFitness();

	void setBoard(array<bool, BOARD_STRING_SIZE>);
	void setPieces(array<bool, PIECE_STRING_SIZE>);
	
	//void CrossOver();
};

#endif