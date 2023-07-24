#ifndef POSITION
#define POSITION

#include <stdio.h>
#include <array>
#include <iostream>
#include <random>
#include <unordered_map>

bool generateRandomBit();

using namespace std;
#define POPULATION_SIZE 250
#define PIECE_SIZE 4
#define N 8
#define M 8
#define BOARD_STRING_SIZE N*M
#define PIECE_STRING_SIZE 128


//unordered_map<string, string> FEDstrings;

class Position {
public:
	//Initial Random Constructor
	Position() {
		setBoard();
		setPieces();
		setFitness();
		setFED();
	}
	// Operational Constructor
	Position(array<bool, BOARD_STRING_SIZE> boardGene, array<bool, PIECE_STRING_SIZE> pieceGene) {
		setBoard(boardGene);
		setPieces(pieceGene);
		setFitness();
		setFED();
	}
	unordered_map<string, string> FEDstrings = {
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
	int fitness;
	string FEDstringCode;
	array<bool, BOARD_STRING_SIZE> boardGene;
	array<bool, PIECE_STRING_SIZE> piecesGene;
	void printBoardGene();
	void printPiecesGene();
	void printFED();
	void setFitness();
	void setFED();

private:
	void setBoard();
	void setPieces();

	void setBoard(array<bool, BOARD_STRING_SIZE>);
	void setPieces(array<bool, PIECE_STRING_SIZE>);
	
	//void CrossOver();
};

#endif