#include "position.h"
#include "operations.h"
using namespace std;

struct GenerationData {
	string code;
	int maximumFitness;
};

GenerationData getMaximumFitness();

#define NUMBER_OF_GENERATIONS 500

Position* next_generation = new Position[POPULATION_SIZE];
Position* current_generation = new Position[POPULATION_SIZE];

int main() {
	GenerationData data;
	for (int i = 0; i < NUMBER_OF_GENERATIONS; i++) {
		selection(current_generation, next_generation);
		for (int j = 0; j < POPULATION_SIZE; j++) {
			current_generation[j].setFED();
			current_generation[j].setFitness();
		}
		data = getMaximumFitness();
		cout << "Maximum Fitness of Gen " << i << ": " << data.maximumFitness;
		cout << " CODE: " << data.code << endl;
	}

	//Free heap memory
	delete[] current_generation;
	delete[] next_generation;
	return 0;
}

GenerationData getMaximumFitness() {
	GenerationData data = {"", 0};

	for (int i = 0; i < POPULATION_SIZE; i++) {
		if (current_generation[i].fitness > data.maximumFitness) {
			data.maximumFitness = current_generation[i].fitness;
			data.code = current_generation[i].FEDstringCode;
		}
	}
	return data;
}