Program: Concurrent Processes
Authors: Go, Kenjie
         Librea, Czyrone
         Salvador, Gabriel

Description:
  This program implements a C++ program that uses fork() and exec().
  At the start of the program, fork() is called to create a child process.
  The child process executes and runs xclock. Meanwhile, the parent process
  loops indefinitely while printing out the current date/time every 10 seconds.
  For every 3rd print-out of the date and time, a message also gets printed.
  Zombie process handling was also added in the program so that when the
  xclock being ran by the child process gets terminated, the child process will
  be removed from the process list as seen when running ps -ax in the terminal.

How to Run and Use the Program:
  1. Open a terminal or command prompt.

  2. Navigate to the directory containing the source file.

  3. Compile the program using a C++ compiler:
    
      g++ -o lab6 Lab6_GoLibrea_Salvador_code.cpp

  4. Run the compiled program: 

      ./lab6
  
  5. Observe how the processes get logged in the system by running:

      ps -ax
  
  6. Try terminating the xclock and notice what changes in the processes list.