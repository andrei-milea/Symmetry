#ifndef _HTTP_SERVER_H
#define _HTTP_SERVER_H

#include "http_connection.h"
#include "connection_manager.h"


namespace http_server
{
/*!
  class that implements a http server using BOOST ASIO
*/
class cHttpServer : private boost::noncopyable
{
public:
	/*!
	  initializes members and prepares for accepting connections
	*/
	cHttpServer(unsigned int port);
	/*!
	  stops the server
	*/
	~cHttpServer();

	/*!
	  starts the server
	*/
	void Start();
	/*!
	  stops the server
	*/
	void Stop();

private:
	void StartAccept();
	void HandleConnection(connection_ptr new_connection, const boost::system::error_code& error);

private:
	boost::asio::io_service m_IOService;
	boost::asio::ip::tcp::acceptor m_Acceptor;
	cConnectionManager m_ConnectionManager;
	boost::asio::signal_set m_Signals;

};

}


#endif
