# CHESS PROPERTIES: Genetic Algorithm Analysis

The chessboard, a seemingly simple 8x8 grid, unfolds into a vast vectorial space of possible positions that defies comprehension. This immense expanse is quantified by the Shannon number, estimated at 10^120, which represents the approximate number of unique chess games that could be played—accounting for every legal sequence of moves. To put this into perspective, the number of atoms in the observable universe is estimated to be around 10^80, a figure dwarfed by the Shannon number by a factor of 10^40. This means that for every atom in the cosmos, there are billions upon billions of potential chess positions, each a distinct configuration of pieces locked in strategic interplay. This colossal scale highlights the complexity encoded within the game’s 64 squares, transforming it into a near-infinite playground of possibilities. So, amidst this staggering multitude, how can we find positions that maximize a certain property?
Through the implementation of a genetic algorithm, chess properties are analyzed and explored, while effectively demostrating convergence towards local and pseudo global maxima in multiple maximization problems. The following is a description of the internal workings of these algorithm. Taking in consideration future changes for enhanced performance through recent breakthroughs in genetic algorithms.

## Algorithm Functionallity

Each chess position is encoded into a dual-gene configuration. A "Position" gene and a "Board" gene. 
The board gene is a 64 binary string that encodes the matrix configuration of the board itself. Each assigned bit represents wether a given chess piece exists or not in the position it encodes. 
The Position Gene is a 4*32 binary string that encodes all possible 32 pieces in the game. Each piece is represented by a 4-binary encoding in the following way:

TODO: ADD ENCODING FROM CODE

The main loop of the algorithm consists in three main steps: Selection, CrossOver and Mutation.

### **SELECTION:**
The selection procedure consists in finding the most suitable "Chess Board Organisms" to reproduce. That is, to pass on part of their genetic encoding to the next generation. A pool of _**FIT**_ individuals are selected based on their _FITNESS_- This fitness is arbitrary, but for this project, the goal is to **MAXIMIZE THE TOTAL NUMBER OF POSSIBLE MOVES WHITE CAN DO IN A NON-CHECK, POSSIBLE TO REACH IN GAME CHESS POSITION**. Therefore, the fitness function that evaluates the strength of each individual nnecesarilly needs to be directly proportional to the amount of legal moves white can do in such position. 
For this project, a linear fitness function proved to work best: F(moves) = a*moves + b. Where "b" is a given Punishment variable used to maintain within the chess rules the number and type of pieces within the chess board. (EXPLAIN ADVANTAGES AND DISADVANTAGES OF THIS)


### **CROSSOVER**
CrossOver, just like in real-life reproduction, genetic information is mixed by given a crossover allele in the gene, splitting the gene in half and literally crossover each hald from one individual to the other, to produce..... FINISH
The Genetic CrossOver Index is chosen at random. 

### **MUTATION**
Mutation, allows ffor new and key genetic information, possibly unexplored before, to populate the current population. Multiple key or strong genetic information can be lost thorugh selection and crossover, where a single bit of information is crucial for performance. Thus, mutation carries out the role of allowing the pole of living organisms to consider a larger "vector space" of genetic information.

## **FUTURE IMPROVEMENTS**
The algorithm still produces overall best-fit impossible and king-in-check positions which in this case are undisirable. The problem is centralize on the encoding chosen. 
The encoding should somehow strictlly limit the chess-board vector-space on to the ones that are possible. If it is assumed that the global maxima of legal moves by white, wuth no king in check, is maximized if and only if 9 white queens are used, the genetic encoding of the chess-board encoding could be simplified into a dual-gene encoding, maintaining the "Board" gene, and a "Position" gene, which implicitlly encodes in which position each piece should be placed when reading the board gene in order for example. However, through the implementation of this project, no assumptions where made about the main characteristics a sub-optimal or global maxima in legal moves chess-board should have; Therefore the presence of undisirable positions was allowed, given that additionally, this could provide insightful and totally usuful genetic allele sequences for fitness improvement through crossover, that could otherwise be ignored with a piece-strict encoding like mentioned before.

### SPECIATION

Subdividing reproduction within individuals by speciation coul provide with highlly improved performance. Empirically, results obtained with 750-1250 individuals, generally converge in the same manner as populations of 4000 individuals in the long run: A .....

## EMPIRIC ANALYSIS ON FITNESS FUNCTION
The fitness function chosen was of the form: F(moves) = a*moves + b.

Where _**a**_ is an empirical constant that enhances or deplinished the overall importance given to the net number of moves in **ANY** chess position
**_b_** is the so called _Punishment Factor_, which provides with sufficient offset to produce the desirable vector-subspace of chess-boards within all possibilities of possible and impossible chess-boards positions.

Both a and b where choseen empirically by using runs of 500 generations, and populations of 2500 individuals. For each (a,b) pair, 5 runs where executed, and the best fit and maximum number of moves positions were registered. Twenty Five (a,b) pairs where analyzed. The following where the results:
