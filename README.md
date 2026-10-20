# Project 2: mt-collatz 

## Course
COP4634 - Systems & Networks I  
Fall 2026

## Project Overview
This project implements a mutlithreaded solution for solving and recording the frequencies of stopping times for a Collatz sequence.
Once the frequencies of stopping times for a Collatz sequence has been calculating. The histogram storing the frequencies is outputed to standard output, and
the upper limit of the sequence, the number of threads used, and the time it took to execute is outputed to standard error. 

The histogram only support recroding frequencies of stopping time 0 through 1000 inclusive. If a stopping time is greater than 1000. The program will notify the user,
skip the value and continue onto the next value.

## Files
- `mt-collatz.cpp` - contains `main()`, reads user input, and passes the upper limit of the collatz sequence and the number of threads to use to ThreadManager.
- `ThreadManager.cpp` - implementation for creating, and joining threads, along with the runner function 'collatzRunner' for each thread. 
- `ThreadManager.hpp` - declares the `ThreadManager` class and its functions.
- `FrequencyHistogram.cpp` - implementation for functions to create, add and print, an array, which functions as a frequency histogram for collatz stopping times.
- `FrequencyHistogram.hpp` - declares the `FrequencyHistogram` class and its functions. 
- 'CollatzCalculator.cpp' - implementation for the calculateStoppingTime function to calculate the stopping time for a value in a collatz sequence.
- 'CollatzCalculator.hpp' - declares the `CollatzCalculator` namespace and the calculateStoppingTime function. 
- 'CommandLineParser.cpp' - implementation for functions to parse command line arguments for the collatz sequence limit, number of threads, and thread safety toggle.
- 'CommandLineParser.hpp' - declares the `CommandLineParser` namespace and its functions.
- `Makefile` - compiles and links the project.
- `README` - describes the project and its usage.
- `.gitignore` - ignores executable, object, and swap files.

## Building the Program
From the project directory, run:

```bash
make
```

To remove the executable and object files, run:

```bash
make clean
```

The Makefile compiles the project with debugging information and compiler warnings enabled.

## Running the Program
Run the program with:

```bash
./mt-collatz [upper limit] [number of threads] 
```
upper limit and number of threads are required command line arguments for the program to run, they must both be non-zero positive integers.

After exectution the program will print out the histogram to standard output.
The upper limit of the sequence, the number of threads used, the time it took to calculate the stopping time 
and the creation of the histogram in seconds and nanoseconds is outputed to standard error.

Output for the frequency histogram has been truncated to the first 12 lines. 
The integer on the left is the stopping time and its frequency is displayed on the right.

```text
0,1
1,1
2,1
3,1
4,1
5,2
6,2
7,4
8,4
9,6
10,6
11,8
.....
100000,4,0.51629338
```

The program has an option to run in an unsafe mode, which will disable all locks used on shared data 
The required syntax is:

```bash
./mt-collatz [upper limit] [number of threads] -nolock 
```

## Notes
The project is intended to run on the department Linux servers.

The program will also skip values that cause an overflow when calculating the stopping time during the (3n+ 1) operation on uint64_t (usigned long long), this is an extreme 
edge case and I (Brent Anderson) decided not to have to program stop executing, due to its rarity and the large range that would require this to happen. The program will notify the user on the
value that caused the overflow and no stopping time for the value will be added to the histogram.

https://en.cppreference.com/cpp/thread/mutex/lock, https://en.cppreference.com/cpp/thread/mutex/unlock, 
and https://en.cppreference.com/cpp/thread/scoped_lock was used as a refence for how mutex locks are to be used and 
the difference between scoped_lock and manual lock and unlock functions.

https://en.cppreference.com/cpp/thread/thread/hardware_concurrency was used to get the number of logical processors on an OS, to avoid creating more threads than logical processors.

```bash
man clock_gettime
```
The man page for clock_gettime was used to determine the correct structures and variables types to use, and how to correct nanoseconds when a overflow into seconds occurs.

The use of std::unique_ptr and #pragma once was learned from https://cplusplus.com/ when I (Brent Anderson) was teaching myself modern C++ (C++14-C++23)

## Problems
1. Exception being thrown while shared data was locked by a thread, causing a deadlock. This was solved by handling exceptions inside of the thread runner function
and moving shared access outside of where exceptions could be thrown. 



