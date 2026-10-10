#include <iostream>
#include <stdexcept>
#include <ctime>

#include "CommandLineParser.hpp"
#include "FrequencyHistogram.hpp"
#include "ThreadManager.hpp"

std::unique_ptr<FrequencyHistogram> hist(new FrequencyHistogram());
std::uint64_t counter = 0;

int main(int argc, char **argv)
{
	uint64_t range = 0;
	size_t numThreads = 0;
	bool isUnsafeMode = false;
	struct timespec start; 
	struct timespec end;
	time_t seconds = 0;
	long nseconds = 0;

	try {
		CommandLineParser::validateArgumentCount(argc);
		range = CommandLineParser::parseStartValue(argv[1]);
		numThreads = CommandLineParser::parseThreadCount(argv[2]);
		if (argc == 4) 
			isUnsafeMode = CommandLineParser::isUnsafeThreadMode(argv[3]);

	} catch (std::exception &message) {
		std::cerr << message.what() << "\n";
		return EXIT_FAILURE;

	}
	std::unique_ptr<ThreadManager> threadPool(new ThreadManager(numThreads, isUnsafeMode));

	clock_gettime(CLOCK_REALTIME, &start);
	try {
		threadPool->initializeThreads(range, counter, *hist);
	} catch (const std::system_error &) {
		threadPool->joinAll();
		return EXIT_FAILURE;
	}
	threadPool->joinAll();
	clock_gettime(CLOCK_REALTIME, &end);

	seconds = end.tv_sec - start.tv_sec;
	nseconds = end.tv_nsec - start.tv_nsec;
	if (nseconds < 0) {
		--seconds;
		/* L used to ensure compiler threats it as a literal long instead of int type */
		nseconds += 1000000000L;
	}	

	hist->print();
	std::cerr << range << ","  << numThreads << "," << seconds << "." << nseconds << "\n"; 
	return EXIT_SUCCESS;
}
