#ifndef _HTTP_CONNECTION_H
#define _HTTP_CONNECTION_H

#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>

#include "../../engine/session.h"

class cHttpConnection
    : public boost::enable_shared_from_this<cHttpConnection>
{
public:

    typedef boost::shared_ptr<cHttpConnection> pointer;

     static pointer Create(boost::asio::io_service& io_service)
     {
         return pointer(new cHttpConnection(io_service));
     };

     boost::asio::ip::tcp::socket& GetSocket()
     {
         return m_Socket;
     };

     void HandleClient();
     void HandleRequest(const boost::system::error_code& error);
     void HandleWriteResponse(const boost::system::error_code& error);
     

private:
    cHttpConnection(boost::asio::io_service& io_service)
        : m_Socket(io_service)
    {
    };

private:
    boost::asio::ip::tcp::socket m_Socket;
    boost::asio::streambuf m_RequestBuf;
    boost::asio::streambuf m_ResponseBuf;

	std::vector<cSession> m_Sessions;
    
};



#endif
