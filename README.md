# Hi Kevin! :)

Assignment 6 is all situated in the `snakes_and_ladders/` folder.  
Use `make` in the repo root to build `snl.out`.

NOTE: Throughout the code and this readme, 
snake fields and ladder fields will be commonly referred to as `specials` or `special fields`.

You can run an example with `make run` or execute it manually.  
The program reads CLI arguments to customzie the board. 
Just `make run` uses the flags `-w 5 -h 5 -d 5 -s 10 20 -s 24 5 -s 11 6 -s 9 23` by default.

---

### Usage

- **w**:  
  Width of the board.

- **h**:  
  Height of the board.

- **d**:  
  Number of faces on the dice.

- **u**:  
  When given, adds a bias to the distribution of dice throws via a parameter. 
  1 designates a bias to low numbers, 2 designates a bias to middling numbers, 3 designates a bias to higher numbers.

- **r**:
  Maximum number of rolls per simulation.

- **n**:
  Number of simulations to run.

- **s**:
  Designates a `special field (a snake or a ladder)`. Must be followed by two numbers.
  Type of special field is determined by what number is larger.
  For multiple snakes and ladders, reuse this flag.
  
  Example: 
  `-s 10 20 -s 50 10 -s 2 99` designates a ladder, a snake and then another ladder

### Usage note

  - All CLI arguments require parameters representing whole numbers.

  - No CLI argument parameters may be smaller than 1.

---

### File Structure

- **Graph functions**:  
  `graph.c` and `graph.h`

- **CLI argument parsing**:  
  `utils.c` and `utils.h`

- **Game simulation**:  
  `sim.c` and `sim.h`

- **Main**:
  `main.c`

---

### Examples

I have provided a few text files with examples in `snakes_and_ladders/examples/`.

Use the make commands `run1` through `run6` to try them out, 
or write `make run file=filename` to easily pass your own text file with flags!

- **run**: default
  Runs the simulation with a preset default board.

- **run1**: normal_board
  Creates an average board like youd find in an actual snakes and ladders game. 

- **run2**: oneshot
  Limits the simulation such that a single roll of 100 must be achieved on a d100 to win.

- **run3**: whoops_all_1s
  Changes the dice to be a d1, requiring 100 rolls.

- **run4**: impossible_difficulty
  Limits the simulation such that no configuration of rolls can achieve victory.

- **run5**: coin_toss
  Makes the field 1 x 1 and makes the dice a d2, effectively creating a coin flip simulator.

- **run6**: infinite_loop
  Plays the game normally with the caveat that 6 snakes camp the finish, causing an infinite loop.

- **run7**: low_bias
  Creates an average board, but sets the dice size to 10 and creates a bias towards lower numbers. 

- **run8**: mid_bias
  Creates an average board, but sets the dice size to 10 and creates a bias towards middling numbers. 

- **run9**: high_bias
  Creates an average board, but sets the dice size to 10 and creates a bias towards higher numbers. 
