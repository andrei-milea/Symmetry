#ifndef _CONNECTION_MANAGER_H
#define _CONNECTION_MANAGER_H

#include "http_connection.h"
#include <set>

namespace http_server
{
/*!
  class that maintains a a set of connections
*/
class cConnectionManager : private boost::noncopyable
{
public:
	void StartConnection(connection_ptr);
	void StopConnection(connection_ptr);

	void StopAllConnections();

private:
	std::set<connection_ptr> m_Connections;



};

}

#endif

