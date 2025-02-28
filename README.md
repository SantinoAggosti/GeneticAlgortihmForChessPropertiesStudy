# Chess Properties Maximization: A Genetic Algorithm Approach

The chessboard, an unassuming 8x8 grid, unfolds into a vast vector space of possible positions that defies comprehension. This immense complexity is illustrated by the number of unique legal chess positions, estimated to be around 10^44, based on recent calculations by Tromp and Österlund (2010). For context, the observable universe contains roughly 10^80 atoms—a figure that vastly exceeds the number of chess positions, yet still highlights their staggering scale. In contrast, the Shannon number, which estimates the total number of possible chess games rather than positions, is a far larger figure, approximated at 10^120. Within the 10^44 unique positions, each represents a distinct configuration of pieces locked in strategic interplay, transforming the game’s 64 squares into a near-infinite playground of possibilities. Amidst this staggering multitude, how can we pinpoint positions that maximize specific properties?

This project employs a genetic algorithm to explore and analyze chess properties, demonstrating convergence toward local and pseudo-global maxima for various maximization challenges. As of February 27, 2024, the algorithm focuses on maximizing the number of legal moves available to White in reachable, non-check positions. Below is a detailed breakdown of the algorithm’s mechanics, inspired by recent advancements in genetic algorithms and poised for future enhancements.

The algorithm’s structure draws heavily from Genetic Algorithms in Search, Optimization, and Machine Learning by David E. Goldberg. This project serves as my final application of the knowledge gained from that book. It’s both inspiring and rewarding to harness the principles of life and natural selection to tackle the immense complexity of chess positions. The search space, estimated at 10^44 possible configurations, is akin to finding a needle in a haystack as vast as the universe itself. Overcoming this challenge required innovative encoding strategies and careful tuning of the algorithm’s parameters.

## Algorithm Functionality

Each chess position is represented as a dual-gene configuration: a **Board gene** and a **Position gene**.  
- The **Board gene** is a 64-bit binary string encoding the chessboard’s layout. Each bit indicates whether a piece occupies a specific square (1 for occupied, 0 for empty).  
- The **Position gene** is a 128-bit string (4 bits × 32 pieces) encoding the identity of up to 32 pieces (e.g., king, queen, pawn) using a unique 4-bit identifier per piece.  

The algorithm operates through a main loop comprising three key phases: **Selection**, **Crossover**, and **Mutation**. Together, these phases drive the evolution of a population of chess positions toward higher fitness.

### Selection
Selection identifies the fittest “Chessboard Organisms” to pass their genetic material to the next generation. Fitness is defined arbitrarily based on the project’s goal: **maximizing the total number of legal moves White can make in a non-check, "game-reachable position"**. The fitness function is thus proportional to White’s legal moves. After testing various models, a linear function proved most effective:  

**F(moves) = a × moves + b**  
- *a* scales the move count.  
- *b* is a *Punishment Factor* that penalizes boards violating chess rules (e.g., too many pieces).  

The *Punishment Factor* varies by board and is set empirically. For instance, exceeding the maximum of 9 queens per side (achievable via pawn promotion) incurs a penalty. However, over-penalizing queens can slow convergence by limiting early exploration of queen-heavy configurations, which might later yield high-move positions with slight adjustments. A deeper study of penalty tuning is planned to optimize average performance.

### Crossover
Crossover mimics biological reproduction by blending genetic material from two parent positions. A random crossover point splits each gene (Board and Position) in half, swapping segments between parents to create two offspring for the next generation. This random index ensures diverse recombination while preserving meaningful genetic patterns.

### Mutation
Mutation introduces small, random changes to maintain genetic diversity. Without it, valuable traits might be lost through selection and crossover—especially when a single bit drastically affects fitness. By flipping bits at a low probability, mutation expands the population’s exploration of the chess position vector space, potentially unlocking previously unseen high-fitness configurations.

## Future Improvements

The current algorithm, when the punishment facotr is loose enough, occasionally generates impractical outcomes, such as impossible positions or boards with a king in check. This stems from the encoding, which doesn’t inherently restrict the solution space to legal, reachable positions. One potential fix is a stricter encoding—e.g., a dual-gene system where the Position gene explicitly places pieces from the Board gene, assuming constraints like 9 queens maximize moves. However, this project avoids such assumptions to preserve flexibility and uncover unexpected insights. Undesirable positions are tolerated, as they may still contribute useful genetic sequences via crossover.

### Speciation
Introducing speciation—grouping similar individuals into reproductive subsets—could boost performance. The initial testing of this claim, was performed by subdividing each generation into 4 species. Each individual was assigned a species depending on the rank the black-king was placed at. The first two ranks constituted a species, the third and fourth antoher, and so on. In addition, each generation fitness was normalized so that each species constituted a ~25% of the individuals in each generation. Finally, inter-species and within-species reproduction restriction where tested. 
Speciation results are inconclusive. There was no noticable improvement in maximum fitness, nor accelerated convergence.
A different speciation definition might accelerate convergence by fostering specialized subgroups, each optimizing distinct traits (e.g., queen placement vs. pawn structure). 
Further experiments are needed to quantify its impact.

### Penalty Refinement
The empirical *Punishment Factor* remains a weak point. A systematic approach—perhaps a dynamic penalty adjusting to generation trends—could replace trial-and-error tuning, enhancing consistency and convergence speed.

## Results

Using a population of 2500 and the tuned fitness function, the algorithm produces boards with over 195 legal moves for White within 500 generations. These positions feature no king in check and obey piece limits obtainable in a real game (e.g., via promotions). As a probabilistic method, performance varies: some runs dip below average, while others exceed it, with top performers reaching more than 205 moves.

Interestingly, larger populations don’t always yield better results. Fitness improves with size up to 2500–3000 individuals, beyond which performance slightly declines—possibly due to diluted selection pressure. Rigorous statistical analysis is pending to confirm this trend and other observations.

Here’s a standout position with 205 moves:  
[Link: https://i.imgur.com/Nfxf7tw.png](https://i.imgur.com/Nfxf7tw.png)  
![Preview](https://i.imgur.com/BrnnUnQ.jpg)

Evolution curves illustrate the population’s fitness growth:  
![Curve 1](https://github.com/user-attachments/assets/be07cd65-5b0c-4955-b824-203e5b15101f)  
![Curve 2](https://github.com/user-attachments/assets/d8390da8-aec9-49e0-a70f-1bcf82890f77)

## Favorite Positions

Below are some aesthetically pleasing positions generated by the algorithm. Enjoy! <3

1. **FEN**: `Q3Q1n1/2Q2PkP/r2Q2N1/Q5R1/5Q2/1Q5Q/4Q3/3R2K1 w - - 0 1`  
   ![Image](https://github.com/user-attachments/assets/7aca69e8-1335-4d3d-aa72-73acec7f90a7)

2. **FEN**: `kbR3Q1/NN1Q4/1Q6/4Q3/Q6Q/5Q2/K2Q4/2R3Q1 w - - 0 1`  
   ![Preview](https://i.imgur.com/Nfxf7tw.png)

3. **FEN**: `3Q4/7K/k1N2Q2/n1Q4B/R3Q3/1Q4QQ/3Q4/Q4R2 w - - 0 1`  
   ![Image](https://github.com/user-attachments/assets/5385824a-d1d0-43b3-a159-c711c6f0bd66)
4. **FEN**: `Q2R2nk/2Q3RB/5Q2/1Q5Q/8/4Q3/Q5Q1/3QB1K1 w - - 0 1`
   ![image](https://github.com/user-attachments/assets/50fa2716-e613-4c18-9013-c658590ba75e)

