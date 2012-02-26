#include "thread_pool.h"
#include <cassert>
#include "logger.h"
#include "command.h"

#define MAX_THREADS_NUM 100

namespace engine
{

cThreadPool::cThreadPool(unsigned int num_threads)
	:m_Num_Threads(num_threads),
	 m_Started(false)
{
	assert(num_threads <= MAX_THREADS_NUM);
};

cThreadPool::~cThreadPool()
{
	assert(false == m_Started);
};

void cThreadPool::StartPool()
{
	m_Started = true;
	try
	{
		for(unsigned int i = 0; i < m_Num_Threads; i++)
		{
			m_ThreadPool.create_thread(boost::bind(&cThreadPool::Run, this));
		}
	}
	catch(std::exception &ex)
	{
		cLogger log(LOG_SEV_ERROR);
		log<<CONTEXT_STR << ex.what();
	}
};

void cThreadPool::StopPool()
{
	m_ThreadPool.interrupt_all();
	m_ThreadPool.join_all();
	m_Started = false;
};

void cThreadPool::AddToCommandQueue(boost::shared_ptr<cCommand>& command)
{
	m_CommandQueue.Put(command);
};


void cThreadPool::Run()
{
	try
	{
		while(true)
		{
			boost::shared_ptr<cCommand> pCommand(m_CommandQueue.Remove());
			try
			{
				pCommand->Execute();
			}
			catch(const std::exception &ex)
			{
				cLogger log(LOG_SEV_ERROR);
				log<<ex.what();
			}
			boost::this_thread::interruption_point();
		}
	}
	catch(const boost::thread_interrupted&)
	{
		cLogger log(LOG_SEV_INFO);
		log<<CONTEXT_STR<<"Thread interrupted";
	}
};


}


