
#include "http_server.h"
#include <boost/bind.hpp>


using namespace boost::asio::ip;

cHttpServer::cHttpServer(boost::asio::io_service& io_service)
    :m_Acceptor(io_service, tcp::endpoint(tcp::v4(), 80))
{
    StartAccept();
};

void cHttpServer::StartAccept()
{
    cHttpConnection::pointer new_connection = cHttpConnection::Create(m_Acceptor.io_service());

    m_Acceptor.async_accept(new_connection->GetSocket(),
    boost::bind(&cHttpServer::HandleConnection, this, new_connection,
	   boost::asio::placeholders::error));
};

void cHttpServer::HandleConnection(cHttpConnection::pointer new_connection,
		const boost::system::error_code& error)
{
    if (!error)
    {
        new_connection->HandleClient();
        StartAccept();
    }
};
