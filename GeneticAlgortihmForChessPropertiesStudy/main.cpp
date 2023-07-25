#include "position.h"
#include "operations.h"
using namespace std;

struct GenerationData {
	string code;
	float maximumFitness;
	int maxNumberMoves;
};

GenerationData getMaximumFitness();
void getMaximumFitness(GenerationData &data);
void getMaximumMoves(GenerationData& data);



#define NUMBER_OF_GENERATIONS 3000

Position* next_generation = new Position[POPULATION_SIZE];
Position* current_generation = new Position[POPULATION_SIZE];

int main() {
	int maxMoves = 0;
	GenerationData finalFitData = {"", 0, 0};
	GenerationData finalMoveData = {"", 0, 0};
	GenerationData data;
	for (int i = 0; i < NUMBER_OF_GENERATIONS; i++){
		operations(current_generation, next_generation);
		for (int j = 0; j < POPULATION_SIZE; j++) {
			current_generation[j].setFED();
			current_generation[j].setFitness();
		}
		data = getMaximumFitness();
		getMaximumFitness(finalFitData);
		getMaximumMoves(finalMoveData);
		cout << "Maximum Fitness of Gen " << i << ": " << data.maximumFitness;
		cout << " CODE: " << data.code << "; ";
		cout << "Number of Moves: " << data.maxNumberMoves << endl;
	}
	cout <<"CODE (Max Move): " << finalMoveData.code << "; MOVES:" << finalMoveData.maxNumberMoves << endl;
	cout << "CODE (Max Fit): " << finalFitData.code << "; MOVES:" << finalFitData.maxNumberMoves << endl;


	//Free heap memory
	delete[] current_generation;
	delete[] next_generation;
	return 0;
}

GenerationData getMaximumFitness() {
	GenerationData data = {"", 0, 0};

	for (int i = 0; i < POPULATION_SIZE; i++) {
		if (current_generation[i].fitness > data.maximumFitness) {
			data.maximumFitness = current_generation[i].fitness;
			data.code = current_generation[i].FEDstringCode;
		}
		if (current_generation[i].numberOfMoves > data.maxNumberMoves) {
			data.maxNumberMoves = current_generation[i].numberOfMoves;
		}
	}
	return data;
}

void getMaximumFitness(GenerationData &data) {

	for (int i = 0; i < POPULATION_SIZE; i++) {
		if (current_generation[i].fitness > data.maximumFitness) {
			data.maximumFitness = current_generation[i].fitness;
			data.code = current_generation[i].FEDstringCode;
			data.maxNumberMoves = current_generation[i].numberOfMoves;
		}
	
	}
}

void getMaximumMoves(GenerationData &data) {

	for (int i = 0; i < POPULATION_SIZE; i++) {
		if (current_generation[i].numberOfMoves > data.maxNumberMoves) {
			data.code = current_generation[i].FEDstringCode;
			data.maxNumberMoves = current_generation[i].numberOfMoves;
		}

	}
}