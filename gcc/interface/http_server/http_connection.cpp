
#include "http_connection.h"
#include "http_request.h"
#include "http_response.h"
#include "connection_manager.h"
#include "pagebuilder.h"
#include "../../engine/session.h"
#include "../../engine/logger.h"
#include "../../engine/command_creator.h"



#include <iostream>
#include <cassert>
#include <boost/bind.hpp>


namespace http_server
{

//static members
std::map<std::size_t, cSession*> cHttpConnection::s_Sessions;
cEstimator						cHttpConnection::s_Estimator;

typedef std::pair<std::size_t, cSession*> ses_pair;

typedef boost::asio::buffers_iterator<boost::asio::streambuf::const_buffers_type> iterator;
std::pair<iterator, bool> get_whole_http_message(iterator begin, iterator end)
{
	std::string bufstr(begin, end);
	if(0 == (end - begin))
		return std::make_pair(begin, false);
	std::size_t len_iter = bufstr.find("Content-Length: ");
	std::size_t delim_iter = bufstr.find("\r\n\r\n");
	if(std::string::npos ==	len_iter  && std::string::npos != delim_iter)
		return std::make_pair(end, true);
	if(std::string::npos ==	len_iter  && std::string::npos == delim_iter)
		return std::make_pair(begin, false);

	std::string lenpart = bufstr.substr(len_iter);
	std::string lenstr = bufstr.substr(len_iter + 16, lenpart.find("\r\n"));
	int body_sz = atoi(lenstr.c_str());
	if((bufstr.begin() + delim_iter + 4 + body_sz) == bufstr.end())
		return std::make_pair(end, true);

	return std::make_pair(begin, false);
}

void cHttpConnection::HandleClient()
{
	//read
	boost::asio::async_read_until(m_Socket, m_RequestBuf, get_whole_http_message,
	                              boost::bind(&cHttpConnection::HandleRequest, shared_from_this(),
	                              boost::asio::placeholders::error));
}

void cHttpConnection::HandleRequest(const boost::system::error_code& error)
{
	if(!error)
	{
		std::istream is(&m_RequestBuf);
//		debug
//		const char* data_ = boost::asio::buffer_cast<const char*>(m_RequestBuf.data());
//		std::string data(data_, m_RequestBuf.size());
		cRequest _request(is);
		if(false == _request.ParseRequest())
		{
			std::string request_str;
			is >> request_str;

			cLogger::getInstance().print(CONTEXT_STR + "failed to parse request :" + request_str, LOG_SEV_INFO);

			cResponse response(m_ResponseBuf);
			response.BuildResponse(OK, std::string("Error: ") + "invalid request", "text/plain");

			boost::asio::async_write(m_Socket, m_ResponseBuf,
									 boost::bind(&cHttpConnection::HandleWriteResponse, shared_from_this(),
									 boost::asio::placeholders::error));
			return;
		}
		m_HttpVersion = (_request.GetVersion() == HTTP_VER1)? 1 : 0;
		switch(_request.GetMethod())
		{
		case GET_M:
			if(_request.GetResource() == "/" || _request.GetResource() == "/index.html" || _request.GetResource() == "/pres.html")
			{
				//add new session
				unsigned int ses_id = cHttpConnection::GetRandUniqueId();
				cHttpConnection::s_Sessions.insert(ses_pair(ses_id, new cSession(ses_id)));

				//build response
				cResponse response(m_ResponseBuf);
				std::string index_page;
				if(_request.GetResource() == "/" || _request.GetResource() == "/index.html")
					index_page = cPageBuilder::GetInstance()->GetIndexPage(ses_id);
				else
					index_page = cPageBuilder::GetInstance()->GetPresPage(ses_id);

				response.BuildResponse(OK, index_page, "text/html");
			}
			else if(cPageBuilder::GetInstance()->GetResError() != cPageBuilder::GetInstance()->GetPageResource(_request.GetResource()))
			{
				cResponse response(m_ResponseBuf);
				const std::string resource = cPageBuilder::GetInstance()->GetPageResource(
				                                 _request.GetResource());
				if(std::string::npos != _request.GetResource().find("js"))
					response.BuildResponse(OK, resource, "text/javascript");
				else if(std::string::npos != _request.GetResource().find(".html"))
					response.BuildResponse(OK, resource, "text/html");
				else if(std::string::npos != _request.GetResource().find(".jpg"))
					response.BuildResponse(OK, resource, "image/jpg");
				else if(std::string::npos != _request.GetResource().find(".css"))
					response.BuildResponse(OK, resource, "text/css");
				else
					response.BuildResponse(OK, resource, "text/javascript");
			}
			else
			{
				cResponse response(m_ResponseBuf);
				//assert(false);
				//add new session
				//cHttpConnection::s_Sessions.insert(ses_pair(ses_id, new cSession(ses_id)));

				//const std::string index_page  = cPageBuilder::GetInstance()->GetIndexPage(ses_id);
				response.BuildResponse(NOT_FOUND, "", "text/plain");
				//response.BuildResponse(NOT_FOUND, "BAD_REQUEST");
			}
			boost::asio::async_write(m_Socket, m_ResponseBuf,
			                        boost::bind(&cHttpConnection::HandleWriteResponse, shared_from_this(),
									boost::asio::placeholders::error));
			break;
		case POST_M:
			{	//////////////the request is a command
				cResponse response(m_ResponseBuf);
				if( (false == _request.ParseHeaders()) || (false == _request.ParseCommand()) )
				{
					response.BuildResponse(NOT_FOUND, "", "text/plain");
					boost::asio::async_write(m_Socket, m_ResponseBuf,
									 boost::bind(&cHttpConnection::HandleWriteResponse, shared_from_this(),
									 boost::asio::placeholders::error));
					return;
				}
					
				unsigned int ses_id = _request.GetSessionId();

				if(cHttpConnection::s_Sessions.find(ses_id)!=cHttpConnection::s_Sessions.end())
				{
					HandleExistingSession(response, _request, ses_id);
				}
				else
				{
					response.BuildResponse(NOT_FOUND, "invalid request: no session id", "text/plain");
				}

				boost::asio::async_write(m_Socket, m_ResponseBuf,
									 boost::bind(&cHttpConnection::HandleWriteResponse, shared_from_this(),
									 boost::asio::placeholders::error));
			}
			break;
		case HEAD_M:
			break;
		case PUT_M:
			break;
		case OPTIONS_M:
			break;
		case DELETE_M:
			break;
		case TRACE_M:
			break;
		case CONNECT_M:
			break;
		default:
			break;

		}
	}
	else if(error == boost::asio::error::eof)
	{

		m_ConnectionManager.StopConnection(shared_from_this());
	}
}

void cHttpConnection::HandleExistingSession(cResponse& response, const cRequest& _request, const std::size_t ses_id)
{
	try
	{
		cSession* session = cHttpConnection::s_Sessions[ses_id];
		if(session->GetState() == STATE_FREE)
		{
			std::shared_ptr<cCommand> command(cCommandCreator::GetCommand(
									_request.GetCommandId(), _request.GetParam()));
			
			int runtime_estimation = command->EstimateRunTime(s_Estimator);

			if( runtime_estimation <= 360/*seconds*/)
			{
				session->RunCommand(command);
				response.BuildResponse(OK, command->GetResultStr(), "text/plain");
			}
			else
			{
				session->ScheduleCommand(command);
				response.BuildResponse(OK,
									   cPageBuilder::GetInstance()->GetLoadingPage(
										   runtime_estimation, ses_id), "text/plain");
			}
		}
		else if(session->GetState() == STATE_RESULT_PENDING)
		{
			response.BuildResponse(OK, session->GetPendingCommand()->GetResultStr(), "text/plain");
		}
	}
	catch(std::exception& e)
	{
		cLogger::getInstance().print(e, LOG_SEV_INFO);
		response.BuildResponse(OK, std::string("Error: ") + e.what(), "text/plain");
	}
}

void cHttpConnection::HandleWriteResponse(const boost::system::error_code& error)
{
	if(error)
	{
		throw std::runtime_error(CONTEXT_STR + error.message());
	}
	else
	{
		if(m_HttpVersion == true)	//persistent connection
		{
			HandleClient();
		}
		else
		{
			m_ConnectionManager.StopConnection(shared_from_this());
		}
	}
}

void cHttpConnection::Stop()
{
	boost::system::error_code error;
	m_Socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both, error);
	m_Socket.close();
}

}//namespace http_server


