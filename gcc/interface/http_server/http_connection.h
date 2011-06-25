#ifndef _HTTP_CONNECTION_H
#define _HTTP_CONNECTION_H

#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>

#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int.hpp>
#include <boost/random/variate_generator.hpp>
#include <limits.h>

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

	static unsigned int GetRandUniqueId()const
	{
		static boost::mt19937 gen;
    	static boost::uniform_int<> dist(1, MAXINT);
    	static boost::variate_generator<boost::mt19937&, boost::uniform_int<> > rnd(gen, dist);

		unsigned int random_id = rnd();

		if(m_Sessions.find(random_id) != m_Sessions::end())
    		return random_id;
		else
			return GetRandUniqueId();
	};

private:
    boost::asio::ip::tcp::socket m_Socket;
    boost::asio::streambuf m_RequestBuf;
    boost::asio::streambuf m_ResponseBuf;

	static std::map<unsigned int, cSession> m_Sessions;
    
};



#endif
