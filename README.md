# vectorfield
Basic vector field graphing software created for A-Level Computer Science coursework module. Uses SFML to display graphics. The following algorithms & structures are implemented:
- the shunting yard algorithm to parse mathematical expressions,
- state machines to control the program flow, 
- 4th-order Runge-Kutta integration, to solve the differential equation in question. 

See the development log for how I define and solved the problem.

The program purports to be an educational tool to a teacher who is teaching vector fields to students.

# To build
The program is on Github for archival purposes. Regardless, if you want to build it, you only need:
- SFML libraries
- A C++ compiler

It should build without issues by compiling together all of the files in the **source** folder with the added arguments of `-lsfml-graphics -lsfml-window -lsfml-system` to `g++`.

The program has only been tested on Windows but it should work on Linux as well.

# Development log
I have logged the development of this project (as required by the A-Level module) which you can read in `log.pdf`. This also includes the details for the algorithms used and how I have tied them together to solve the overall problem.

It also discusses some limitations of the solution, with mention to features which would be useful in further development.
