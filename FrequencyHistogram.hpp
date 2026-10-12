/**
 * Defines the FrequencyHistogram class 
 * Used to store the frequencies of each stopping time in a collatz sequence
 * for stopping times 0 through 1000 inclusive
 *
 * @author Brent Anderson
 * @date 10/11/2026
 * @info COP4634
 */
#pragma once

#include <cstddef>
#include <memory>
#include <mutex>

class FrequencyHistogram
{

	private:
		/* Size of histogram, includes 0 throughout 1000 */
		static constexpr std::size_t HISTOGRAM_SIZE = 1001;
		/*
		 * array representing the frequencies of collatz stopping time 
		 * indexes represent stoping times,
		 * values of indexes represent the frequency of the stopping time in a sequence  
		 */ 
		std::unique_ptr<std::size_t[]> frequencies;
		/* mutex lock to ensure thread safety for adding values to the histogram */
		std::mutex histogramMutex;
	public:
		/**
		 * Constructs a FrequencyHistogram with all frequencies set to zero
		 */
		FrequencyHistogram();
		/**
		 * increases the count for a collatz stopping time in the histogram
		 *
		 * @param size_t The stopping time to increment
		 */
		void add(std::size_t stoppingTime, bool isUnsafe);

		/**
		 * Prints the histogram to standard output
		 *
		 * Each entry is printed as a comma-separated record containing
		 * the stopping time and its frequency
		 */
		void print() const;
		/**
		 * Returns the size of the frequencies array
		 *
		 * @return size_t the size of the frequencies array
		 */
		size_t getHistogramSize() const;
		// remove this function only for testing 
		std::size_t total() const;
};
