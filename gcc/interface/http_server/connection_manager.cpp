
#include "connection_manager.h"

namespace http_server
{

void cConnectionManager::StartConnection(connection_ptr connection)
{
	m_Connections.insert(connection);
	connection->HandleClient();
};


void cConnectionManager::StopConnection(connection_ptr connection)
{
	m_Connections.erase(connection);
	connection->Stop();
};

void cConnectionManager::StopAllConnections()
{
	std::for_each(m_Connections.begin(), m_Connections.end(), boost::bind(&cHttpConnection::Stop, _1));
	m_Connections.clear();
};


}

