/**
 * Implements the FrequencyHistogram class 
 * Used to store the frequencies of each stopping time in a collatz sequence
 * for stopping times 0 through 1000 inclusive
 *
 * Supports both unsafe and safe version 
 *
 * @author Brent Anderson
 * @date 09/30/2026
 * @info COP4634
 */
#include <iostream>
#include <stdexcept>
#include "FrequencyHistogram.hpp"

FrequencyHistogram::FrequencyHistogram() : frequencies(new std::size_t[HISTOGRAM_SIZE]()) {}

/**
 * manual lock and unlock instead of RAII scoped_lock used to implement unsafe handling easier
 */
void FrequencyHistogram::add(std::size_t stoppingTime, bool isUnsafe)
{
	if (isUnsafe) {
		++frequencies[stoppingTime];
	} else {
		histogramMutex.lock();	
		++frequencies[stoppingTime];
		histogramMutex.unlock();
	}
}
/**
 * No locks are used due to it only being called after threads finish building the histogram
 */
void FrequencyHistogram::print() const
{
	for (std::size_t i = 0; i < HISTOGRAM_SIZE; ++i)
		std::cout << i << "," << frequencies[i] << "\n";
}

size_t FrequencyHistogram::getHistogramSize() const 
{
	return HISTOGRAM_SIZE;
}

std::size_t FrequencyHistogram::total() const 
{
	std::size_t total = 0;
	for (std::size_t i = 0; i < HISTOGRAM_SIZE; ++i) 
		total += frequencies[i];

	return total;
}
