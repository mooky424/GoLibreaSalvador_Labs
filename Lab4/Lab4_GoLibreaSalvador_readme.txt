Program: Intro to Assembly I: GAS & AT&T Syntax
Authors: Go, Kenjie
         Librea, Czyrone
         Salvador, Gabriel

Description:
  This program implements a C++ function that accepts an integer num to be multiplied to an integer multiplier. The code is optimized such that it handles negative and 0 inputs.

How to Run and Use the Program:
  1. Open a terminal or command prompt.

  2. Navigate to the directory containing the source file.

  3. Before compiling, open and edit the code should you want to change the value of the integer inputs.

  4. Compile the program using a C++ compiler:
    
      g++ -o lab4 Lab4_GoLibrea_Salvador.cpp

  5. Run the compiled program: 

      ./lab4
  
  6. Should you want to generate the assembly code of the C++ code, run the
  command below:

      g++ -S -o lab4.S Lab4_GoLibrea_Salvador.cpp