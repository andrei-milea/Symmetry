#ifndef _COMMAND_QUEUE
#define _COMMAND_QUEUE

#include <queue>
#include <utility>
#include <boost/thread.hpp>
#include "command.h"

namespace engine
{
	class cSession;
	using session_command = std::pair<std::shared_ptr<cCommand>, cSession*>;


/*!
 thread safe class that implements a commands queue
 used to keep the command until the worker threads from
 the pool executes them (half sync half async pattern)
 used design patterns: thread safe interface, monitor object,
 half-sync, half-async
*/
class cCommandQueue
{
public:	//guarded methods -- interface
	cCommandQueue();
	~cCommandQueue();

	//synchronized methods
	void Put(session_command& command);
	void Put(session_command&& command);
	session_command Remove();

	bool Empty();

	std::size_t GetSize();

protected:	//not guarded methods
	inline void Put_i(session_command& command);
	inline session_command Remove_i();
	inline bool Empty_i()const;
	std::size_t GetSize_i()const;

private:
	std::queue<session_command> m_Queue;
	boost::mutex m_Mutex;
	boost::condition_variable m_NotEmptyCond;

};

}

#endif


