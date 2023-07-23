#include <stdio.h>
#include <array>
#include <iostream>
#include <forward_list>
#include <vector>

bool generateRandomBit();

using namespace std;
#define POPULATION_SIZE 100
#define BOARD_STRING_SIZE 64
#define PIECE_STRING_SIZE 128

class Position {
public:
	Position() {
		setBoard();
		setPieces();
	}
	array<bool, BOARD_STRING_SIZE> boardGene;
	array<bool, PIECE_STRING_SIZE> piecesGene;
	void printBoardGene();
	void printPiecesGene();

private:
	void setBoard();
	void setPieces();
	
	//void CrossOver();
};