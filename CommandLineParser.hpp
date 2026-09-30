/**
 * Defines the CommandLineParser namespace
 * used to parse the command line arguments for starting number
 * number of threads and for thread safety toggle  
 *
 * @author Brent Anderson
 * @date 09/30/2026
 * @info COP4634
 */
#pragma once

#include <cstddef>
#include <cstdint>

namespace CommandLineParser
{
	/**
	 * Validates the number of command-line arguments.
	 *
	 * The program accepts either two or three arguments
	 * Starting value for collatz and number of threads to use are required
	 * -nolock is optional
	 *
	 * @param int Number of command-line arguments
	 *
	 * @throws std::invalid_argument if the number of arguments is not 2 or 3
	 */
	void validateArgumentCount(int argc);
	
	/**
	 * Parses the maximum collatz starting value
	 *
	 * @param const char* The command-line argument representing the collatz starting value
	 *
	 * @return uint64_t The parsed maximum starting value 
	 *
	 * @throws std::invalid_argument if the argument is not a valid integer
	 * @throws std::out_of_range if the argument exceeds the uint64_t range
	 */
	std::uint64_t parseStartValue(const char *argument);

	/**
	 * Parses the number of threads
	 *
	 * @param const char* The command-line argument representing the number of threads
	 *
	 * @return size_t The number of threads
	 *
	 * @throws std::invalid_argument if the argument is not a valid integer or is zero
	 * @throws std::out_of_range if the argument exceeds the size_t range
	 */
	std::size_t parseThreadCount(const char *argument);

	 /**
	 * Determines if the program will run in unsafe thread mode
	 *
	 * only "-nolock" is supported
	 *
	 * @param const char* The third option command line argument 
	 *
	 * @return true if the char* array is equal to "-nolock"
	 *
	 * @throws std::invalid_argument if the caracter array is not equal to "-nolock"   
	 */
	bool isUnsafeThreadMode(const char *argument);
}
