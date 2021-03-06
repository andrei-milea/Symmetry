#ifndef _THREAD_POOL_H
#define _THREAD_POOL_H

#include "command_queue.h"

namespace engine
{

/*!
  thread pool class
  uses a queue to hold the commands received
*/
class cThreadPool
{
public:
	cThreadPool(unsigned int num_threads);
	~cThreadPool();

	void StartPool();
	void StopPool();

	void AddToCommandQueue(std::shared_ptr<cCommand>& command, cSession* session);

	bool isStarted()const
	{
		return m_Started;
	};

private:
	
	/*!
	 function that runs in all the threads
	 waits until the queue is not empty
	 and process incoming commands
	*/
	void Run();

private:
	boost::thread_group m_ThreadPool;
	cCommandQueue m_CommandQueue;
	volatile unsigned int m_Num_Threads;
	volatile bool m_Started;
};

}

#endif

