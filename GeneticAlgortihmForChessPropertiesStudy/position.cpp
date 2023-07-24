#include "position.h"
#include <string>
#include "thc.h"

using namespace thc;


void Position :: setPieces() {
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
    char whiteKingCount = 0;
    char blackKingCount = 0;
    //for (auto letter : FEDstringCode) {
    //    if (letter == 'K') {
    //        whiteKingCount++;
    //    }
    //    else if (letter == 'k') {
    //        blackKingCount++;
    //    }
    //}
    //if (blackKingCount == 1 && whiteKingCount == 1) {
        ChessRules position;
        const char* str = &FEDstringCode[0];
        position.Forsyth(str);
        vector<Move> moveList;
        position.GenLegalMoveList(moveList);
        fitness = moveList.size();
    //}
    //else {
    //    fitness = 0;
    //}
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

void Position::printFED() {
    cout << "FED: ";
    cout << FEDstringCode << endl;
}

void Position :: setFED() {
    int numberOfPieces = -1;
    int emptySpaces = 0;
    FEDstringCode = "";
    for (int i = 0; i < BOARD_STRING_SIZE; i++) {
        if (i != 0 && ((i % N) == 0)) {
            if (emptySpaces != 0) {
                FEDstringCode.append(to_string(emptySpaces));
                emptySpaces = 0;
            }
            FEDstringCode.append("/");
        }
        string piece = "";
        if (boardGene[i] && numberOfPieces != 31) {
            numberOfPieces++;

            // Translate coding to string
            for (int j = 0; j < PIECE_SIZE; j++) {
                piece.append(to_string(piecesGene[numberOfPieces * 4 + j]));
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
    FEDstringCode.append(" w KQkq - 0 1");
}

