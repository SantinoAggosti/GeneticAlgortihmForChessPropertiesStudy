// Author: @santinoagosti

#ifndef POSITION
#define POSITION

#include <stdio.h>
#include <array>
#include <iostream>
#include <random>
#include <unordered_map>


// Positions: Binary Coded organisms consisting of a gene to represent the pieces and positioning of such pieces.
// Each piece is encoded through 4 digits, as shown in FEDstrings. With a max quantity of pieces (32), the total encodign pieces length is 128 chars.
// The position is encoded through a binary matrix in string form (100101110....) of 64 characters, representing the allowed positioning of the pieces.
// Population Size indicated the amount of "Positions" organisms in the population at any given time.

#define POPULATION_SIZE 2750
#define PIECE_SIZE 4
#define N1 8
#define M1 8
#define BOARD_STRING_SIZE N1*M1
#define MAX_PIECES 32
#define PIECE_STRING_SIZE MAX_PIECES*PIECE_SIZE

bool generateRandomBit();

enum Species {
	FIRSTQ,
	SECONDQ,
	THIRDQ,
	FOURTHQ,
	NOBLACKKING
};

class Position {
public:
	//Initial Random Constructor
	Position() {
		setBoard();
		setPieces();
		//setSpecies();
		setFED();
		setFitness();
	}
	// Operational Constructor
	Position(std::array<bool, BOARD_STRING_SIZE> boardGene, std::array<bool, PIECE_STRING_SIZE> pieceGene) {
		setBoard(boardGene);
		setPieces(pieceGene);
		//setSpecies();
		setFitness();
		setFED();

	}
	std::unordered_map<std::string, std::string> FEDstrings = {
		{"1001", "P"},
		{"1010", "N"},
		{"1011", "B"},
		{"1100", "R"},
		{"1101", "Q"},
		{"1110", "K"},
		{"0001", "p"},
		{"0010", "n"},
		{"0011", "b"},
		{"0100", "r"},
		{"0101", "q"},
		{"0110", "k"},

	};
	float fitness;
	int species;
	int numberOfMoves;
	std::string FEDstringCode;
	std::array<bool, BOARD_STRING_SIZE> boardGene;
	std::array<bool, PIECE_STRING_SIZE> piecesGene;
	void printBoardGene();
	void printPiecesGene();
	void printFED();
	void setFitness();
	void setFED();
	void setSpecies(int& rank);
	void setSpecies();
	void setNumberOfMoves(int size);
private:
	void setBoard();
	void setPieces();

	void setBoard(std::array<bool, BOARD_STRING_SIZE>);
	void setPieces(std::array<bool, PIECE_STRING_SIZE>);
};

#endif