#include "ThreadManager"

ThreadManager::ThreadManager(std::size_t numThreads) : threadPool(new std::thread[numThreads])
{
	threadPoolSize = numThreads;

}

void ThreadManager::initializeThreads(std::uint64_t range)
{
	for(size_t = 0; i < threadPoolSize; ++i) 
		threadPool[i] = new std::thread(counter); /* testing for framework and organization not for use or build */
}

