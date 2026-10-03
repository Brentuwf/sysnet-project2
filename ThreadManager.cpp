#include "ThreadManager.hpp"
#include "CollatzCalculator.hpp"
#include "FrequencyHistogram.hpp"

ThreadManager::ThreadManager(std::size_t numThreads) : threadPool(new std::thread[numThreads])
{
	threadPoolSize = numThreads;

}

void ThreadManager::joinAll()
{
        for (std::size_t i = 0; i < threadPoolSize; ++i) {
                if (threadPool[i].joinable())
                        threadPool[i].join();
        }
}

void ThreadManager::initializeThreads(std::uint64_t range, std::uint64_t &counter, FrequencyHistogram &hist)
{
	for(std::size_t i = 0; i < threadPoolSize; ++i) 
		threadPool[i] = std::thread(&ThreadManager::collatzWorker, this, std::ref(counter), range, std::ref(hist)); 
}

std::uint64_t ThreadManager::getNextValue(std::uint64_t &counter) const
{
        std::lock_guard<std::mutex> lock(counterMutex);
        std::uint64_t value = ++counter;

        return value;
}

void ThreadManager::collatzWorker(std::uint64_t &counter, std::uint64_t limit, FrequencyHistogram &hist)
{
 	while (true) {
                std::uint64_t value = getNextValue(counter); 

                if (value > limit)
                        return;

                hist.add(CollatzCalculator::calculateStoppingTime(value));
        }
}

