// Author: @santinoagosti

#include "position.h"
#include <string>
#include "thc.h"
#include <cmath>

using namespace std;


void Position::setPieces() {
	for (int i = 0; i < PIECE_STRING_SIZE; i++) {
		piecesGene[i] = generateRandomBit();
	}
}

void Position::setBoard() {
	for (int i = 0; i < BOARD_STRING_SIZE; i++) {
		boardGene[i] = generateRandomBit();
	}
}

void Position::setBoard(array<bool, BOARD_STRING_SIZE> board) {
	for (int i = 0; i < BOARD_STRING_SIZE; i++) {
		boardGene[i] = board[i];
	}
}

void Position::setPieces(array<bool, PIECE_STRING_SIZE> pieces) {
	for (int i = 0; i < PIECE_STRING_SIZE; i++) {
		piecesGene[i] = pieces[i];
	}
}

// For now, any position with two kings of the same color will have a fitness of cero.

void Position::setFitness() {

	thc::ChessRules position;
	const char* str = &FEDstringCode[0];
	position.Forsyth(str);
	vector<thc::Move> moveList;
	vector<thc::Move> checks;
	position.GenLegalMoveList(moveList);

	int adders = 0;
	char whiteKnightCount = 0;
	char whitePawnCount = 0;
	char whiteBishopCount = 0;
	char whiteQueenCount = 0;
	char whiteRookCount = 0;
	char whiteKingCount = 0;
	char blackKingCount = 0;
	for (auto letter : FEDstringCode) {
		if (letter == ' ') {
			break;
		}
		switch (letter) {
		case 'Q':
			whiteQueenCount++;
			break;
		case 'N':
			whiteKnightCount++;
			break;
		case 'P':
			whitePawnCount++;
			break;
		case 'B':
			whiteBishopCount++;
			break;
		case 'R':
			whiteRookCount++;
			break;
		case 'K':
			whiteKingCount++;
			break;
		case 'k':
			blackKingCount++;
			break;
		}
	}

	if (blackKingCount != 1) {
		adders -= 40;
	}
	if (whiteKingCount != 1) {
		adders -= 15;
	}
	if (whiteQueenCount > 9) {
		adders -= 20;
	}
	if (whiteRookCount > 10) {
		adders -= 15;
	}
	if (whiteBishopCount + whiteQueenCount + whitePawnCount + whiteRookCount + whiteKingCount > 15) {
		adders -= 15;
	}
	if (whiteQueenCount + whiteRookCount > 11) {
		adders -= 15;
	}
	if (whiteQueenCount + whiteBishopCount > 11) {
		adders -= 15;
	}

	// Black King in Check
	if (blackKingCount == 1) {
		if (position.AttackedPiece(position.bking_square)) {
			adders -= 23;
		}
	}

	fitness = moveList.size() * 1.08 + adders;
	fitness < 0 ? fitness = 0 : fitness;
	setNumberOfMoves(moveList.size());
}

void Position::setNumberOfMoves(int size) {
	numberOfMoves = size;
}

bool generateRandomBit() {
	random_device rd; // Obtain a random seed from hardware
	mt19937 gen(rd()); // Seed the random number generator
	uniform_int_distribution<> distrib(0, 1); // Distribution for generating 0 or 1

	int randomBit = distrib(gen); // Generate 0 or 1 randomly

	return randomBit;
}

void Position::printBoardGene() {
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

void Position::printFED() {
	cout << "FED: ";
	cout << FEDstringCode << endl;
}

void Position::setFED() {
	int numberOfPieces = -1;
	int emptySpaces = 0;
	int rank = 1;
	FEDstringCode = "";
	for (int i = 0; i < BOARD_STRING_SIZE; i++) {
		if (i != 0 && ((i % N1) == 0)) {
			if (emptySpaces != 0) {
				FEDstringCode.append(to_string(emptySpaces));
				emptySpaces = 0;
			}
			FEDstringCode.append("/");
			rank++;
		}
		string piece = "";
		if (boardGene[i] && numberOfPieces != 31) {
			numberOfPieces++;

			// Translate coding to string
			for (int j = 0; j < PIECE_SIZE; j++) {
				piece.append(to_string(piecesGene[numberOfPieces * 4 + j]));
			}
			if (piece == "0110") {
				setSpecies(rank);
			}

			// If the coding does exist
			if (FEDstrings.find(piece) != FEDstrings.end()) {
				if (emptySpaces != 0) {
					FEDstringCode.append(to_string(emptySpaces));
					emptySpaces = 0;
				}
				FEDstringCode.append(FEDstrings.at(piece));
			}
			// If that coding doesn't exist
			else {
				emptySpaces++;
			}
		}
		else {
			emptySpaces++;
		}
	}
	if (emptySpaces != 0) {
		FEDstringCode.append(to_string(emptySpaces));
	}
	// Structure for library used;
	FEDstringCode.append(" w - - 0 1");
}

void Position::setSpecies(int& rank) {
	switch (rank) {
	case 1:
		species = FIRSTQ;
		break;
	case 2:
		species = FIRSTQ;
		break;
	case 3:
		species = SECONDQ;
		break;
	case 4:
		species = SECONDQ;
		break;
	case 5:
		species = THIRDQ;
		break;
	case 6:
		species = THIRDQ;
		break;
	case 7:
		species = FOURTHQ;
		break;
	case 8:
		species = FOURTHQ;
		break;
	default:
		species = NOBLACKKING;
		break;
	}
}
void Position::setSpecies() {
	species = SECONDQ;
}

