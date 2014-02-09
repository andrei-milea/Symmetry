

#include "command_queue.h"
#include "session.h"

namespace engine
{


/*****************************************
///////////////interface//////////////////
*****************************************/

typedef boost::unique_lock<boost::mutex> lock_guard;

cCommandQueue::cCommandQueue()
{
}

cCommandQueue::~cCommandQueue()
{
}

void cCommandQueue::Put(session_command& command)
{
	lock_guard lock(m_Mutex);
	Put_i(command);
	m_NotEmptyCond.notify_one();
}

void cCommandQueue::Put(session_command&& command)
{
	lock_guard lock(m_Mutex);
	Put_i(command);
	m_NotEmptyCond.notify_one();
}


session_command cCommandQueue::Remove()
{
	lock_guard lock(m_Mutex);
	while(Empty_i())
	{
		m_NotEmptyCond.wait(lock);
	}

	return Remove_i();
}

bool cCommandQueue::Empty()
{
	lock_guard lock(m_Mutex);
	return Empty_i();
}

std::size_t cCommandQueue::GetSize()
{
	lock_guard lock(m_Mutex);
	return GetSize_i();
}

/*****************************************
////////////implementation////////////////
*****************************************/

void cCommandQueue::Put_i(session_command& command)
{
	m_Queue.push(command);
}

session_command cCommandQueue::Remove_i()
{
	auto command = m_Queue.front();
	m_Queue.pop();
	return command;
}

bool cCommandQueue::Empty_i()const
{
	return m_Queue.empty();
}

std::size_t cCommandQueue::GetSize_i()const
{
	return m_Queue.size();
}

}


