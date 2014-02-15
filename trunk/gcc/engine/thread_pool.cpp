#include "thread_pool.h"
#include <cassert>
#include "logger.h"
#include "command.h"
#include "session.h"


namespace engine
{

cThreadPool::cThreadPool(unsigned int num_threads)
	:m_Num_Threads(num_threads),
	 m_Started(false)
{
}

cThreadPool::~cThreadPool()
{
	assert(false == m_Started);
}

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
	catch(const std::exception &ex)
	{
		cLogger::getInstance().print(ex);
		throw;
	}
}

void cThreadPool::StopPool()
{
	m_ThreadPool.interrupt_all();
	m_ThreadPool.join_all();
	m_Started = false;
}

void cThreadPool::AddToCommandQueue(std::shared_ptr<cCommand>& command, cSession* session)
{
	m_CommandQueue.Put(std::make_pair(command, session));
}


void cThreadPool::Run()
{
	try
	{
		while(true)
		{
			auto command(m_CommandQueue.Remove());
			try
			{
				command.first->Execute();
				command.second->SetPendingCommand(command.first);
			}
			catch(const std::exception &ex)
			{
				cLogger::getInstance().print(ex);
				throw;
			}
			boost::this_thread::interruption_point();
		}
	}
	catch(const boost::thread_interrupted&)
	{
		cLogger::getInstance().print(CONTEXT_STR + "Thread interrupted", LOG_SEV_INFO);
	}
}


}


