/**
 * Defines the FrequencyHistogram class 
 * Used to store the frequencies of each stopping time in a collatz sequence
 * for stopping to 0 through 1000
 *
 * @author Brent Anderson
 * @date 09/30/2026
 * @info COP4634
 */
#pragma once

#include <cstddef>
#include <memory>
#include <mutex>

class FrequencyHistogram
{

	private:
		static constexpr std::size_t HISTOGRAM_SIZE = 1001;

		std::unique_ptr<std::size_t[]> frequencies;
		mutable std::mutex mutex;
	public:
		/**
		 * Constructs a FrequencyHistogram with all frequencies set to zero
		 */
		FrequencyHistogram();
		/**
		 * increases the count for a collatz stopping in the histogram
		 *
		 * @param size_t The stopping time to record to increment
		 */
		void add(std::size_t stoppingTime);

		/**
		 * Prints the histogram to standard output
		 *
		 * Each entry is printed as a comma-separated record containing
		 * the stopping time and its frequency
		 */
		void print() const;
		std::size_t total() const;
};
