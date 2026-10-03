#include <iostream>
#include <stdexcept>

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
	std::unique_ptr<ThreadManager> threadPool(new ThreadManager(numThreads));
	threadPool->initializeThreads(range, counter, *hist);
	threadPool->joinAll();

	hist->print();
	return EXIT_SUCCESS;
}
