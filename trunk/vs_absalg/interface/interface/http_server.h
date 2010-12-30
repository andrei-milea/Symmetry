#ifndef _HTTP_SERVER_H
#define _HTTP_SERVER_H

#include "http_connection.h"


class cHttpServer : private boost::noncopyable
{
public:
    cHttpServer(boost::asio::io_service &io_service);
    ~cHttpServer()  {};

private:
    void StartAccept();
    void HandleConnection(cHttpConnection::pointer new_connection, const boost::system::error_code& error);

private:
    boost::asio::ip::tcp::acceptor m_Acceptor;

};



#endif
