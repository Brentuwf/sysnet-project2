#include <stdexcept>
#include "CollatzCalculator.hpp"

std::size_t CollatzCalculator::calculateStoppingTime(std::uint64_t startValue)
{
	std::size_t stoppingTime = 0;

	while (startValue != 1) {
		if (startValue % 2 == 0) {
			startValue /= 2;
		} else {
			if (startValue > CollatzCalculator::MAX_ODD_VALUE)
				throw std::overflow_error("Collatz calculation exceeded uint64_t range");

			startValue = (3 * startValue) + 1;
		}

		++stoppingTime;
	}

	return stoppingTime;
}
