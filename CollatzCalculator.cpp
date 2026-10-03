#include <stdexcept>
#include "CollatzCalculator.hpp"

std::size_t CollatzCalculator::calculateStoppingTime(std::uint64_t value)
{
	std::size_t stoppingTime = 0;

	while (value != 1) {
		if (value % 2 == 0) {
			value /= 2;
		} else {
			if (value > CollatzCalculator::MAX_ODD_VALUE)
				throw std::overflow_error("Collatz calculation exceeded uint64_t range");

			value = (3 * value) + 1;
		}

		++stoppingTime;
	}

	return stoppingTime;
}
