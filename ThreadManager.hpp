#pragma once 

#include <thread>
#include "FrequencyHistogram.hpp"

class ThreadManager
{
	private:
		std::unique_ptr<std::thread[]> threadPool;
		std::size_t threadPoolSize;
		mutable std::mutex counterMutex;

		std::uint64_t getNextValue(std::uint64_t &counter) const;
		void collatzWorker(std::uint64_t &counter, std::uint64_t limit, FrequencyHistogram &hist);
	public:
		ThreadManager(std::size_t numThreads);
		void joinAll();
		void initializeThreads(std::uint64_t range, std::uint64_t &counter, FrequencyHistogram &hist);
};
