/**
 * implements the CommandLineParser namespace
 * used to parse the command line arguments for the limit of the collatz sequence, 
 * the number of threads and if locks for thread safety will be used  
 *
 * @author Brent Anderson
 * @date 10/11/2026
 * @info COP4634
 */
#include <limits>
#include <stdexcept>
#include <string>
#include "CommandLineParser.hpp"

void CommandLineParser::validateArgumentCount(int argc)
{
	if (!(argc == 3 || argc == 4))
		throw std::invalid_argument("Usage: ./mt-collatz [upper limit] [number of threads] [-nolock]\n-nolock is optional");
}

std::uint64_t CommandLineParser::parseStartValue(const char *limitArgument)
{
	const std::string input(limitArgument);

	if (input.empty() || input.front() == '-')
		throw std::invalid_argument("Sequence limit must be a positive integer");

	std::size_t pos = 0;
    	unsigned long long limit = 0;
	
	try {
        	limit = std::stoull(input, &pos, 10);
	} catch (const std::out_of_range&) {
		throw std::out_of_range("Sequence limit exceeds the range of an unsigned long long type");
	} catch (const std::invalid_argument&) {
		throw std::invalid_argument("Sequence limit must be a positive integer");
	}

	if (pos != input.size() || limit == 0)
		throw std::invalid_argument("Sequence limit must be a positive integer");

	return static_cast<std::uint64_t>(limit);
}

std::size_t CommandLineParser::parseThreadCount(const char* numThreadsArgument)
{
	const std::string input(numThreadsArgument);

	if (input.empty() || input.front() == '-')
		throw std::invalid_argument("Sequence limit must be a positive integer");

	std::size_t pos = 0;
	unsigned long numThreads = 0;

	try {
		numThreads = std::stoul(input, &pos, 10);
	} catch (const std::out_of_range&) {
		throw std::out_of_range("Thread count exceeds the range of an unsigned long type");
	} catch (const std::invalid_argument&) {
		throw std::invalid_argument("Thread count must be a positive integer");
	}

	if (pos != input.size() || numThreads == 0)
		throw std::invalid_argument("Thread count must be a positive integer");

	if (numThreads > std::numeric_limits<std::size_t>::max())
		throw std::out_of_range("Thread count exceeds the range of an size_t type");

	return static_cast<std::size_t>(numThreads);
}

bool CommandLineParser::isUnsafeThreadMode(const char* argument)
{
	if (std::string(argument) != "-nolock")
		throw std::invalid_argument("Optional argument must be -unsafe");

	return true;
}

