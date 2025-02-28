# CHESS PROPERTIES: Genetic Algorithm Analysis

The chessboard, a seemingly simple 8x8 grid, unfolds into a vast vectorial space of possible positions that defies comprehension. This immense expanse is quantified by the Shannon number, estimated at 10^120, which represents the approximate number of unique chess games that could be played—accounting for every legal sequence of moves. To put this into perspective, the number of atoms in the observable universe is estimated to be around 10^80, a figure dwarfed by the Shannon number by a factor of 10^40. This means that for every atom in the cosmos, there are billions upon billions of potential chess positions, each a distinct configuration of pieces locked in strategic interplay. This colossal scale highlights the complexity encoded within the game’s 64 squares, transforming it into a near-infinite playground of possibilities. So, amidst this staggering multitude, how can we find positions that maximize a certain property?
Through the implementation of a genetic algorithm, chess properties are analyzed and explored, while effectively demostrating convergence towards local and pseudo global maxima in multiple maximization problems.
For now (27/02/2024), this algorithm converges into white movement local-maxima chess positions.
The following is a description of the internal workings of these algorithm. Taking in consideration future changes for enhanced performance through recent breakthroughs in genetic algorithms.

The main functions and the structure of the algorithm itself was highly inspired by the book: "Genetic algorithms in search, optimization, and machine learning" by David E. Goldberg. This is considered by myself as a final project regarding the knowledge acquired through it. It is inpsiring and rewarding to use the core ideas of life and natural selection, to basiclly find a couple needles in _**10^40 universe sized haystacks**_.

## Algorithm Functionallity

Each chess position is encoded into a dual-gene configuration. A "Position" gene and a "Board" gene. 
The board gene is a 64 binary string that encodes the matrix configuration of the board itself. Each assigned bit represents wether a given chess piece exists or not in the position it encodes. 
The Position Gene is a 4*32 binary string that encodes all possible 32 pieces in the game. Each piece, is represented through a unique 4-binary encoding. 
The main loop of the algorithm consists in three main steps: Selection, CrossOver and Mutation. Each piece of the main loop is key to create a suitable and incresinglly evolving population.

### **SELECTION:**
The selection procedure consists in finding the most suitable "Chess Board Organisms" to reproduce. That is, to pass on part of their genetic encoding to the next generation. A pool of _**FIT**_ individuals are selected based on their _FITNESS_- This fitness is arbitrary, but for this project, the goal is to **MAXIMIZE THE TOTAL NUMBER OF POSSIBLE MOVES WHITE CAN DO IN A NON-CHECK, POSSIBLE TO REACH IN GAME CHESS POSITION**. Therefore, the fitness function that evaluates the strength of each individual nnecesarilly needs to be directly proportional to the amount of legal moves white can do in such position. 
For this project, a linear fitness function proved to work best: F(moves) = a*moves + b. Where "b" is a given *Punishment Factor* used to maintain within the chess rules the number and type of pieces within the chess board. The main disadvantage with this, is that the *Punishment Factor*, depends on the board being analyzed, and is empirically defined by the properties of such board. Therefore, each characteristic that is non-desirable can be punished in different manners, and in this case, where selected empirically. For example, punishing to much the addition of too many queens (9 is the maximum amount any player can have at any point in the game), can be counter-productive; The algorithm converges to a local-maxima much slower, due to the fact that the algorithm is not ggiven the possibility to in early generations, explore queens distributions that will later on be partially suitable if minimum changes are performed.

A deep analysis is yet to be performed on twicking the punishment variables that constitute the *Punishment Factor*, to improve the overall algorithm avarage performance. 

### **CROSSOVER**
CrossOver, just like in real-life reproduction, constitutes the mixing of the genetic inforormation between two given posisitons. Given a crossover allele in the gene, splitting the gene in half and literally crossover each half from one individual to the other, to produce a new individual for the next generation.
The Genetic CrossOver Index is chosen at random.

### **MUTATION**
Mutation, allows ffor new and key genetic information, possibly unexplored before, to populate the current population. Multiple key or strong genetic information can be lost thorugh selection and crossover, where a single bit of information is crucial for performance. Thus, mutation carries out the role of allowing the pole of living organisms to consider a larger "vector space" of genetic information.

## **FUTURE IMPROVEMENTS**
The algorithm still produces overall best-fit impossible and king-in-check positions which in this case are undisirable. The problem is centralize on the encoding chosen. 
The encoding should somehow strictlly limit the chess-board vector-space on to the ones that are possible. If it is assumed that the global maxima of legal moves by white, wuth no king in check, is maximized if and only if 9 white queens are used, the genetic encoding of the chess-board encoding could be simplified into a dual-gene encoding, maintaining the "Board" gene, and a "Position" gene, which implicitlly encodes in which position each piece should be placed when reading the board gene in order for example. However, through the implementation of this project, no assumptions where made about the main characteristics a sub-optimal or global maxima in legal moves chess-board should have; Therefore the presence of undisirable positions was allowed, given that additionally, this could provide insightful and totally usuful genetic allele sequences for fitness improvement through crossover, that could otherwise be ignored with a piece-strict encoding like mentioned before.

### SPECIATION

Subdividing reproduction within individuals by speciation coul provide with highlly improved performance. Empirically, results obtained with 750-1250 individuals, generally converge in the same manner as populations of 4000 individuals in the long run: A .....

# RESULTS

With the empirical configuration established for the fitness function and a population size of 2500, within 500 generations the algorithm produces chess boards positions, (where no king is in check, and the number of pieces in the board is theoreticlly obtainable within a chesss game), a board with more than 195 possible movements for white. Being a probabilistic algorithm, some runs will underperform the average, while others can outperform it. The following is a position with 205 moves obtained by the algorithm:
![alt text]([https://github.com/[username]/[reponame]/blob/[branch]/image.jpg?raw=true](https://github.com/SantinoAggosti/GeneticAlgortihmForChessPropertiesStudy/blob/master/images/206%20-%202Q4B-5Q2-3Q4-Q5Q1-4Q3-1R5Q-1BR1Q3-1kn1K1Q1%20b%20-%20-%200%201.jpg))



Counter intuetivelly, the larger the population doesn´t correlate necesarilly to a higher maximum fitness obtained. There is indeed a correlation initially. But after around 2500-3000 individuals, performance begins to slowly deteriorate as the number of individuals per generation increases. Further data collection and analysis are required to demonstrate this thorugh a rigorous mathematical approach, along with other several statements made through this file.
