/**
 * Defines the CollatzCalculator namespace
 * used to calculate the stopping time for a collatz sequence  
 *
 * @author Brent Anderson
 * @date 09/30/2026
 * @info COP4634
 */
#pragma once

#include <cstddef> /* for size_t (unsigned int) and uint64_t (unsigned long long) */
#include <limits>

namespace CollatzCalculator 
{
	/*
	 * Maximum odd value that can safely undergo the 3n + 1
	 * used to prevent overflow on uint64_t
	 */
	static constexpr std::uint64_t MAX_ODD_VALUE = (std::numeric_limits<std::uint64_t>::max() - 1) / 3;
	/**
	 * Calculates the Collatz stopping time for a starting value
	 *
	 * @param uint64_t The positive integer to start the sequence from
	 * @return size_t The number of steps required for the sequence to reach 1
	 *
	 * @throw std::overflow_error if calculating 3n + 1 would 
	 * exceed the maximum value uint64_t can hold 
	 */
	std::size_t calculateStoppingTime(std::uint64_t startValue);
}
