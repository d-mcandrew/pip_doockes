
Team members' contributions over the past two weeks
===============================================================================
Daniel
-------------------------------------------------------------------------------
Wrote first version of player to randomly choose moves
Wrote simple heuristic function
Debugged minimax player

Mara
-------------------------------------------------------------------------------
Wrote minimax player
Added features to heuristic function


Improvements to AI
===============================================================================
Minimax tree which searches to depth of two moves
Multipliers to reward particularly good board positions and penalize 
particularly bad board position

These strategies should work in beating some relatively easy players because 
they usually prevent terrible moves, which can come up frequently in Othello 
and basically determine the outcome of a game in only a single move. This week,
we specifically fixed a bug which caused the player to incorrectly evaluate 
very good and very bad moves, improving its performance significantly.