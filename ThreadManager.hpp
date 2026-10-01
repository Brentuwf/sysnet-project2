#pragma once 

#include <thread>

class ThreadManager
{
	private:
		std::unique_ptr<std::thread[]> threadPool;
		std::size_t threadPoolSize;

	public:
		ThreadManager(std::size_t numThreads);
		void initializeThreads(std::uint64_t range);
};
