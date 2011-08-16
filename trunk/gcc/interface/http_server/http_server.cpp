
#include "http_server.h"
#include "../../engine/logger.h"
#include <boost/bind.hpp>
#include <signal.h>

namespace http_server
{

using namespace boost::asio::ip;

cHttpServer::cHttpServer(unsigned int port)
    :m_IOService(),
	m_Acceptor(m_IOService, tcp::endpoint(tcp::v4(), port)),
	m_Signals(m_IOService)
{
	m_Signals.add(SIGINT);
	m_Signals.add(SIGTERM);
#if defined(SIGQUIT)
	m_Signals.add(SIGQUIT);
#endif // defined(SIGQUIT)
	m_Signals.async_wait(boost::bind(&cHttpServer::Stop, this));

    StartAccept();
};

void cHttpServer::StartAccept()
{
    connection_ptr new_connection = cHttpConnection::Create(m_Acceptor.get_io_service(), m_ConnectionManager);

    m_Acceptor.async_accept(new_connection->GetSocket(),
    boost::bind(&cHttpServer::HandleConnection, this, new_connection,
	   boost::asio::placeholders::error));
};

void cHttpServer::HandleConnection(connection_ptr new_connection,
		const boost::system::error_code& error)
{
    if (!error)
    {
		m_ConnectionManager.StartConnection(new_connection);
        StartAccept();
    }
	else
	{
		cLogger log(LOG_SEV_ERROR);
		log<< CONTEXT_STR + error.message();
	}
};

void cHttpServer::Start()
{
	m_IOService.run();
};

void cHttpServer::Stop()
{
	m_Acceptor.close();
	m_ConnectionManager.StopAllConnections();
};



}


