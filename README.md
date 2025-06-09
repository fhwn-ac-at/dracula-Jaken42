# Hi Kevin! :)

Assignment 6 is all situated in the `snakes_and_ladders/` folder.  
Use `make` in the repo root to build `snl.out`.

NOTE: Throughout the code and this readme, 
snake fields and ladder fields will be referred to as `special fields`.

You can run an example with `make run` or execute it manually.  
The program reads CLI arguments to customzie the board. 
`make run` uses the flags `-w 5 -h 5 -d 5 -s 10 20 -s 24 5 -s 11 6 -s 9 23` by default.

---

### Usage

- No CLI argument parameters may be smaller than 1.

- All CLI argument parameters must be whole numbers.

- **w**:  
  Width of the board.

- **h**:  
  Height of the board.

- **d**:  
  Number of faces on the dice.

- **r**
  Maximum number of rolls per simulation.

- **n**
  Number of simulations to run.

- **s**
  Designates a `special field` (a snake or a ladder). Must be followed by two numbers.
  Type of special field is determined by what number is larger.
  For multiple snakes and ladders, reuse this flag.
  
  Example: 
  `-s 10 20 -s 50 10 -s 2 99`

---

### File Structure

- **Graph functions**:  
  `graph.c` and `graph.h`

- **CLI argument parsing**:  
  `utils.c` and `utils.h`

- **Game simulation**:  
  `sim.c` and `sim.h`

- **Main**
  `main.c`

---

### Examples

I have provided a few text files with examples in snakes_and_ladders/examples/.
Redirect their contents to the program to try them out!
