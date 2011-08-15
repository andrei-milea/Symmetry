#ifndef _COMMAND_QUEUE
#define _COMMAND_QUEUE

#include <queue>
#include <boost/thread.hpp>

namespace engine
{

class cCommand;

//thread safe class that implements a commands queue
//used to keep the command until the worker threads from
//the pool executes them (half sync half async pattern)
//used design patterns: thread safe interface, monitor object, 
//half-sync, half-async
class cCommandQueue
{
public:	//guarded methods -- interface
	cCommandQueue();
	~cCommandQueue();

	//synchronized methods
	void Put(cCommand *command);
	cCommand* Remove();

	 bool Empty();

	 std::size_t GetSize();

protected:	//not guarded methods
	inline void Put_i(cCommand *command);
	inline cCommand* Remove_i();
	inline bool Empty_i()const;
	std::size_t GetSize_i()const;

private:
	std::queue<cCommand *> m_Queue; 
	boost::mutex m_Mutex;
	boost::condition_variable m_NotEmptyCond;

};

}

#endif


