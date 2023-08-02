# Elementary Cellular Automata
A basic elementary cellular automaton simulator.   
Choose any rule you like, choose an initial state you like (or let one rule spill into the next by changing it mid-simulation) and watch the beautiful patterns.

## Starting
You can set the resolution and pixel size with command line arguments, 500x250x3 is default when no arguments are provided,  
following examples are rule 110.

<img src="https://github.com/HLuksic/ElementaryCellularAutomata/assets/100716721/7136fa11-b96b-4748-82ae-911ffd3be609" alt="drawing" width=500/>

`>ElementaryCellularAutomata.exe 80 80 10`

<img src="https://github.com/HLuksic/ElementaryCellularAutomata/assets/100716721/2c7337b6-5723-4236-93c3-62b2d23949a2" alt="drawing" width=600/>

`>ElementaryCellularAutomata.exe 250 250 3`

<img src="https://github.com/HLuksic/ElementaryCellularAutomata/assets/100716721/66b8fc31-77ac-43fb-8c07-49d6ce2c8d46" alt="drawing" width=700/>

`>ElementaryCellularAutomata.exe 900 900 1`

## Shortcuts:
- TAB - Open / close console
- CTRL - Run / pause the automaton
- R - Shortcut to reset

## Console commands:
- help - Show list of commands, shortcuts and interesting rules
- setrule - Set the automaton rule, range 0-255
- getrule - Show current rule
- setstate - Set the initial state, can be left, right, center or random, remember to reset afterwards
- reset - Clear the simulation and revert to initial state
- clear - Clear the console
- wrap - Enable / disable wrapping around the edges of the simulation

## Examples
Rule 73 from initial state center:

https://github.com/HLuksic/ElementaryCellularAutomata/assets/100716721/247ca30b-1baa-4420-a13a-33db2abe0745

Rule 73 spill into rule 90:

https://github.com/HLuksic/ElementaryCellularAutomata/assets/100716721/d7b0dc71-17ac-48a5-855a-df6d4982bd4e

Rule 90 from initial state center:

https://github.com/HLuksic/ElementaryCellularAutomata/assets/100716721/a2171c67-b5c0-4db3-b4c4-31d1c1e68974

The following examples (in 900x500x2) are a very nice demonstration of how different automata interact. This is rule 184 from  
a random initial state spilling into rule 90. Notice how the proximity of lines seeding rule 90 affect its  
pattern and the perpetual cycle of an increasing state of chaos before "resetting" back to a more stable state.

https://github.com/HLuksic/ElementaryCellularAutomata/assets/100716721/2e1235e4-f131-4e0e-ac39-3ae234032590

https://github.com/HLuksic/ElementaryCellularAutomata/assets/100716721/40d3370b-6079-4139-ae57-33defe57a66b

https://github.com/HLuksic/ElementaryCellularAutomata/assets/100716721/da2b68d2-73da-4b48-9463-40fc8a81bd9b
