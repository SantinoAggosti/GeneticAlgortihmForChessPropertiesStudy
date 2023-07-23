#include "position.h"
using namespace std;

int main() {
	Position* generation = new Position[POPULATION_SIZE];
	generation[46].printBoardGene();
	generation[46].printPiecesGene();

	//Free heap memory
	delete[] generation;
	return 0;
}