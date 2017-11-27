# mcts_legend_of_heros
A fight agent generator using mcts algorithm for the legent of heros games

# Introduction
Monte Carlo Tree Search(MCTS) is one of the most widely used algorithms in reinforcemene learning. A vanilla MCTS is designed for combinational game with properties: zero-sum, perfect-information, deteministic, discrete and sequential.
However, these properties are also restriction many problems: in sc2, the game is real-time and partially observed, and in turn-based rpg game(the task we want to explore), the players cannot be considered symmetry and have different actions even in same state. 

We want to find out if MCTS is also suitable for this kind of rpg games, and expand some corresbonding variations if possible. 

# Planed

Mini game design & Game State Definite
+ [x] a mini rpg game design, include player's attribute, available skills etc.
+ [x] basic game state design and definition
+ [ ] game state discretization

MCTS and variations 
+ [x] a basic monte carlo tree search implementation
+ [ ] a monte carlo tree search variation for encoded state

Performance
+ [x] average score for default policy (random sampling)
+ [ ] average score for a basic MCTS
+ [ ] average score for MCTS variations

# Others
