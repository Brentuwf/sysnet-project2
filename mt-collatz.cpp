#include <iostream>

#include "CollatzCalculator.hpp"

int main(int argc, char **argv)
{
	std::cout << CollatzCalculator::calculateStoppingTime(64) << "\n";
	return EXIT_SUCCESS;
}
