#include <iostream>
#include <stdexcept>
#include "FrequencyHistogram.hpp"

FrequencyHistogram::FrequencyHistogram() : frequencies(new std::size_t[HISTOGRAM_SIZE]()) {}

void FrequencyHistogram::add(std::size_t stoppingTime)
{
	if (stoppingTime >= HISTOGRAM_SIZE)
		throw std::out_of_range("Stopping time exceeds histogram range");

	std::lock_guard<std::mutex> lock(mutex);
	++frequencies[stoppingTime];
}

void FrequencyHistogram::print() const
{
	for (std::size_t i = 0; i < HISTOGRAM_SIZE; ++i)
		std::cout << i << "," << frequencies[i] << "\n";
}

std::size_t FrequencyHistogram::total() const 
{
	std::size_t total = 0;
	for (std::size_t i = 0; i < HISTOGRAM_SIZE; ++i) 
		total += frequencies[i];

	return total;
}
