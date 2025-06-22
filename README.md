# PROGRAMMING A CIRCUIT SIMULATOR WITH MODIFIED NODAL ANALYSIS

Project for PHYS30762 at the University of Manchester

This repository explores the design of an AC circuit simulator implemented in C++ using Modified Nodal Analysis
(MNA). The simulator supports arbitrary closed circuits consisting solely of resistors, inductors, and
capacitors connected to a single AC voltage source. Users can construct custom circuits by instantiating
the default `Circuit` class and adding components via their nodal locations. All source files required for
simulation are accessible by including the `MNA.h` header file found within the `MNA` folder. 


Quick and simple guide on how to use MNA
- Include the `MNA.`h header file 
- Instantiate the `Circuit` class 
- Call `set_ac_soucre("source_node", 1.0, 1.0)`, where the second and third arguments are the initial phasor of the source and the frequency respectively.
- Call `add_component<Component_type>("node1", "node2", 1.0, "label)`, where the third argument is the material value of the component, and `Component_type` is either `Resistor`, `Capacitor`, or`Inductor`. 
- When all of the desired components are added, call `print_data()` to view the properties of the circuit.
Example usage of the programme can be found in the `Examples` folder.


# DECLARATION OF USE OF AI
- During this project, ChatGPT was used. This included help with design ideas, automating repetitive tasks, error debugging, and help with MakeFiles.

# To Compile
Use the makefile: write `mingw32-make` in the terminal. Alternatively, type `g++ -Wall -Wextra -std=c++17 -IMNA/include -IExamples (Get-ChildItem MNA/src/*.cxx, Examples/*.cxx, Examples/*.cpp | ForEach-Object { $_.FullName }) -o main.exe` in the terminal. 

