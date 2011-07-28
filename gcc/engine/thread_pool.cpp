#include "thread_pool.h"
#include <cassert>
#include "logger.h"
#include "command.h"

#define MAX_THREADS_NUM 100



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

void cThreadPool::AddToCommandQueue(cCommand *command)
{
	m_CommandQueue.Put(command);
};


void cThreadPool::Run()
{
	while(true)
	{
		boost::scoped_ptr<cCommand> pCommand(m_CommandQueue.Remove());
		try
		{
			pCommand->Execute();
		}
		catch(std::exception &ex)
		{
			cLogger log(LOG_SEV_ERROR);
			log<<ex.what();
		}
	}
};




