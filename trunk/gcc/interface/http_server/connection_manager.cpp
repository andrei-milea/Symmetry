
#include "connection_manager.h"

namespace http_server
{

cConnectionManager::StartConnection(connection_ptr connection)
{
	m_Connections.insert(connection);
	connection.HandleClient();
};


cConnectionManager::StopConnection(connection_ptr connection)
{
	m_Connections.erase(connection);
	connection->Stop();
};

cConnectionManager::StopAllConnections()
{
	std::for_each(m_Connections.begin(), m_Connections.end(), boost::bind(&connection::Stop, _1));
	m_Connections.clear();
};


}

