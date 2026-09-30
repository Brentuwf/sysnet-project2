#include <iostream>
#include <stdexcept>

#include "CollatzCalculator.hpp"
#include "CommandLineParser.hpp"
#include "FrequencyHistogram.hpp"

int main(int argc, char **argv)
{
	FrequencyHistogram *hist = new FrequencyHistogram(); /* mem leak for testing only */
	uint64_t startValue = 0;
	size_t numThreads = 0;
	bool isUnsafeMode = false;

	try {
		CommandLineParser::validateArgumentCount(argc);
		startValue = CommandLineParser::parseStartValue(argv[1]);
		numThreads = CommandLineParser::parseThreadCount(argv[2]);
		if (argc == 4) 
			isUnsafeMode = CommandLineParser::isUnsafeThreadMode(argv[3]);

	} catch (std::exception &message) {
		std::cerr << message.what() << "\n";
		return EXIT_FAILURE;

	}

	hist->print();

	std::cout << CollatzCalculator::calculateStoppingTime(startValue) << "\n";
	return EXIT_SUCCESS;
}
