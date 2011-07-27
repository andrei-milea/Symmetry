

#include "command_queue.h"
#include "getelem_command.h"
#include "getsubgrp_command.h"




/*****************************************
///////////////interface//////////////////
*****************************************/

typedef boost::unique_lock<boost::mutex> lock_guard;

cCommandQueue::cCommandQueue()
{
};

cCommandQueue::~cCommandQueue()
{
};

void cCommandQueue::Put(cCommand *command)
{
	lock_guard lock(m_Mutex);
	Put_i(command);
	m_NotEmptyCond.notify_one();
};


cCommand* cCommandQueue::Remove()
{
	lock_guard lock(m_Mutex);
	while(Empty_i())
	{
		m_NotEmptyCond.wait(lock);
	}
	
	return Remove_i();
};

bool cCommandQueue::Empty()
{
	lock_guard lock(m_Mutex);
	return Empty_i();
};


/*****************************************
////////////implementation////////////////
*****************************************/

void cCommandQueue::Put_i(cCommand *command)
{
	m_Queue.push(command);
};

cCommand* cCommandQueue::Remove_i()
{
	cCommand* command = m_Queue.front();
	m_Queue.pop();
	return command;
};

bool cCommandQueue::Empty_i()const
{
	return (0 == m_Queue.size());
};




