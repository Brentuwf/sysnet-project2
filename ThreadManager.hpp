/**
 * Defines the ThreadManager class 
 * Used to create and initialize the number of threads to use in calculating a collatz sequence
 * Responsbile for safety creating and joining threads    
 *
 * @author Brent Anderson
 * @date 10/07/2026
 * @info COP4634
 */
#pragma once 

#include <thread>
#include <cstdint>
#include "FrequencyHistogram.hpp"

class ThreadManager
{
	private:
		/* array of thread objects used to create and join each thread */
		std::unique_ptr<std::thread[]> threadPool;
		/* number of threads to create */
		std::size_t threadPoolSize;
		/* determines if mutex locks will be used, true for no locks, false for locks be used to ensure safety */
		bool isUnsafeMode;
		/* mutex lock for the shared counter variable, mutable to be able to be modified in const functions */
		mutable std::mutex counterMutex;
		/**
		 * returns the next value for the collatz sequence 
		 *
		 * @param uint64_t& reference to the shared coutner
		 * @return uint64_t the next value for the coutner
		 */
		std::uint64_t getNextValue(std::uint64_t &counter) const;
		/**
		 * Thread worker function to get the next value to find the stopping time for
		 * then calculate the stopping time for a value, and increase its frequency in the frequency histogram
		 * 
		 * Returns after the next value is greater than the limit.
		 * Skips values that cause overflow or stopping time greater than 1000
		 *
		 * @param uint64_t& reference to the shared counter
		 * @param uint64_t the upper limit of the collatz sequence  
		 * @param FrequencyHistogram& reference to the shared FrequencyHistogram object
		 */
		void collatzWorker(std::uint64_t &counter, std::uint64_t limit, FrequencyHistogram &hist);
	public:
		/**
		 * Contructs the ThreadManager object 
		 * Initailizes the array of thread objects and the value of isUnsafeMode
		 *
		 * @param size_t the number of threads to create
		 * @param bool true for -nolock, mutex locks will not be used  
		 * 	       false otherwise, mutex locks will be used to ensure thread safety  
		 */
		ThreadManager(std::size_t numThreads, bool isUnsafe);
		/**
		 * joins all threads that are able to be joined
		 */
		void joinAll();
		/**
		 * Creates the number of thread specified by threadPoolSize 
		 *
		 * @param uint64_t& reference to the shared counter
		 * @param uint64_t the upper limit of the collatz sequence
		 * @param FrequencyHistogram& reference to the shared frequencyHistogram object
		 *
		 * @throws std::system_error if thread creation fails
		 */ 
		void initializeThreads(std::uint64_t &counter, std::uint64_t limit, FrequencyHistogram &hist);
};
