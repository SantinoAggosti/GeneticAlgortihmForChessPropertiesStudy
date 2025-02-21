# CHESS PROPERTIES: Genetic Algorithm Analysis

Through the implementation of a genetic algorithm, chess properties are analyzed and explored, while effectively demostrating convergence towards local and pseudo global maxima in multiple maximization problems.
The following is a description of the internal workings of these algorithm. Taking in consideration future changes for enhanced performance through recent breakthroughs in genetic algorithms.

# Algorithm Functionallity

Each chess position is encoded into a dual-gene configuration. A "Position" gene and a "Board" gene. 
The board gene is a 64 binary string that encodes the matrix configuration of the board itself. Each assigned bit represents wether a given chess piece exists or not in the position it encodes. 
The Position Gene is a 4*32 binary string that encodes all possible 32 pieces in the game. Each piece is represented by a 4-binary encoding in the following way:

TODO: ADD ENCODING FROM CODE
