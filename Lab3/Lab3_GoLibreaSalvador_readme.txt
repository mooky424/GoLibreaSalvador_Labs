Program: Stack Implementation in C++
Authors: Go, Kenjie
         Librea, Czyrone
         Salvador, Gabriel

Description:
  This program implements a simple stack data structure using a
  linked list in C++. It provides basic stack operations such as:

    1. Push: Add an element to the top of the stack.
    2. Pop: Remove and return the top element of the stack.
    3. Peek: Retrieve the top element without removing it.

  The stack is implemented using a struct IntNode for individual
  elements and IntStack to manage the linked list structure. Memory
  management is handled properly using a destructor to prevent memory leaks.

How to Run and Use the Program:
  1. Open a terminal or command prompt.
  2. Navigate to the directory containing the source file.
  3. Compile the program using a C++ compiler:
        g++ -o stack Lab3_GoLibrea_Salvador.cpp
  4. Run the compiled program: 
        ./stack
  5. The program will do the following:
      a. Initialize an empty stack.
      b. Push 100 elements (0 to 99) onto the stack.
      c. Push additional values (5, 3, 2) onto the stack.
      d. Pop and print the top element multiple times.
      e. Use the peek function to retrieve the top value without removing it.
      f. Automatically clean up memory when the program finishes.