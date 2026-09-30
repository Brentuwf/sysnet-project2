#include <cerrno>
#include <cstdlib>
#include <limits>
#include <stdexcept>
#include <string>
#include "CommandLineParser.hpp"

void CommandLineParser::validateArgumentCount(int argc)
{
	if (!(argc == 3 || argc == 4))
		throw std::invalid_argument("mt-collatz only excepts 2 or 3 command line arguments");
}

std::uint64_t CommandLineParser::parseStartValue(const char *argument)
{
	if (*argument == '\0')
		throw std::invalid_argument("starting value must be a positive integer");

	char* end = NULL;
	errno = 0; /* clear error number to see if conversion will result in overflow */

	unsigned long long value = std::strtoull(argument, &end, 10);

	if (errno == ERANGE || *end != '\0' || value == 0)
		throw std::invalid_argument("starting value must be a positive integer");

	return static_cast<std::uint64_t>(value);
}

std::size_t CommandLineParser::parseThreadCount(const char* argument)
{
	if (*argument == '\0')
		throw std::invalid_argument("Thread count must be a positive integer");

	char* end = NULL;
	errno = 0;

	unsigned long value = std::strtoul(argument, &end, 10);

	if (errno == ERANGE || *end != '\0' || value == 0)
		throw std::invalid_argument("Thread count must be a positive integer");

	if (value > std::numeric_limits<std::size_t>::max())
		throw std::out_of_range("Thread count exceeds the size_t range");

	return static_cast<std::size_t>(value);
}

bool CommandLineParser::isUnsafeThreadMode(const char* argument)
{
	if (std::string(argument) != "-nolock")
		throw std::invalid_argument("Optional argument must be -unsafe");

	return true;
}

