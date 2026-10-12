/**
 * Main driver for the collatz sequence calculation program 
 * Responsible for creating shared data, parsing user input, and displaying the frequency histogram and its results 
 * to standard error / standard out  
 *
 * @author Brent Anderson
 * @date 10/11/2026
 * @info COP4634
 */
#include <ctime>
#include <cstdint>
#include <iostream>
#include <stdexcept>
#include "CommandLineParser.hpp"
#include "FrequencyHistogram.hpp"
#include "ThreadManager.hpp"

std::unique_ptr<FrequencyHistogram> hist(new FrequencyHistogram());
std::uint64_t counter = 0;

int main(int argc, char **argv)
{
	uint64_t limit = 0;
	size_t numThreads = 0;
	bool isUnsafeMode = false;
	struct timespec start; 
	struct timespec end;
	time_t seconds = 0;
	long nseconds = 0;

	try {
		CommandLineParser::validateArgumentCount(argc);
		limit = CommandLineParser::parseStartValue(argv[1]);
		numThreads = CommandLineParser::parseThreadCount(argv[2]);
		if (argc == 4) 
			isUnsafeMode = CommandLineParser::isUnsafeThreadMode(argv[3]);

	} catch (const std::exception &message) {
		std::cerr << message.what() << "\n";
		return EXIT_FAILURE;

	}

	std::unique_ptr<ThreadManager> threadPool(new ThreadManager(numThreads, isUnsafeMode));

	clock_gettime(CLOCK_REALTIME, &start);
	try {
		threadPool->initializeThreads(counter, limit, *hist);
	} catch (const std::system_error &message) {
		std::cerr << message.what() << "\n";
		threadPool->joinAll();
		return EXIT_FAILURE;
	}

	threadPool->joinAll();
	clock_gettime(CLOCK_REALTIME, &end);

	seconds = end.tv_sec - start.tv_sec;
	nseconds = end.tv_nsec - start.tv_nsec;
	
	/* Handler for borrowing a second if overflow accured */ 
	if (nseconds < 0) {
		--seconds;
		/* L used to ensure compiler treats it as a literal long instead of int type */
		nseconds += 1000000000L;
	}	

	hist->print();
	std::cerr << limit << ","  << numThreads << "," << seconds << "." << nseconds << "\n"; 
	return EXIT_SUCCESS;
}
