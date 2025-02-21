# CHESS PROPERTIES: Genetic Algorithm Analysis

Through the implementation of a genetic algorithm, chess properties are analyzed and explored, while effectively demostrating convergence towards local and pseudo global maxima in multiple maximization problems.
The following is a description of the internal workings of these algorithm. Taking in consideration future changes for enhanced performance through recent breakthroughs in genetic algorithms.

# Algorithm Functionallity

Each chess position is encoded into a dual-gene configuration. A "Position" gene and a "Board" gene. 
The board gene is a 64 binary string that encodes the matrix configuration of the board itself. Each assigned bit represents wether a given chess piece exists or not in the position it encodes. 
The Position Gene is a 4*32 binary string that encodes all possible 32 pieces in the game. Each piece is represented by a 4-binary encoding in the following way:

TODO: ADD ENCODING FROM CODE

The main loop of the algorithm consists in three main steps: Selection, CrossOver and Mutation.

#**SELECTION:**
The selection procedure consists in finding the most suitable "Chess Board Organisms" to reproduce. That is, to pass on part of their genetic encoding to the next generation. A pool of _**FIT**_ individuals are selected based on their _FITNESS_- This fitness is arbitrary, but for this project, the goal is to **MAXIMIZE THE TOTAL NUMBER OF POSSIBLE MOVES WHITE CAN DO IN A NON-CHECK, POSSIBLE TO REACH IN GAME CHESS POSITION**. Therefore, the fitness function that evaluates the strength of each individual nnecesarilly needs to be directly proportional to the amount of legal moves white can do in such position. 
For this project, a linear fitness function proved to work best: F(moves) = a*moves + b. Where "b" is a given Punishment variable used to maintain within the chess rules the number and type of pieces within the chess board. (EXPLAIN ADVANTAGES AND DISADVANTAGES OF THIS)


# **CROSSOVER**
CrossOver, just like in real-life reproduction, genetic information is mixed by given a crossover allele in the gene, splitting the gene in half and literally crossover each hald from one individual to the other, to produce..... FINISH
The Genetic CrossOver Index is chosen at random. 

# **MUTATION**
Mutation, allows ffor new and key genetic information, possibly unexplored before, to populate the current population. Multiple key or strong genetic information can be lost thorugh selection and crossover, where a single bit of information is crucial for performance. Thus, mutation carries out the role of allowing the pole of living organisms to consider a larger "vector space" of genetic information.
# BEST RUNS:
