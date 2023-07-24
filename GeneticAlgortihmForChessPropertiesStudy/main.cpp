#include "position.h"
#include "operations.h"
using namespace std;

Position* next_generation = new Position[POPULATION_SIZE];
Position* current_generation = new Position[POPULATION_SIZE];

int main() {

	cout << "GEN 1:" << endl;
	current_generation[0].printBoardGene();
	current_generation[0].printPiecesGene();
	current_generation[1].printBoardGene();
	current_generation[1].printPiecesGene();

	selection(current_generation, next_generation);

	cout << "GEN 2:" << endl;

	current_generation[0].printBoardGene();
	current_generation[0].printPiecesGene();
	current_generation[1].printBoardGene();
	current_generation[1].printPiecesGene();

	//xOver(current_generation[0], current_generation[1], 4, 4, next_generation);
	//cout << "CrossedOver position: " << endl;
	//next_generation[0].printBoardGene();
	//next_generation[0].printPiecesGene();

	//Free heap memory
	delete[] current_generation;
	delete[] next_generation;
	return 0;
}