#ifndef _HTTP_CONNECTION_H
#define _HTTP_CONNECTION_H

#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>

#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int.hpp>
#include <boost/random/variate_generator.hpp>
#include <limits.h>
#include "../../engine/estimate.h"

namespace engine
{
class cSession;
}


namespace http_server
{

class cResponse;
class cRequest;
class cConnectionManager;

class cHttpConnection
	: public boost::enable_shared_from_this<cHttpConnection>
{


	typedef boost::shared_ptr<cHttpConnection> connection_ptr;
	typedef std::map<unsigned int, engine::cSession*> sessions_map;

public:

	static connection_ptr Create(boost::asio::io_service& io_service, cConnectionManager &conn_manager)
	{
		return connection_ptr(new cHttpConnection(io_service, conn_manager));
	};

	boost::asio::ip::tcp::socket& GetSocket()
	{
		return m_Socket;
	};

	void HandleClient();
	void HandleRequest(const boost::system::error_code& error);
	void HandleExistingSession(cResponse& response, const cRequest& _request, const unsigned int ses_id);
	void HandleWriteResponse(const boost::system::error_code& error);
	void Stop();
	static void ClearSessions()
	{
		s_Sessions.clear();
	};


private:
	cHttpConnection(boost::asio::io_service& io_service, cConnectionManager &conn_manager)
		:m_Socket(io_service),
		 m_ConnectionManager(conn_manager)
	{
	};

	static unsigned int GetRandUniqueId()
	{
		static boost::mt19937 gen;
		static boost::uniform_int<> dist(1, INT_MAX);
		static boost::variate_generator<boost::mt19937&, boost::uniform_int<> > rnd(gen, dist);

		unsigned int random_id = rnd();

		if(cHttpConnection::s_Sessions.empty())
			return random_id;

		if(cHttpConnection::s_Sessions.find(random_id) == cHttpConnection::s_Sessions.end())
			return random_id;
		else
			return GetRandUniqueId();
	};

private:
	boost::asio::ip::tcp::socket			m_Socket;
	boost::asio::streambuf					m_RequestBuf;
	boost::asio::streambuf					m_ResponseBuf;
	cConnectionManager						&m_ConnectionManager;
	bool									m_HttpVersion;

	static sessions_map						s_Sessions;
	static engine::cEstimator				s_Estimator;
};

typedef boost::shared_ptr<cHttpConnection> connection_ptr;

}


#endif
